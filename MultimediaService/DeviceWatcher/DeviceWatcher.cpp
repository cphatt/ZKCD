#include "DeviceWatcher.h"
#include "DiskScanner/DiskScanner.h"
#include "DiskDetach/DiskDetach.h"
#include "RunnableThread.h"
#include "UserInterfaceUtility.h"
#include "Detach.h"
#include <QDir>
#include <QRegExp>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <QTimer>

#ifndef gcc
static const QString mountUSBPath("/media/udisk");
static const QString mountSDPath("/media/sdisk");
#else
static const QString usbPath("/home/user/Music/USB");
static const QString sdPath("/home/user/Music/SD");
#endif

static const int watcherInteval(500);
static void usbDiskWatcherCallback(void *paramater);

class DeviceWatcherPrivate
{
    Q_DISABLE_COPY(DeviceWatcherPrivate)
public:
    explicit DeviceWatcherPrivate(DeviceWatcher *parent);
    ~DeviceWatcherPrivate();
    void initialize();
    void connectAllSlots();
    void diskDeviceAdd(const QString &path);
    void diskDeviceRemove(const QString &path);
    void usbDiskScan(const QString &path);
    void usbDiskCancelScan(const QString &path);
    void sdDiskScan(const QString &path);
    void sdDiskCancelScan(const QString &path);
    bool regExpUSBPath(const QString& path);
    bool regExpSDPath(const QString& path);
    DiskScanner* m_USBDiskScanner = NULL;
    DiskScanner* m_SDDiskScanner = NULL;
    DiskDetach* m_DiskDetach = NULL;
    QString m_USBDiskPath;
    QString m_SDDiskPath;
    DeviceWatcherStatus m_USBDiskStatus = DWS_Empty;
    DeviceWatcherStatus m_SDDiskStatus = DWS_Empty;
    //    CustomThread* m_USBDiskWatcher = NULL;
    QTimer* m_Timer = NULL;
    //    QProcess* m_Process = NULL;
    volatile bool m_Heartbeat = false;
    bool m_InitDetach = false;
private:
    DeviceWatcher* m_Parent = NULL;
};

DeviceWatcher::DeviceWatcher(QObject *parent)
    : QObject(parent)
    , m_Private(new DeviceWatcherPrivate(this))
{
}

DeviceWatcher::~DeviceWatcher()
{
}

void DeviceWatcher::synchronize()
{
    qDebug() << "DeviceWatcher::synchronize";
    deviceWatcherCheckStatus(DWT_SDDisk);
    deviceWatcherCheckStatus(DWT_USBDisk);
}

void DeviceWatcher::deviceWatcherCheckStatus(const int type)
{
    qDebug() << "deviceWatcherCheckStatus" << type;
    switch (type) {
    case DWT_SDDisk: {
        emit onDeviceWatcherStatus(DWT_SDDisk, m_Private->m_SDDiskStatus);
        break;
    }
    case DWT_USBDisk: {
        emit onDeviceWatcherStatus(DWT_USBDisk, m_Private->m_USBDiskStatus);
        break;
    }
    default: {
        break;
    }
    }
}

#ifdef gcc
void DeviceWatcher::usbToggle(const int action)
{
    if (0 == action) {
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Add);
    } else {
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Remove);
    }
}

void DeviceWatcher::sdToggle(const int action)
{
    if (0 == action) {
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Add);
    } else {
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Remove);
    }
}
#endif

void DeviceWatcher::timerEvent(QTimerEvent *event)
{
    qDebug() << "DeviceWatcher::timerEvent";
    killTimer(event->timerId());
#ifndef gcc
    system("/sbin/mdev -s");
    system("mount -t ramfs -n none /media");
    system("insmod /lib/modules/3.4.0/kernel/drivers/ark/sdmmc/ark_dw_mmc.ko");
    system("insmod /lib/modules/3.4.0/kernel/drivers/usb/musb/musb_hdrc.ko");
    system("insmod /lib/modules/3.4.0/kernel/drivers/usb/musb/ark1680_musb.ko");
    system("insmod /lib/modules/3.4.0/kernel/drivers/usb/gadget/g_ncm.ko");
    system("echo otg > /sys/devices/platform/musb-ark1680.0/musb-hdrc.0/mode");
#else
    bool sdExsits(false);
    bool usbExists(false);
    if (QFile::exists(sdPath)) {
        sdExsits = true;
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Add);
    }
    if (QFile::exists(usbPath)) {
        usbExists = true;
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Add);
    }
