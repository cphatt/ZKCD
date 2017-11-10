#include "ImagePlayer.h"
#include "AutoConnect.h"
#include "Utility.h"
#include "MultimediaPersistent.h"
#include "UserInterfaceUtility.h"
#include <QList>
#include <QFileInfo>
#include <QTimer>
#include <QMatrix>
#include <QImage>
#include <QImageReader>
#include <QBuffer>
#include <QDomDocument>

class ImagePlayerPrivate
{
    Q_DISABLE_COPY(ImagePlayerPrivate)
public:
    explicit ImagePlayerPrivate(ImagePlayer* parent);
    ~ImagePlayerPrivate();
    void initialize();
    void connectAllSlots();
    void createUSBFileNamesXml();
    void createSDFileNamesXml();
    void playListViewIndex(const DeviceWatcherType type, const int index);
    void playPreviousListViewIndex();
    void playNextListViewIndex();
    void rotateImage();
    void zoomInImage();
    void zoomOutImage();
    QByteArray& convertByteArray(const QImage &image);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void exitImagePlayer();
    void imagePlayerSetExit(const DeviceWatcherType type);
    ImagePlayerPlayStatus m_PlayStatus = IPPS_Exit;
    QList<QString> m_USBPathList;
    QList<QString> m_SDPathList;
    //    QImage m_Image;
    //    QByteArray m_ByteArray;
    //    QImageReader m_ImageReader;
    int m_PlayIndex = 0;
    DeviceWatcherType m_DiskType = DWT_Undefine;
    //    QTimer* m_AnimationTimer;
    QTimer* m_ElapsedTimer = NULL;
    QTimer* m_PlayTimer = NULL;
    QString m_USBFileNamesXml;
    QString m_SDFileNamesXml;
    QString m_CurrentPath;
    int m_RotateAngle = 0;
    float m_Scale = 1.0f;
    bool m_Suspend = false;
private:
    ImagePlayer* m_Parent = NULL;
};

ImagePlayer::ImagePlayer(QObject *parent)
    : QObject(parent)
    , m_Private(new ImagePlayerPrivate(this))
{
}

ImagePlayer::~ImagePlayer()
{
}

void ImagePlayer::imagePlayerRequestFileNames(const DeviceWatcherType type)
{
    qDebug() << "ImagePlayer::imagePlayerRequestFileNames" << type;
    if (DWT_SDDisk == type) {
        emit onImagePlayerFileNames(DWT_SDDisk, m_Private->m_SDFileNamesXml);
    } else if (DWT_USBDisk == type) {
        emit onImagePlayerFileNames(DWT_USBDisk, m_Private->m_USBFileNamesXml);
    }
}

void ImagePlayer::imagePlayerPlayListViewIndex(const DeviceWatcherType type, const int index)
{
    m_Private->playListViewIndex(type, index);
}

void ImagePlayer::imagePlayerPlayPreviousListViewIndex()
{
    m_Private->playPreviousListViewIndex();
}

void ImagePlayer::imagePlayerPlayNextListViewIndex()
{
    m_Private->playNextListViewIndex();
}

void ImagePlayer::imagePlayerRotateImage()
{
    m_Private->rotateImage();
}

void ImagePlayer::imagePlayerZoomInImage()
{
    m_Private->zoomInImage();
}

void ImagePlayer::imagePlayerZoomOutImage()
{
    m_Private->zoomOutImage();
}

void ImagePlayer::imagePlayerSetPlayStatusToggle()
{
    qDebug() << "ImagePlayer::imagePlayerSetPlayStatusToggle" << m_Private->m_PlayStatus;
    switch (m_Private->m_PlayStatus) {
    case IPPS_Play: {
        imagePlayerSetPlayStatus(IPPS_Pause);
        break;
    }
    case IPPS_Pause:
    default: {
        imagePlayerSetPlayStatus(IPPS_Play);
        break;
    }
    }
}

