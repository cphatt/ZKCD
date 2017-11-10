#include "DiskScanner.h"
#include "RunnableThread.h"
#include "UserInterfaceUtility.h"
#include <QTimer>
#include <QDir>
#include <QMutex>
#include <QDirIterator>
#include <QCoreApplication>
#include <QMutexLocker>
#include <QQueue>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

static void scannerThreadCallback(void *paramater);

class DiskScannerPrivate
{
    Q_DISABLE_COPY(DiskScannerPrivate)
public:
    explicit DiskScannerPrivate(DiskScanner *parent);
    ~DiskScannerPrivate();
    void initialize();
    void connectAllSlots();
    bool recursionScan(const QString& path);
    //    void recursionScan(const QString &path);
    void scanFinish();
    CustomThread* m_CustomThread = NULL;
    QMap<int, QStringList> m_FilterMapList;
    QStringList m_Filter;
    //    QMap<int, QStringList> m_DiskMapList;
    QTimer* m_Timer = NULL;
    QString m_Path;
    volatile bool m_ContinueFlag = true;
    QMutex m_Mutex;
private:
    DiskScanner* m_Parent = NULL;
};

DiskScanner::DiskScanner(QObject *parent)
    : QObject(parent)
    , m_Private(new DiskScannerPrivate(this))
{   
}

DiskScanner::~DiskScanner()
{
}

void DiskScanner::setScannerSuffixMap(const QMap<int, QStringList> &mapList)
{
    m_Private->m_FilterMapList = mapList;
    for (QMap< int, QStringList >::iterator suffixIter = m_Private->m_FilterMapList.begin();
         suffixIter != m_Private->m_FilterMapList.end();
         ++suffixIter) {
        for (int i = 0; i < suffixIter.value().size(); ++i) {
            m_Private->m_Filter.append(QString("*") + suffixIter.value().at(i));
        }
    }
    //    for (QMap<int, QStringList>::const_iterator iterator = m_Private->m_FilterMapList.constBegin(); iterator != m_Private->m_FilterMapList.constEnd(); ++iterator) {
    //        m_Private->m_DiskMapList.insert(iterator.key(), QStringList());
    //    }
}

void DiskScanner::setMinimumScanTime(const int msec)
{
    m_Private->m_Timer->setInterval(msec);
}

void DiskScanner::startScanner(const QString &path)
{
    QMutexLocker mutexLocker(&m_Private->m_Mutex);
    qDebug() << "DiskScanner::startScanner";
    m_Private->m_Timer->start();
    m_Private->m_Path = path;
    m_Private->m_ContinueFlag = true;
    m_Private->m_CustomThread->start(QThread::InheritPriority);
}

void DiskScanner::stopScanner()
{
    QMutexLocker mutexLocker(&m_Private->m_Mutex);
    qDebug() << "DiskScanner::stopScanner";
    m_Private->m_Path.clear();
    m_Private->m_Timer->stop();
    m_Private->m_ContinueFlag = false;
    //    for (QMap<int, QStringList>::Iterator iterator = m_Private->m_DiskMapList.begin();
    //         iterator != m_Private->m_DiskMapList.end();
    //         ++iterator) {
    //        iterator.value().clear();
    //    }
    if (m_Private->m_CustomThread->isRunning()) {
        m_Private->m_CustomThread->wait();
    }
}

void DiskScanner::onFinish()
{
    qDebug() << "DiskScanner::onFinish" << m_Private->m_Timer->isActive() << sender() << m_Private->m_CustomThread->currentThreadId();
    if (!m_Private->m_Timer->isActive()) {
        onTimeout();
    }
}

void DiskScanner::onTimeout()
{
    qDebug() << "DiskScanner::onTimeout" << m_Private->m_Timer->isActive();
    if (!m_Private->m_CustomThread->isRunning()) {
        m_Private->scanFinish();
    }
}