#endif

#ifndef gcc
    //    QDir dir("/dev/");
    //    dir.setFilter(QDir::System | QDir::NoDotAndDotDot);
    //    QFileInfoList fileInfoList = dir.entryInfoList();
    //    bool sdExsits(false);
    //    bool usbExists(false);
    //    for (QFileInfoList::iterator fileIter = fileInfoList.begin(); fileIter != fileInfoList.end(); ++fileIter) {
    //        if ((!sdExsits) && (m_Private->regExpSDPath(fileIter->filePath()))) {
    //            qDebug() << fileIter->filePath();
    //            sdExsits = true;
    //            onDiskDeviceChange(fileIter->filePath(), DiskDeviceWatcher::A_Add);
    //        } else if ((!usbExists) && (m_Private->regExpUSBPath(fileIter->filePath()))) {
    //            qDebug() << fileIter->filePath();
    //            usbExists = true;
    //            onDiskDeviceChange(fileIter->filePath(), DiskDeviceWatcher::A_Add);
    //        }
    //        if (sdExsits && usbExists) {
    //            break;
    //        }
    //    }
#endif
    QObject::timerEvent(event);
}

DeviceWatcherPrivate::DeviceWatcherPrivate(DeviceWatcher *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
#ifdef gcc
    m_Parent->startTimer(3000);
#else
    m_Parent->startTimer(0);
#endif
}

DeviceWatcherPrivate::~DeviceWatcherPrivate()
{
}

void DeviceWatcherPrivate::initialize()
{
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(false);
    m_Timer->setInterval(3333);
    //    m_Process = new QProcess(m_Parent);
    //    m_Process->setProcessChannelMode(QProcess::MergedChannels);
    //    m_USBDiskWatcher = new CustomThread(m_Parent);
    //    m_USBDiskWatcher->setCallbackFunction(usbDiskWatcherCallback, static_cast<void *>(this));
    QStringList m_MusicSuffix;
    m_MusicSuffix.clear();
    m_MusicSuffix.append(QString(".MP2"));
    m_MusicSuffix.append(QString(".MP3"));
    m_MusicSuffix.append(QString(".WMA"));
    m_MusicSuffix.append(QString(".M4A"));
    m_MusicSuffix.append(QString(".FLAC"));
    m_MusicSuffix.append(QString(".APE"));
    m_MusicSuffix.append(QString(".OGG"));
    m_MusicSuffix.append(QString(".AC3"));
    m_MusicSuffix.append(QString(".AAC"));
    m_MusicSuffix.append(QString(".WAV"));
    m_MusicSuffix.append(QString(".AMR"));
    m_MusicSuffix.append(QString(".RA"));
    m_MusicSuffix.append(QString(".AU"));
    m_MusicSuffix.append(QString(".MMF"));

    QStringList m_ImageSuffix;
    m_ImageSuffix.clear();
    m_ImageSuffix.append(QString(".JPG"));
    m_ImageSuffix.append(QString(".BMP"));
    m_ImageSuffix.append(QString(".JPEG"));
    m_ImageSuffix.append(QString(".PNG"));
    m_ImageSuffix.append(QString(".GIF"));
    QStringList m_VideoSuffix;
    m_VideoSuffix.clear();
    m_VideoSuffix.append(QString(".AVI"));
    m_VideoSuffix.append(QString(".MP4"));
    m_VideoSuffix.append(QString(".MPG"));
    m_VideoSuffix.append(QString(".M4V"));
    m_VideoSuffix.append(QString(".MKV"));
    m_VideoSuffix.append(QString(".3GP"));
    m_VideoSuffix.append(QString(".ASF"));
    m_VideoSuffix.append(QString(".MOV"));
    m_VideoSuffix.append(QString(".MPEG"));
    m_VideoSuffix.append(QString(".VOB"));
    m_VideoSuffix.append(QString(".TS"));
    m_VideoSuffix.append(QString(".WMV"));
    m_VideoSuffix.append(QString(".RM"));
    m_VideoSuffix.append(QString(".RMVB"));
    m_VideoSuffix.append(QString(".DIVX"));
    m_VideoSuffix.append(QString(".FLV"));
    m_VideoSuffix.append(QString(".SWF"));
    m_VideoSuffix.append(QString(".OGM"));
    m_VideoSuffix.append(QString(".DAT"));

    m_USBDiskScanner = new DiskScanner(m_Parent);
    m_USBDiskScanner->setMinimumScanTime(1500);
    QMap<int, QStringList> map;
    map.insert(0, m_MusicSuffix);
    map.insert(1, m_ImageSuffix);
    map.insert(2, m_VideoSuffix);
    m_USBDiskScanner->setScannerSuffixMap(map);

    m_SDDiskScanner = new DiskScanner(m_Parent);
    m_SDDiskScanner->setMinimumScanTime(1500);
    map.insert(0, m_MusicSuffix);
    map.insert(1, m_ImageSuffix);
    map.insert(2, m_VideoSuffix);
    m_SDDiskScanner->setScannerSuffixMap(map);

    m_USBDiskPath.clear();
    m_SDDiskPath.clear();

    m_DiskDetach = new DiskDetach(m_Parent);
}

void DeviceWatcherPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_USBDiskScanner, SIGNAL(filePath(const QString &, const int)),
                     m_Parent,         SLOT(onUSBFilePath(const QString &, const int)),
                     type);
    QObject::connect(m_USBDiskScanner, SIGNAL(finish()),
                     m_Parent,         SLOT(onFinish()),
                     type);
    QObject::connect(m_SDDiskScanner, SIGNAL(filePath(const QString &, const int)),
                     m_Parent,        SLOT(onSDFilePath(const QString &, const int)),
                     type);
    QObject::connect(m_SDDiskScanner, SIGNAL(finish()),
                     m_Parent,        SLOT(onFinish()),
                     type);
    QObject::connect(m_DiskDetach, SIGNAL(diskPartition(const QString &, const DiskDeviceWatcher::Action)),
                     m_Parent,     SLOT(onDiskDeviceChange(const QString &, const DiskDeviceWatcher::Action)),
                     type);
    //    QObject::connect(m_Process, SIGNAL(finished(int, QProcess::ExitStatus)),
    //                     m_Parent,  SLOT(onFinished(int, QProcess::ExitStatus)),
    //                     type);
    //    QObject::connect(m_Process, SIGNAL(error(QProcess::ProcessError)),
    //                     m_Parent,  SLOT(onError(QProcess::ProcessError)),
    //                     type);
    //    QObject::connect(m_Process, SIGNAL(readyReadStandardOutput()),
    //                     m_Parent,  SLOT(onReadyReadStandardOutput()),
    //                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
    //    QObject::connect(m_USBDiskWatcher, SIGNAL(finished()),
    //                     m_Parent,         SLOT(onFinish()),
    //                     type);
}