void ImagePlayer::imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "ImagePlayer::imagePlayerSetPlayStatus" << status;
    switch (status) {
    case IPPS_Play: {
        if (m_Private->m_PlayTimer->isActive()) {
            m_Private->m_PlayTimer->stop();
        }
        m_Private->m_PlayTimer->start();
        break;
    }
    case IPPS_Pause:
    case IPPS_Exit: {
        if (m_Private->m_PlayTimer->isActive()) {
            m_Private->m_PlayTimer->stop();
        }
        break;
    }
    case IPPS_SuspendToggle: {
        if (m_Private->m_Suspend) {
            m_Private->m_Suspend = false;
            m_Private->m_PlayTimer->start();
        } else {
            if (m_Private->m_PlayTimer->isActive()) {
                m_Private->m_PlayTimer->stop();
                m_Private->m_Suspend = true;
            }
        }
        return ;
        break;
    }
    default: {
        return;
        break;
    }
    }
    m_Private->m_PlayStatus = status;
    emit onImagePlayerPlayStatus(m_Private->m_PlayStatus);
}

void ImagePlayer::imagePlayerExit()
{
    m_Private->imagePlayerSetExit(m_Private->m_DiskType);
}

void ImagePlayer::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "ImagePlayer::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDPathList.clear();
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDPathList.clear();
            break;
        }
        case DWS_Ready: {
            m_Private->createSDFileNamesXml();
            imagePlayerRequestFileNames(DWT_SDDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDPathList.clear();
            m_Private->imagePlayerSetExit(DWT_SDDisk);
            break;
        }
        default : {
            break;
        }
        }
    } else if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBPathList.clear();
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBPathList.clear();
            break;
        }
        case DWS_Ready: {
            m_Private->createUSBFileNamesXml();
            imagePlayerRequestFileNames(DWT_USBDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBPathList.clear();
            m_Private->imagePlayerSetExit(DWT_USBDisk);
            break;
        }
        default : {
            break;
        }
        }
    }
}

void ImagePlayer::onImageFilePath(const QString &path, const DeviceWatcherType type)
{    
//    qDebug() << "ImagePlayer::onImageFilePath" << path << type;
    if (DWT_SDDisk == type) {
        m_Private->m_SDPathList.append(path);
    } else if (DWT_USBDisk == type) {
        m_Private->m_USBPathList.append(path);
    }
}

void ImagePlayer::onTimeout()
{
    const QTimer* ptr = static_cast<const QTimer*>(sender());
    if (ptr == m_Private->m_ElapsedTimer) {
        if (m_Private->m_PlayTimer->isActive()) {
            imagePlayerSetPlayStatus(IPPS_Play);
        } else {
            imagePlayerSetPlayStatus(IPPS_Pause);
        }
        //        if (m_Private->m_Browse) {
        //            m_Private->m_PlayTimer->start();
        //        }
    } else if (ptr == m_Private->m_PlayTimer) {
        imagePlayerPlayNextListViewIndex();
    }
}

ImagePlayerPrivate::ImagePlayerPrivate(ImagePlayer *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

ImagePlayerPrivate::~ImagePlayerPrivate()
{
}

void ImagePlayerPrivate::initialize()
{
    m_PlayTimer = new QTimer(m_Parent);
    m_PlayTimer->setInterval(5 * 1000);
    //    m_AnimationTimer = new QTimer(m_Parent);
    m_ElapsedTimer = new QTimer(m_Parent);
    m_ElapsedTimer->setSingleShot(true);
    m_ElapsedTimer->setInterval(500);
}

void ImagePlayerPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DeviceWatcher, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_PlayTimer, SIGNAL(timeout()),
                     m_Parent,    SLOT(onTimeout()),
                     type);
    //    QObject::connect(m_AnimationTimer, SIGNAL(timeout()),
    //                     m_Parent,         SLOT(onAnimationTimerTimeout()),
    //                     type);
    QObject::connect(m_ElapsedTimer, SIGNAL(timeout()),
                     m_Parent,       SLOT(onTimeout()),
                     type);
}