DiskScannerPrivate::DiskScannerPrivate(DiskScanner *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

DiskScannerPrivate::~DiskScannerPrivate()
{
    m_CustomThread->exit(0);
    m_CustomThread->wait();
}

void DiskScannerPrivate::initialize()
{
    m_CustomThread = new CustomThread(m_Parent);
    m_CustomThread->setCallbackFunction(scannerThreadCallback, static_cast<void *>(this));
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(3500);
}

void DiskScannerPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_CustomThread, SIGNAL(finished()),
                     m_Parent,       SLOT(onFinish()),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

//void DiskScannerPrivate::recursionScan(const QString &path)
//{
//    QDir dir(path);
//    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
//    dir.setSorting(QDir::DirsFirst);
//    QFileInfoList fileInfoList = dir.entryInfoList();
//    for (QFileInfoList::iterator fileIter = fileInfoList.begin(); fileIter != fileInfoList.end(); ++fileIter) {
//        if (fileIter->isDir()) {
//            qDebug() << "fileIter->filePath()" << fileIter->filePath();
//            recursionScan(fileIter->filePath());
//        } else {
//            for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
//                 suffixIter != m_FilterMapList.end();
//                 ++suffixIter) {
//                if (suffixIter.value().contains(fileIter->suffix(), Qt::CaseInsensitive)) {
//                    emit m_Parent->filePath(fileIter->filePath(), suffixIter.key());
//                }
//            }
//        }
//    }
//}

bool DiskScannerPrivate::recursionScan(const QString& path)
{
    QString dirPath(path);
    QQueue<QString> queue;
    queue.enqueue(dirPath);
    DIR* dirptr = NULL;
    struct dirent* direntptr = NULL;
    struct stat64 statbuff;
    QString fullname;
    QString splliter("/");
    while (!queue.isEmpty()) {
        dirPath = queue.dequeue() + splliter;
        if (NULL != (dirptr = opendir(dirPath.toLocal8Bit().data()))) {
            while (NULL != (direntptr = readdir(dirptr))) {
                if ((NULL != direntptr->d_name)
                        && ('.' == direntptr->d_name[0])) {
                    continue;
                } else {
                    fullname = dirPath + QString(direntptr->d_name);
                    if (-1 != stat64(fullname.toLocal8Bit().data(), &statbuff)) {
                        if (S_ISDIR(statbuff.st_mode)) {
                            queue.enqueue(QString(fullname));
                        } else {
                            for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
                                 suffixIter != m_FilterMapList.end();
                                 ++suffixIter) {
                                if (m_ContinueFlag) {
                                    if (suffixIter.value().contains(QString(strrchr(fullname.toLocal8Bit().data(), '.')), Qt::CaseInsensitive)) {
                                        emit m_Parent->filePath(fullname, suffixIter.key());
                                    }
                                } else {
                                    break;
                                }
                            }
                        }
                    } else {
                        qWarning() << "state64 error";
                        break;
                    }
                }
            }
            if (0 == closedir(dirptr)) {
                dirptr = NULL;
            } else {
                qWarning() << "closedir error";
                break;
            }
        } else {
            qWarning() << "opendir failed";
            break;
        }
    }
    return 0;
    //    QString dirPath(path);
    //    QQueue<QString> queue;
    //    queue.enqueue(dirPath);
    //    DIR* dirptr = NULL;
    //    struct dirent* direntptr = NULL;
    //    struct stat64 statbuff;
    //    bool ret = true;
    //    while (!queue.isEmpty()) {
    //        dirPath = queue.dequeue();
    //        if (NULL != (dirptr = opendir(dirPath.toLocal8Bit().data()))) {
    //            while (NULL != (direntptr = readdir(dirptr))) {
    //                char fullname[10086] = {0};
    //                if ('.' == direntptr->d_name[0]) {
    //                    continue;
    //                } else {
    //                    char* flag = strncpy(fullname, dirPath.toLocal8Bit().data(), sizeof(fullname));
    //                    ret = (NULL != flag) && (NULL != strncat(fullname, "/", sizeof(fullname)));
    //                    ret = (NULL != flag) && (NULL != strncat(fullname, direntptr->d_name, sizeof(fullname)));
    //                    if (ret) {
    //                        if (-1 != stat64(fullname, &statbuff)) {
    //                            if (S_ISDIR(statbuff.st_mode)) {
    ////                                qDebug() << "dir" << fullname;
    //                                queue.enqueue(QString(fullname));
    //                            } else {
    //                                for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
    //                                     suffixIter != m_FilterMapList.end();
    //                                     ++suffixIter) {
    //                                    //                                qDebug() << fullname << "fullname" << "recursionScan" << QString(strrchr(fullname, '.'));
    //                                    if (m_ContinueFlag) {
    //                                        if (suffixIter.value().contains(QString(strrchr(fullname, '.')), Qt::CaseInsensitive)) {
    //                                            //                                        qDebug() << fullname << suffixIter.key() << "recursionScan";
    //                                            //                                        m_DiskMapList[suffixIter.key()].append(QString(fullname));
    //                                            emit m_Parent->filePath(fullname, suffixIter.key());
    //                                        }
    //                                    } else {
    //                                        ret = false;
    //                                        break;
    //                                    }
    //                                }
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //            if (0 == closedir(dirptr)) {
    //                dirptr = NULL;
    //            } else {
    //                //close error
    //            }
    //        } else {
    //            qDebug() << "open failed";
    //        }
    //    }
    //    return 0;

    //    QDir dir;
    //    bool ret(true);
    //    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    //    dir.setPath(QString(dirPath));
    //    QFileInfoList fileInfoList;
    //    QQueue<QString> queue;
    //    queue.enqueue(dir.path());
    //    while (!queue.isEmpty()) {
    //        dir.setPath(queue.dequeue());
    //        fileInfoList = dir.entryInfoList();
    //        for (QFileInfoList::iterator iter = fileInfoList.begin();
    //             iter != fileInfoList.end();
    //             ++iter) {
    //            if (iter->isDir()) {
    //                queue.enqueue(iter->filePath());
    //            } else {
    //                for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
    //                     suffixIter != m_FilterMapList.end();
    //                     ++suffixIter) {
    //                    //                                qDebug() << fullname << "fullname" << "recursionScan" << QString(strrchr(fullname, '.'));
    //                    if (m_ContinueFlag) {
    //                        if (suffixIter.value().contains(QString(strrchr(iter->filePath().toLocal8Bit().data(), '.')), Qt::CaseInsensitive)) {
    //                            //                                        qDebug() << fullname << suffixIter.key() << "recursionScan";
    //                            //                                        m_DiskMapList[suffixIter.key()].append(QString(fullname));
    //                            emit m_Parent->filePath(iter->filePath(), suffixIter.key());
    //                        }
    //                    } else {
    //                        ret = false;
    //                        break;
    //                    }
    //                }
    //            }
    //        }
    //        usleep(111);
    //    }
    ////    qDebug() << "filter" << filter;
    //    QDirIterator dirIterator(QString(dirPath),
    //                             m_Filter,
    //                             QDir::Files | QDir::NoSymLinks,
    //                             QDirIterator::Subdirectories);
    //    QFileInfo fileInfo;
    //    while (m_ContinueFlag
    //           && (dirIterator.hasNext())) {
    //        if (dirIterator.hasNext()) {
    //            dirIterator.next();
    //        }
    //        fileInfo = dirIterator.fileInfo();
    ////        qDebug() << "fileInfo" << fileInfo.fileName();
    //        for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
    //             suffixIter != m_FilterMapList.end();
    //             ++suffixIter) {
    ////            qDebug() << fileInfo.filePath() << "fullname" << "recursionScan" << QString(strrchr(fileInfo.filePath().toLocal8Bit().data(), '.'));
    //            if (m_ContinueFlag) {
    //                if (suffixIter.value().contains(QString(strrchr(fileInfo.filePath().toLocal8Bit().data(), '.')), Qt::CaseInsensitive)) {
    ////                    qDebug() << fullname << suffixIter.key() << "recursionScan";
    ////                    m_DiskMapList[suffixIter.key()].append(QString(fullname));
    //                    emit m_Parent->filePath(fileInfo.filePath(), suffixIter.key());
    //                }
    //            } else {
    //                return false;
    //            }
    //        }
    //        usleep(1);
    //    }
    //    bool ret(true);
    //    usleep(119);
    //    DIR* dirptr = NULL;
    //    //    qDebug() << dirPath << "recursionScan";
    //    if (NULL != (dirptr = opendir(dirPath))) {
    //        struct dirent* direntptr = NULL;
    //        while (NULL != (direntptr = readdir(dirptr))) {
    //            char fullname[255] = {0};
    //            if ('.' == direntptr->d_name[0]) {
    //                continue;
    //            } else {
    //                char* flag = strncpy(fullname, dirPath, sizeof(fullname));
    //                ret = (NULL != flag) && (NULL != strncat(fullname, "/", sizeof(fullname)));
    //                ret = (NULL != flag) && (NULL != strncat(fullname, direntptr->d_name, sizeof(fullname)));
    //                if (ret) {
    //                    struct stat64 statbuff;
    //                    if (-1 != stat64(fullname, &statbuff)) {
    //                        if (S_ISDIR(statbuff.st_mode)) {
    //                            if (!(ret = recursionScan(fullname))) {
    //                                break;
    //                            }
    //                        } else {
    //                            for (QMap< int, QStringList >::iterator suffixIter = m_FilterMapList.begin();
    //                                 suffixIter != m_FilterMapList.end();
    //                                 ++suffixIter) {
    //                                //                                qDebug() << fullname << "fullname" << "recursionScan" << QString(strrchr(fullname, '.'));
    //                                if (m_ContinueFlag) {
    //                                    if (suffixIter.value().contains(QString(strrchr(fullname, '.')), Qt::CaseInsensitive)) {
    //                                        //                                        qDebug() << fullname << suffixIter.key() << "recursionScan";
    ////                                        m_DiskMapList[suffixIter.key()].append(QString(fullname));
    //                                        emit m_Parent->filePath(QString(fullname), suffixIter.key());
    //                                    }
    //                                } else {
    //                                    ret = false;
    //                                    break;
    //                                }
    //                            }
    //                        }
    //                    } else {
    //                        qWarning() << "DiskScannerPrivate::recursionScan" << "stat failed";
    //                        ret = false;
    //                        break;
    //                    }
    //                } else {
    //                    qWarning() << "DiskScannerPrivate::recursionScan" << "strgroup failed";
    //                    ret = false;
    //                    break;
    //                }
    //            }
    //            usleep(119);
    //        }
    //        closedir(dirptr);
    //    } else {
    //        qWarning() << "DiskScannerPrivate::recursionScan" << "opendir failed" << dirPath;
    //        ret = false;
    //    }
    //    return ret;
}