void DeviceWatcherPrivate::diskDeviceAdd(const QString &path)
{
    qDebug() << "diskDeviceAdd" << path << m_USBDiskPath << m_SDDiskPath;
    if (regExpUSBPath(path)) {
        if (m_USBDiskPath.isEmpty()
                && QFile::exists(path)) {
#ifdef gcc
            QString mountUSBPath(path);
#else
            if (!QFile::exists(mountUSBPath)) {
                system("mkdir -p /media/udisk");
            }
            if (!m_InitDetach) {
                initDetach();
            }
            const QString temp(detach(path.toLocal8Bit().constData()));
//            QProcess process;
//            QStringList stringList;
//            stringList << QString("-s");
//            stringList << path;
//            process.start(QString("file"), stringList);
//            process.waitForFinished();
//            QString temp = process.readAllStandardOutput();
            //            qDebug() << "temp1" << temp;
            QString argument(" ");
            if (temp.contains(QString("FAT (32 bit)"))) {
                argument = QString(" -r -o utf8 ");
                //mount /dev/* -o utf8 /media/*
                qWarning() << QString("(32 bit)");
            } else if (temp.contains(QString("FAT (16 bit)"))) {
                //mount /dev/* /media/*
                argument = QString(" -r -o utf8 ");
                qWarning() << QString("(16 bit)");
            } else if (temp.contains(QString("ext4"))) {
                //mount /dev/* /media/*
                qWarning() << QString("4");
            } else if (temp.contains(QString("ext3"))) {
                //mount /dev/* /media/*
                qWarning() << QString("3");
            } else if (temp.contains(QString("ext2"))) {
                //mount /dev/* /media/*
                qWarning() << QString("2");
            }/* else if (temp.contains(QString("NTFS"))) {
            }*/ else {
                qCritical() << "unknow type";
                m_USBDiskStatus = DWS_Unsupport;
                m_USBDiskPath = path;
                emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
                return;
            }
//            int ret = process.exitCode();
            QString command = QString(" mount ") + path + argument + mountUSBPath;
            qDebug() << path << "command" << command;
            /*(0 == ret) && (*/int ret = system(command.toLocal8Bit().constData())/*)*/;
            if (0 == ret) {
#endif
                m_USBDiskPath = path;
                usbDiskScan(mountUSBPath);
#ifndef gcc
            } else {
                qCritical() << "mount usb failed!!!!!1";
            }
#endif
        }
    } else if (regExpSDPath(path)) {
        if (m_SDDiskPath.isEmpty()
                && QFile::exists(path)) {
#ifdef gcc
            QString mountSDPath(path);
#else
            if (!QFile::exists(mountSDPath)) {
                system("mkdir -p /media/sdisk");
            }
            QProcess process;
            QStringList stringList;
            stringList << QString("-s");
            stringList << path;
            process.start(QString("file"), stringList);
            process.waitForFinished();
            QString temp = process.readAllStandardOutput();
            //            qDebug() << "temp2" << temp;
            QString argument(" ");
            if (temp.contains(QString("FAT (32 bit)"))) {
                argument = QString(" -r -o utf8 ");
                qWarning() << QString("(32 bit)");
                //mount /dev/* -o utf8 /media/*
            } else if (temp.contains(QString("FAT (16 bit)"))) {
                //mount /dev/* /media/*
                argument = QString(" -r -o utf8 ");
                qWarning() << QString("(16 bit)");
            } else if (temp.contains(QString("ext4"))) {
                //mount /dev/* /media/*
                qWarning() << QString("4");
            } else if (temp.contains(QString("ext3"))) {
                //mount /dev/* /media/*
                qWarning() << QString("3");
            } else if (temp.contains(QString("ext2"))) {
                //mount /dev/* /media/*
                qWarning() << QString("2");
            }/* else if (temp.contains(QString("NTFS"))) {
            }*/ else {
                qCritical() << "unknow type";
                m_SDDiskStatus = DWS_Unsupport;
                m_SDDiskPath = path;
                emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
                return;
            }
            int ret = process.exitCode();
            QString command = QString(" mount ") + path + argument + mountSDPath;
            qDebug() << path << "command" << command;
            (0 == ret) && (ret = system(command.toLocal8Bit().constData()));
            if (0 == ret) {
#endif
                m_SDDiskPath = path;
                sdDiskScan(mountSDPath);
#ifndef gcc
            } else {
                qCritical() << "mount sd failed!!!!!1";
            }
#endif
        }
    } else {
        qDebug() << "add other device!";
    }
}