void ImagePlayerPrivate::createUSBFileNamesXml()
{
    m_USBFileNamesXml.clear();
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("ImagePlayer")));
    QDomElement root = domDocument.firstChildElement(QString("ImagePlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("USBFileNames"));
    root.appendChild(fileNames);
    m_USBFileNamesXml.clear();
    QString usbPersistantPathInfo = MultimediaPersistent::getImagePathInfo(DWT_USBDisk);
    QStringList stringList = usbPersistantPathInfo.split(QChar('/'));
    QString usbPersistantPath = usbPersistantPathInfo.left(usbPersistantPathInfo.length() - stringList.last().length() - 1);
    QString persistantIndex("");
    QFileInfo fileInfo;
    for (int i = 0; i < m_USBPathList.size(); ++i) {
        info = domDocument.createElement(QString("Index:" + QString::number(i)));
        fileNames.appendChild(info);
        fileInfo.setFile(m_USBPathList.at(i));
        info.appendChild(domDocument.createTextNode(fileInfo.fileName()));
        if (persistantIndex.isEmpty()) {
            if (fileInfo.filePath() == usbPersistantPath) {
                if (usbPersistantPathInfo == (fileInfo.filePath() + QString("/") + fileInfo.created().toString(QString("yyyyMMddhhmmss")) + fileInfo.lastModified().toString(QString("yyyyMMddhhmmss")) + QString::number(fileInfo.size()))) {
                    persistantIndex = QString::number(i);
                }
            }
        }
    }
    QDomElement persistant = domDocument.createElement(QString("USBPersistant"));
    root.appendChild(persistant);
    persistant.appendChild(domDocument.createTextNode(persistantIndex));
    QDomElement type = domDocument.createElement(QString("USBType"));
    root.appendChild(type);
    type.appendChild(domDocument.createTextNode(QString::number(MultimediaPersistent::getMultimediaType(DWT_USBDisk))));
    m_USBFileNamesXml = domDocument.toString();
//    qDebug() << "m_USBFileNamesXml11" << m_USBFileNamesXml;
}

void ImagePlayerPrivate::createSDFileNamesXml()
{
    m_SDFileNamesXml.clear();
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("ImagePlayer")));
    QDomElement root = domDocument.firstChildElement(QString("ImagePlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("SDFileNames"));
    root.appendChild(fileNames);
    m_SDFileNamesXml.clear();
    QString sdPersistantPathInfo = MultimediaPersistent::getImagePathInfo(DWT_SDDisk);
    QStringList stringList = sdPersistantPathInfo.split(QChar('/'));
    QString sdPersistantPath = sdPersistantPathInfo.left(sdPersistantPathInfo.length() - stringList.last().length() - 1);
    QString persistantIndex("");
    QFileInfo fileInfo;
    for (int i = 0; i < m_SDPathList.size(); ++i) {
        info = domDocument.createElement(QString("Index:" + QString::number(i)));
        fileNames.appendChild(info);
        fileInfo.setFile(m_SDPathList.at(i));
        info.appendChild(domDocument.createTextNode(fileInfo.fileName()));
        if (persistantIndex.isEmpty()) {
            if (fileInfo.filePath() == sdPersistantPath) {
                if (sdPersistantPathInfo == (fileInfo.filePath() + QString("/") + fileInfo.created().toString(QString("yyyyMMddhhmmss")) + fileInfo.lastModified().toString(QString("yyyyMMddhhmmss")) + QString::number(fileInfo.size()))) {
                    persistantIndex = QString::number(i);
                }
            }
        }
    }
    QDomElement persistant = domDocument.createElement(QString("SDPersistant"));
    root.appendChild(persistant);
    persistant.appendChild(domDocument.createTextNode(persistantIndex));
    QDomElement type = domDocument.createElement(QString("SDType"));
    root.appendChild(type);
    type.appendChild(domDocument.createTextNode(QString::number(MultimediaPersistent::getMultimediaType(DWT_SDDisk))));
    m_SDFileNamesXml = domDocument.toString();
//        qDebug() << "11m_SDFileNamesXml" << m_SDFileNamesXml;
}

void ImagePlayerPrivate::playListViewIndex(const DeviceWatcherType type, const int index)
{
    qDebug() << "ImagePlayerPrivate::playListViewIndex" << type << index;
    QList<QString> temp = getPathList(type);
    if ((temp.size() > index)
            && (QFile(temp.at(index))).exists()) {
        m_ElapsedTimer->stop();
        if (m_PlayTimer->isActive()) {
            m_PlayTimer->start();
        }
        m_DiskType = type;
#if 1
        m_RotateAngle = 0;
        m_Scale = 1.0f;
        m_PlayIndex = index;
        m_PlayStatus = IPPS_Start;
        m_CurrentPath = temp.at(index);
        emit m_Parent->onImagePlayerPlayStatus(m_PlayStatus);
        int percent = m_Scale * 100;
        emit m_Parent->onImagePlayerChange(m_DiskType, m_CurrentPath, m_PlayIndex, percent, m_RotateAngle);
        QFileInfo fileInfo(m_CurrentPath);
        qDebug() << "fileInfo.filePath()" << fileInfo.filePath();
        MultimediaPersistent::setImagePathInfo(m_DiskType, fileInfo.filePath() + QString("/") + fileInfo.created().toString(QString("yyyyMMddhhmmss")) + fileInfo.lastModified().toString(QString("yyyyMMddhhmmss")) + QString::number(fileInfo.size()));
        MultimediaPersistent::setMultimediaType(m_DiskType, MT_Image);
        m_ElapsedTimer->start();
#else
        m_ImageReader.setFileName(temp.at(index));
        if (m_ImageReader.canRead()) {
            if (m_AnimationTimer->isActive()) {
                m_AnimationTimer->stop();
            }
            m_RotateCount = 0;
            m_Scale = 1.0f;
            m_PlayIndex = index;
            if (m_ImageReader.supportsAnimation()
                    && (m_ImageReader.nextImageDelay() > 0)) {
                if (m_ImageReader.read(&m_Image)) {
                    m_PlayStatus = IPPS_Play;
                    emit m_Parent->onImagePlayerPlayStatus(m_PlayStatus);
                    QByteArray data(reinterpret_cast<const char *>(m_Image.bits()), m_Image.numBytes());
                    emit m_Parent->onImagePlayerChange(QFileInfo(temp.at(m_PlayIndex)).fileName(), m_Image.width(), m_Image.height(), m_Image.format(), data);
                    m_AnimationTimer->start(m_ImageReader.nextImageDelay() / 10);
                    if (m_PlayTimer->isActive()) {
                        m_PlayTimer->stop();
                        m_PlayTimer->start();
                    }
                }
            } else {
                if (m_ImageReader.read(&m_Image)) {
                    QByteArray data(reinterpret_cast<const char *>(m_Image.bits()), m_Image.byteCount());
                    if (m_PlayTimer->isActive()) {
                        m_PlayTimer->stop();
                        m_PlayTimer->start();
                        m_PlayStatus = IPPS_Play;
                    } else {
                        m_PlayStatus = IPPS_Pause;
                    }
                    emit m_Parent->onImagePlayerPlayStatus(m_PlayStatus);
                    emit m_Parent->onImagePlayerChange(QFileInfo(temp.at(m_PlayIndex)).fileName(), m_Image.width(), m_Image.height(), m_Image.format(), data);
                }
            }
        }
#endif
    }
}

void ImagePlayerPrivate::playPreviousListViewIndex()
{
    int lastIndex = m_PlayIndex;
    QList<QString> temp = getPathList(m_DiskType);
    if ((lastIndex > 0)
            && (lastIndex <= temp.size() - 1)) {
        --lastIndex;
    } else {
        lastIndex = temp.size() - 1;
    }
    qDebug() << "playPreviousListViewIndex" << m_PlayIndex << lastIndex;
    playListViewIndex(m_DiskType, lastIndex);
}

void ImagePlayerPrivate::playNextListViewIndex()
{
    m_RotateAngle = 0;
    int lastIndex = m_PlayIndex;
    QList<QString> temp = getPathList(m_DiskType);
    if (((lastIndex < (temp.size() - 1)))
            && (lastIndex >= 0)) {
        ++lastIndex;
    } else {
        lastIndex = 0;
    }
    playListViewIndex(m_DiskType, lastIndex);
}

void ImagePlayerPrivate::rotateImage()
{
    int step(90);
    if (((m_RotateAngle + step) < 360)
            && (m_RotateAngle >= 0)) {
        m_RotateAngle += step;
    } else {
        m_RotateAngle = 0;
    }
    int percent = m_Scale * 100;
    emit m_Parent->onImagePlayerChange(m_DiskType, m_CurrentPath, m_PlayIndex, percent, m_RotateAngle);
    //    QMatrix matrix;
    //    matrix.rotate(90 * m_RotateAngle);
    //    QImage image = m_Image.scaled(m_Image.width() * m_Scale, m_Image.height() * m_Scale, Qt::KeepAspectRatio).transformed(matrix, Qt::SmoothTransformation);
    //    emit m_Parent->onImagePlayerChange(QFileInfo(getPathList(m_DiskType).at(m_PlayIndex)).fileName(), image.width(), image.height(), image.format(), convertByteArray(image));
}

void ImagePlayerPrivate::zoomInImage()
{
    if (m_Scale > 1.0f) {
        m_Scale -= 0.25f;
    }
    int percent = m_Scale * 100;
    emit m_Parent->onImagePlayerChange(m_DiskType, m_CurrentPath, m_PlayIndex, percent, m_RotateAngle);
    //    QMatrix matrix;
    //    matrix.rotate(90 * m_RotateAngle);
    //    QImage image = m_Image.scaled(m_Image.width() * m_Scale, m_Image.height() * m_Scale, Qt::KeepAspectRatio).transformed(matrix, Qt::SmoothTransformation);
    //    emit m_Parent->onImagePlayerChange(QFileInfo(getPathList(m_DiskType).at(m_PlayIndex)).fileName(), image.width(), image.height(), image.format(), convertByteArray(image));
}

void ImagePlayerPrivate::zoomOutImage()
{
    if (m_Scale < 2.5f) {
        m_Scale += 0.25f;
    }
    int percent = m_Scale * 100;
    emit m_Parent->onImagePlayerChange(m_DiskType, m_CurrentPath, m_PlayIndex, percent, m_RotateAngle);
    //    QMatrix matrix;
    //    matrix.rotate(90 * m_RotateAngle);
    //    QImage image = m_Image.scaled(m_Image.width() * m_Scale, m_Image.height() * m_Scale, Qt::KeepAspectRatio).transformed(matrix, Qt::SmoothTransformation);
    //    emit m_Parent->onImagePlayerChange(QFileInfo(getPathList(m_DiskType).at(m_PlayIndex)).fileName(), image.width(), image.height(), image.format(), convertByteArray(image));
}

QByteArray &ImagePlayerPrivate::convertByteArray(const QImage &image)
{
    //    m_ByteArray.setRawData(reinterpret_cast<const char *>(image.bits()), image.byteCount());
    QByteArray byteArray;
    return  byteArray;
}

QList<QString> &ImagePlayerPrivate::getPathList(const DeviceWatcherType type)
{
    switch (type) {
    case DWT_SDDisk: {
        return m_SDPathList;
    }
    case DWT_USBDisk:
    default: {
        return m_USBPathList;
    }
    }
}

void ImagePlayerPrivate::exitImagePlayer()
{
    //    if (m_AnimationTimer->isActive()) {
    //        m_AnimationTimer->stop();
    //    }
    if (m_PlayTimer->isActive()) {
        m_PlayTimer->stop();
    }
}

void ImagePlayerPrivate::imagePlayerSetExit(const DeviceWatcherType type)
{
    qDebug() << "ImagePlayerPrivate::imagePlayerSetExit" << type << m_DiskType;
    if (type == m_DiskType) {
        exitImagePlayer();
        m_Parent->imagePlayerSetPlayStatus(IPPS_Exit);
    }
}

//void ImagePlayer::onAnimationTimerTimeout()
//{
//    if (m_Private->m_ImageReader.currentImageNumber() < m_Private->m_ImageReader.imageCount() - 1) {
//        if (m_Private->m_ImageReader.read(&m_Private->m_Image)) {
//            QMatrix matrix;
//            matrix.rotate(90 * m_Private->m_RotateAngle);
//            QImage image = m_Private->m_Image.scaled(m_Private->m_Image.width() * m_Private->m_Scale, m_Private->m_Image.height() * m_Private->m_Scale, Qt::KeepAspectRatio).transformed(matrix, Qt::SmoothTransformation);
//            emit onImagePlayerChange(QFileInfo(m_Private->getPathList(m_Private->m_DiskType).at(m_Private->m_PlayIndex)).fileName(), image.width(), image.height(), image.format(), m_Private->convertByteArray(image));
//        }
//    } else {
//        m_Private->m_ImageReader.setFileName(m_Private->m_ImageReader.fileName());
//        onAnimationTimerTimeout();
//    }
//}