void DiskScannerPrivate::scanFinish()
{
    qDebug() << "DiskScannerPrivate::scanFinish" << m_Timer->isActive();
    if (!m_Timer->isActive()) {
        QMutexLocker mutexLocker(&m_Mutex);
        qDebug() << "scanFinish" << m_Path;
        if (!m_Path.isEmpty()) {
            //            for (QMap<int, QStringList>::ConstIterator iterator = m_DiskMapList.constBegin();
            //                 iterator != m_DiskMapList.constEnd();
            //                 ++iterator) {
            //                emit m_Parent->filePath(iterator.value(), iterator.key());
            //            }
            emit m_Parent->finish();
        }
        m_Path.clear();
        m_Timer->stop();
        m_ContinueFlag = false;
        //        for (QMap<int, QStringList>::Iterator iterator = m_DiskMapList.begin();
        //             iterator != m_DiskMapList.end();
        //             ++iterator) {
        //        }
    }
}

static void scannerThreadCallback(void *paramater)
{
    DiskScannerPrivate *ptr = static_cast<DiskScannerPrivate *>(paramater);
    if (NULL != ptr) {
        if (ptr->m_ContinueFlag) {
            //            ptr->recursionScan(ptr->m_Path);
            ptr->recursionScan(ptr->m_Path);
            if (ptr->m_ContinueFlag) {
                ptr->scanFinish();
            }
        }
    }
}