void DeviceWatcherPrivate::diskDeviceRemove(const QString &path)
{
    qDebug() << "diskDeviceRemove" << path << m_USBDiskPath << m_SDDiskPath;
    if (m_USBDiskPath == path) {
#ifndef gcc
        //        if (m_USBDiskWatcher->isRunning()) {
        //            qWarning() << "m_USBDiskWatcher->terminate()";
        //            m_USBDiskWatcher->wait();
        //        }
        //        if (0 != system("echo otg > /sys/devices/platform/musb-ark1680.0/musb-hdrc.0/mode")) {
        m_Heartbeat = false;
        m_Timer->stop();
        if (DWS_Unsupport == m_USBDiskStatus) {
            m_USBDiskStatus = DWS_Remove;
            m_USBDiskPath.clear();
            emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
            m_USBDiskStatus = DWS_Empty;
            return ;
        }
#else
        QString mountUSBPath(path);
#endif
#ifndef gcc
        QString command = QString(" umount -l ") + mountUSBPath;
        int ret = system(command.toLocal8Bit().constData());
        if (0 == ret) {
#endif
            usbDiskCancelScan(mountUSBPath);
#ifndef gcc
        } else {
            qCritical() << "umount usb failed!!!!";
        }
#endif
    } else if (m_SDDiskPath == path) {
#ifndef gcc
        if (!QFile::exists(path)) {
            if (DWS_Unsupport == m_SDDiskStatus) {
                m_SDDiskStatus = DWS_Remove;
                m_SDDiskPath.clear();
                emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
                m_SDDiskStatus = DWS_Empty;
                return ;
            }
#else
        QString mountSDPath(path);
#endif
#ifndef gcc
        QString command = QString(" umount -l ") + mountSDPath;
        int ret = system(command.toLocal8Bit().constData());
        if (0 == ret) {
#endif
            sdDiskCancelScan(mountSDPath);
#ifndef gcc
        } else {
            qCritical() << "umount sd failed!!!!";
        }
    }
#endif
} else {
qDebug() << "remove other device!";
}
}

void DeviceWatcherPrivate::usbDiskScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::usbDiskScan" << path;
    m_USBDiskStatus = DWS_Busy;
    m_USBDiskScanner->startScanner(path);
    emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
}

void DeviceWatcherPrivate::usbDiskCancelScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::usbDiskCancelScan" << path;
    m_Heartbeat = false;
    //    if (m_USBDiskWatcher->isRunning()) {
    //        m_USBDiskWatcher->wait();
    //    }
    m_USBDiskStatus = DWS_Remove;
    m_USBDiskPath.clear();
    m_USBDiskScanner->stopScanner();
    emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
    m_USBDiskStatus = DWS_Empty;
}

void DeviceWatcherPrivate::sdDiskScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::sdDiskScan" << path;
    m_SDDiskStatus = DWS_Busy;
    m_SDDiskScanner->startScanner(path);
    emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
}

void DeviceWatcherPrivate::sdDiskCancelScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::sdDiskCancelScan" << path;
    m_SDDiskStatus = DWS_Remove;
    m_SDDiskPath.clear();
    m_SDDiskScanner->stopScanner();
    emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
    m_SDDiskStatus = DWS_Empty;
}

bool DeviceWatcherPrivate::regExpUSBPath(const QString &path)
{
#ifndef gcc
    //    QRegExp usbRegExp("^/dev/sd[a-z][0-9]{0,1}");
    //    return usbRegExp.exactMatch(path);
    return path.startsWith(QString("/dev/sd"));
#else
    if (0 == path.compare(usbPath)) {
        return true;
    } else {
        return false;
    }
#endif
}


bool DeviceWatcherPrivate::regExpSDPath(const QString &path)
{
#ifndef gcc
    //    QRegExp sdRegExp("^/dev/mmcblk{0,1}[0-9]{0,1}p{0,1}[0-9]");
    //    return sdRegExp.exactMatch(path);
    return path.startsWith(QString("/dev/mmcblk"));
#else
    if (0 == path.compare(sdPath)) {
        return true;
    } else {
        return false;
    }
#endif
}

void DeviceWatcher::onDiskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action)
{
    qWarning() << "DeviceWatcher::onDiskDeviceChange" << device << action;
    switch (action) {
    case DiskDeviceWatcher::A_Add: {
        m_Private->diskDeviceAdd(device);
        break;
    }
    case DiskDeviceWatcher::A_Remove: {
        m_Private->diskDeviceRemove(device);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onUSBFilePath(const QString &path, const int index)
{
    switch(index) {
    case 0: {
        emit onMusicFilePath(path, DWT_USBDisk);
        break;
    }
    case 1: {
        emit onImageFilePath(path, DWT_USBDisk);
        break;
    }
    case 2: {
        emit onVideoFilePath(path, DWT_USBDisk);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onSDFilePath(const QString &path, const int index)
{
    switch(index) {
    case 0: {
        emit onMusicFilePath(path, DWT_SDDisk);
        break;
    }
    case 1: {
        emit onImageFilePath(path, DWT_SDDisk);
        break;
    }
    case 2: {
        emit onVideoFilePath(path, DWT_SDDisk);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onFinish()
{
    QObject* ptr = sender();
    if (ptr == m_Private->m_USBDiskScanner) {
        qDebug() << "USB::onFinish";
        m_Private->m_USBDiskStatus = DWS_Ready;
        emit onDeviceWatcherStatus(DWT_USBDisk, m_Private->m_USBDiskStatus);
#ifndef gcc
        m_Private->m_Heartbeat = true;
        m_Private->m_Timer->start();
//                m_Private->m_USBDiskWatcher->start();
#endif
    } else if (ptr == m_Private->m_SDDiskScanner) {
        qDebug() << "SD::onFinish";
        m_Private->m_SDDiskStatus = DWS_Ready;
        emit onDeviceWatcherStatus(DWT_SDDisk, m_Private->m_SDDiskStatus);
    }/* else if (ptr == m_Private->m_USBDiskWatcher) {
        onDiskDeviceChange(m_Private->m_USBDiskPath, DiskDeviceWatcher::A_Remove);
    }*/
}

void DeviceWatcher::onTimeout()
{
#ifndef gcc
//    if (!m_Private->m_InitDetach) {
//        initDetach();
//    }
    QString device;
    if ((m_Private->m_USBDiskPath.length() > 0)
            && (m_Private->m_USBDiskPath.right(1).at(0).isNumber())) {
        device = m_Private->m_USBDiskPath.left(m_Private->m_USBDiskPath.length() - 1);
    } else {
        device = m_Private->m_USBDiskPath;
    }
//    const QString output(detach(device.toLocal8Bit().constData()));
//    if (output.contains(QString("writable, no read permission"))) {
//        m_Private->m_Heartbeat = false;
//        onDiskDeviceChange(m_Private->m_USBDiskPath, DiskDeviceWatcher::A_Remove);
//    }
    int fd = ::open(device.toLocal8Bit().data(), O_RDONLY);
    int ret = 0;
    if (-1 != fd) {
        ret = close(fd);
        fd = 0;
    }
    if (0 != (fd + ret)) {
        m_Private->m_Heartbeat = false;
        onDiskDeviceChange(m_Private->m_USBDiskPath, DiskDeviceWatcher::A_Remove);
    }
#endif
    //    if (QProcess::NotRunning != m_Private->m_Process->state()) {
    //        m_Private->m_Process->terminate();
    //        m_Private->m_Process->waitForFinished();
    //    }
    //    if (m_Private->m_Heartbeat) {
    //        QStringList stringList;
    //        stringList << QString("-s");
    //        if ((m_Private->m_USBDiskPath.length() > 0)
    //                && (m_Private->m_USBDiskPath.right(1).at(0).isNumber())) {
    //            stringList << m_Private->m_USBDiskPath.left(m_Private->m_USBDiskPath.length() - 1);
    //        } else {
    //            stringList << m_Private->m_USBDiskPath;
    //        }
    //        m_Private->m_Process->start(QString("file"), stringList);
    //        m_Private->m_Process->waitForStarted();
    //    }
}

void DeviceWatcher::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //    qDebug() << __FUNCTION__ << exitCode << exitStatus;
    //    if (m_Private->m_Heartbeat) {
    //        if((0 == exitCode)
    //                && (QProcess::NormalExit == exitStatus)) {
    //            m_Private->m_Timer->start();
    //        } else {
    //            onDiskDeviceChange(m_Private->m_USBDiskPath, DiskDeviceWatcher::A_Remove);
    //        }
    //    }
}

void DeviceWatcher::onError(QProcess::ProcessError error)
{
    qDebug() << __FUNCTION__ << error;
}

void DeviceWatcher::onStateChanged(QProcess::ProcessState state)
{
}

void DeviceWatcher::onReadyReadStandardOutput()
{
    //    while (m_Private->m_Process->canReadLine()) {
    //        QString output(m_Private->m_Process->readLine());
    ////        qWarning() << __FUNCTION__ << output;
    //        if (output.contains(QString("writable, no read permission"))) {
    //            m_Private->m_Heartbeat = false;
    //            onDiskDeviceChange(m_Private->m_USBDiskPath, DiskDeviceWatcher::A_Remove);
    //        }
    //    }
}

static void usbDiskWatcherCallback(void* paramater)
{
#if 1
    DeviceWatcherPrivate* ptr = static_cast<DeviceWatcherPrivate *>(paramater);
    if (NULL != ptr) {
        //        int fd(-1);
        //        int ret(0);
        while (ptr->m_Heartbeat) {
            QProcess process;
            QStringList stringList;
            stringList << QString("-s");
            if ((ptr->m_USBDiskPath.right(1).length() > 0)
                    && (ptr->m_USBDiskPath.right(1).at(0).isNumber())) {
                stringList << ptr->m_USBDiskPath.left(ptr->m_USBDiskPath.length() - 1);
            } else {
                stringList << ptr->m_USBDiskPath;
            }
            process.start(QString("file"), stringList);
            process.waitForFinished();
            if (0 == process.exitCode()) {
                QString temp = process.readAllStandardOutput();
                qWarning() << "temp1" << temp;
                if (temp.contains(QString("writable, no read permission"))) {
                    break;
                }
                //                    if (temp.contains(QString("FAT (32 bit)"))) {
                //                        //mount /dev/* -o utf8 /media/*
                ////                        qWarning() << QString("(32 bit)");
                //                    } else if (temp.contains(QString("FAT (16 bit)"))) {
                //                        //mount /dev/* /media/*
                ////                        qWarning() << QString("(16 bit)");
                //                    } else if (temp.contains(QString("ext4"))) {
                //                        //mount /dev/* /media/*
                ////                        qWarning() << QString("4");
                //                    } else if (temp.contains(QString("ext3"))) {
                //                        //mount /dev/* /media/*
                ////                        qWarning() << QString("3");
                //                    } else if (temp.contains(QString("ext2"))) {
                //                        //mount /dev/* /media/*
                ////                        qWarning() << QString("2");
                //                    }/* else if (temp.contains(QString("NTFS"))) {
                //                    }*/ else {
                //                        qWarning() << "unknow type";
                //                        break;
                //                    }
                //                fd = ::open(ptr->m_USBDiskPath.left(ptr->m_USBDiskPath.length() - 1).toLocal8Bit().data(), O_RDONLY);
                //                if (-1 != fd) {
                //                    ret = ::close(fd);
                //                    if (0 != ret) {
                //                        qWarning() << "usbDiskWatcherCallback close failed";
                //                        break;
                //                    }
                //                    ++ptr->m_Hearbeat;
            } else {
                //                    qWarning() << "usbDiskWatcherCallback open failed";
                break;
            }
            ::usleep(watcherInteval);
        }
        ptr->m_Heartbeat = false;
    }
#else
    DeviceWatcherPrivate* ptr = static_cast<DeviceWatcherPrivate *>(paramater);
    if (NULL != ptr) {
        int fd = -1;
        int ret = 0;
        qWarning() << "ptr->m_USBDiskPath" << ptr->m_USBDiskPath;
        if (-1 != (fd = ::open(ptr->m_USBDiskPath.toLocal8Bit().data(), O_RDONLY))) {
            struct stat64 fdStat64;
            ret = ::fstat64(fd, &fdStat64);
            qWarning() << "fstat64" << ret;
            while (1) {
                if (!ptr->m_Hearbeat) {
                    ret = ::fchmod(fd, fdStat64.st_mode);
                    //                    qWarning("fchmod:%d\n", ret);
                    ret = fdatasync(fd);
                    if (-1 == ret) {
                        ret = ::close(fd);
                        if (0 != ret) {
                            qWarning() << "close failed";
                        }
                        break;
                    } else {
                        ptr->m_Hearbeat = true;
                    }
                }
                usleep(111);
                //                qWarning("fdatasync:%d\n", ret);
            }
        } else {
            //            qWarning("open failed");
        }
    }
#endif
}
