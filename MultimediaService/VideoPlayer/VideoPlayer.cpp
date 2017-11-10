#include "VideoPlayer.h"
#include "AutoConnect.h"
#include "Utility.h"
#include "MultimediaPersistent.h"
#include "UserInterfaceUtility.h"
#include <QList>
#include <QFileInfo>
#include <QDomDocument>

class VideoPlayerPrivate
{
    Q_DISABLE_COPY(VideoPlayerPrivate)
public:
    enum CommandType {
        CT_Undefine = -1,
        CT_PlayIndex = 0,
        CT_PlayNext = 1,
        CT_PlayPrevious = 2,
        CT_Pause = 3,
        CT_Seek = 4,
        CT_Toggle = 5,
    };
    explicit VideoPlayerPrivate(VideoPlayer *parent);
    ~VideoPlayerPrivate();
    void initialize();
    void connectAllSlots();
    //    bool requestAudioSource(const AudioSource source);
    //    void releaseAudioSource(const AudioSource source);
    void playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height, const int millesimal);
    void setPlayStatus(const VideoPlayerPlayStatus status);
    void pauseToggleHandler(const QString& output);
    void startHandler(const QString& output);
    void endTimePositionHandler(const QString &output);
    void millesimalHandler(const QString& output);
    void timePositionHandler(const QString &output);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void endOfFileHandler();
    void unsupportHandler();
    void seekToMillesimal(const int millesimal);
    void createSDFileNamesXml();
    void createUSBFileNamesXml();
    void videoPlayerSetPlay();
    void videoPlayerSetSuspend();
    void videoPlayerSetPause();
    void videoPlayerSetExit(const DeviceWatcherType type);
    void exitVideoPlayer();
    VideoPlayerShowStatus m_ShowStatus = VPSS_Normal;
    VideoPlayerPlayStatus m_PlayStatus = VPPS_Exit;
    QString m_SDFileNamesXml;
    QString m_USBFileNamesXml;
    QList<QString> m_SDPathList;
    QList<QString> m_USBPathList;
    QProcess* m_VideoPlayer = NULL;
    DeviceWatcherType m_DiskType = DWT_Undefine;
    int m_PlayIndex = -1;
    int m_ElapsedTime = -1;
    int m_Millesimal = 0;
    int m_EndTime = -1;
    int m_X = 0;
    int m_Y = 0;
    int m_Width = 800;
    int m_Height = 480;
    bool m_Suspend = false;
    QTimer* m_Timer = NULL;
    VideoPlayerPrivate::CommandType m_LastCommand = VideoPlayerPrivate::CT_Undefine;
private:
    VideoPlayer *m_Parent = NULL;
};

//static void releaseMusicSource(void* paramater)
//{
//    qDebug() << "VideoPlayerreleaseMusicSource" << paramater;
//    VideoPlayerPrivate* ptr = static_cast<VideoPlayerPrivate*>(paramater);
//    if (NULL != ptr) {
//        ptr->releaseAudioSource(AS_Video);
//    }
//}

//void VideoPlayer::releaseAudioSource(const AudioSource source)
//{
//    qDebug() << "VideoPlayer::releaseAudioSource" << source;
//    if (AS_Video == source) {
//        videoPlayerExit(m_Private->m_DiskType);
//        clearOwner();
//    }
//}

void VideoPlayer::videoPlayerRequestFileNames(const DeviceWatcherType type)
{
    switch (type) {
    case DWT_SDDisk: {
        emit onVideoPlayerFileNames(DWT_SDDisk, m_Private->m_SDFileNamesXml);
        break;
    }
    case DWT_USBDisk: {
        emit onVideoPlayerFileNames(DWT_USBDisk, m_Private->m_USBFileNamesXml);
        break;
    }
    default: {
        break;
    }
    }
}

void VideoPlayer::videoPlayerSetPlayStatusToggle()
{
    qDebug() << "VideoPlayer::videoPlayerSetPlayStatusToggle" << m_Private->m_PlayStatus;
    m_Private->m_Timer->stop();
    switch (m_Private->m_PlayStatus) {
    case VPPS_Play: {
        videoPlayerSetPlayStatus(VPPS_Pause);
        break;
    }
    case VPPS_Pause: {
        videoPlayerSetPlayStatus(VPPS_Play);
        break;
    }
    case VPPS_Stop: {
        videoPlayerSetPlayStatus(VPPS_Stop);
    }
    default: {
        break;
    }
    }
}

void VideoPlayer::videoPlayerSetShowStatus(const VideoPlayerShowStatus status)
{
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        if (status != m_Private->m_ShowStatus) {
            m_Private->m_ShowStatus = status;
            emit onVideoPlayerShowStatus(m_Private->m_ShowStatus);
        }
    }
}

void VideoPlayer::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "VideoPlayer::videoPlayerSetPlayStatus" << m_Private->m_VideoPlayer->state() << m_Private->m_PlayStatus << status;
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        if (VideoPlayerPrivate::CT_Undefine == m_Private->m_LastCommand) {
            m_Private->m_Timer->stop();
            switch (status) {
            case VPPS_Play: {
                m_Private->videoPlayerSetPlay();
                break;
            }
            case VPPS_Pause: {
                m_Private->videoPlayerSetPause();
                break;
            }
            case VPPS_SuspendToggle: {
                m_Private->videoPlayerSetSuspend();
                break;
            }
            case VPPS_Stop: {
                videoPlayerPlayListViewIndex(m_Private->m_DiskType, m_Private->m_PlayIndex, m_Private->m_X, m_Private->m_Y, m_Private->m_Width, m_Private->m_Height, 0);
                break;
            }
            default : {
                break;
            }
            }
        }
    }
}

void VideoPlayer::videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height, const int millesimal)
{
    if (VideoPlayerPrivate::CT_Undefine == m_Private->m_LastCommand) {
        m_Private->m_Timer->stop();
        m_Private->playVideoIndex(type, index, x, y, width, height, millesimal);
    }
}

void VideoPlayer::videoPlayerPlayPreviousListViewIndex()
{
    if (VideoPlayerPrivate::CT_Undefine == m_Private->m_LastCommand) {
        m_Private->m_Timer->stop();
        int lastIndex = m_Private->m_PlayIndex;
        QList<QString> temp = m_Private->getPathList(m_Private->m_DiskType);
        if ((lastIndex > 0)
                && (lastIndex <= temp.size() - 1)) {
            --lastIndex;
        } else {
            lastIndex = temp.size() - 1;
        }
        videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex, m_Private->m_X, m_Private->m_Y, m_Private->m_Width, m_Private->m_Height, 0);
    }
}

void VideoPlayer::videoPlayerPlayNextListViewIndex()
{
    if (VideoPlayerPrivate::CT_Undefine == m_Private->m_LastCommand) {
        m_Private->m_Timer->stop();
        int lastIndex = m_Private->m_PlayIndex;
        QList<QString> temp = m_Private->getPathList(m_Private->m_DiskType);
        if (((lastIndex < (temp.size() - 1)))
                && (lastIndex >= 0)) {
            ++lastIndex;
        } else {
            lastIndex = 0;
        }
        videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex, m_Private->m_X, m_Private->m_Y, m_Private->m_Width, m_Private->m_Height, 0);
    }
}

void VideoPlayer::videoPlayerSeekToMillesimal(const int millesimal)
{
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        if (VideoPlayerPrivate::CT_Undefine == m_Private->m_LastCommand) {
            m_Private->m_Timer->stop();
            m_Private->seekToMillesimal(millesimal);
        }
    }
}

void VideoPlayer::videoPlayerExit()
{
    qDebug() << "VideoPlayer::videoPlayerExit";
    m_Private->videoPlayerSetExit(m_Private->m_DiskType);
}

void VideoPlayer::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
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
            videoPlayerRequestFileNames(DWT_SDDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDPathList.clear();
            m_Private->videoPlayerSetExit(DWT_SDDisk);
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
            videoPlayerRequestFileNames(DWT_USBDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBPathList.clear();
            m_Private->videoPlayerSetExit(DWT_USBDisk);
        }
        default : {
            break;
        }
        }
    }
}

void VideoPlayer::onVideoFilePath(const QString &path, const DeviceWatcherType type)
{
    if (type == DWT_USBDisk) {
        m_Private->m_USBPathList.append(path);
    } else if (type == DWT_SDDisk) {
        m_Private->m_SDPathList.append(path);
    }
}

void VideoPlayer::onTimeout()
{
    m_Private->endOfFileHandler();
}

void VideoPlayer::onReadyReadStandardOutput()
{
    while (m_Private->m_VideoPlayer->canReadLine()) {
        QString output(m_Private->m_VideoPlayer->readLine());
//        if (output.contains("PRIVATECHANGE:")) {
        qWarning() << "VideoPlayeronReadyReadStandardOutput" << output;
//        } else
        /*if (output.contains("Starting playback...")) {
            m_Private->startHandler(output);
        } else */if (output.contains(QString("ANS_LENGTH="))) {
            m_Private->endTimePositionHandler(output);
        } else if (output.contains(QString("ANS_PERCENT_POSITION="))) {
            m_Private->millesimalHandler(output);
        } else if (output.contains(QString("ANS_TIME_POSITION="))) {
            m_Private->timePositionHandler(output);
        } else if (output.contains(QString("ANS_pause"))) {
            m_Private->pauseToggleHandler(output);
        } else if (output.contains(QString("EOF code: 1"))) {
//#ifndef gcc
//            system("echo 3 > /proc/sys/vm/drop_caches");
//#endif
            m_Private->setPlayStatus(VPPS_Stop);
            m_Private->m_Timer->start();
        } else if ((output.contains(QString("incorrect streams")))
                   || (output.contains(QString("No stream found")))) {
            m_Private->unsupportHandler();
            //            qDebug() << __FUNCTION__ << output;
        }/* else if (output.contains(QString("Exiting... (End of file)\n"))) {
            m_Private->endOfFileHandler();
        }*/
    }
}

void VideoPlayer::onStarted()
{
    qWarning() << "VideoPlayer::onStarted" << m_Private->m_VideoPlayer->state();
    //    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
    //        if (!m_Private->m_ElapsedTimer->isActive()) {
    //            m_Private->m_PlayStatus = VPPS_Start;
    //            emit onVideoPlayerPlayStatus(m_Private->m_PlayStatus);
    //            qDebug() << "emit m_Parent->onVideoPlayerPlayStatus" << m_Private->m_PlayStatus;
    //            emit onVideoPlayerElapsedInformation(0, 0);
    //            m_Private->m_ElapsedTimer->start();
    //        }
    //    }
}

void VideoPlayer::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qWarning() << "VideoPlayer::onFinished" << exitCode << exitStatus;
}

void VideoPlayer::onStateChanged(QProcess::ProcessState state)
{
    qWarning() << "VideoPlayer::onStateChanged" << state;
}

void VideoPlayer::onReadyReadStandardError()
{
    qWarning() << "VideoPlayer::onReadyReadStandardError";
}

void VideoPlayer::onError(QProcess::ProcessError error)
{
    qWarning() << "VideoPlayer::onError" << error << m_Private->m_VideoPlayer->error();
}

VideoPlayer::VideoPlayer(QObject *parent)
    : QObject(parent)
    , m_Private(new VideoPlayerPrivate(this))
{
}

VideoPlayer::~VideoPlayer()
{
}

VideoPlayerPrivate::VideoPlayerPrivate(VideoPlayer *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

VideoPlayerPrivate::~VideoPlayerPrivate()
{
    if (QProcess::NotRunning != m_VideoPlayer->state()) {
        m_VideoPlayer->write("pausing_keep_force  quit\n");
        m_VideoPlayer->waitForBytesWritten();
        m_VideoPlayer->waitForFinished();
    }
}

void VideoPlayerPrivate::initialize()
{
    m_VideoPlayer = new QProcess(m_Parent);
    m_VideoPlayer->setProcessChannelMode(QProcess::MergedChannels);
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(2000);
}

void VideoPlayerPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DeviceWatcher, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_VideoPlayer, SIGNAL(started()),
                     m_Parent,      SLOT(onStarted()),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(finished(int, QProcess::ExitStatus)),
                     m_Parent,      SLOT(onFinished(int, QProcess::ExitStatus)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(error(QProcess::ProcessError)),
                     m_Parent,      SLOT(onError(QProcess::ProcessError)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(stateChanged(QProcess::ProcessState)),
                     m_Parent,      SLOT(onStateChanged(QProcess::ProcessState)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(readyReadStandardOutput()),
                     m_Parent,      SLOT(onReadyReadStandardOutput()),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(readyReadStandardError()),
                     m_Parent,      SLOT(onReadyReadStandardError()),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

//bool VideoPlayerPrivate::requestAudioSource(const AudioSource source)
//{
//    qDebug() << "VideoPlayerPrivate::requestAudioSource" << source;
//    bool flag(true);
//    const HANDLER ptr = acquirePreemptiveResource(releaseMusicSource, static_cast<void*>(this));
//    if (releaseMusicSource != ptr) {
//        QDBusInterface interface(ArkMicroAudioService,
//                                 ArkMicroAudioPath,
//                                 ArkMicroAudioInterface,
//                                 QDBusConnection::sessionBus());
//        qDebug() << "interface.call";
//        QDBusReply<bool> reply = interface.call(ArkMicroAudioRequest,
//                                                source,
//                                                qApp->applicationName(),
//                                                ArkMicroMultimediaPath,
//                                                ArkMicroMultimediaInterface,
//                                                ArkMicroAudioRelease);
//        if (reply.isValid()) {
//            flag = reply.value();
//        } else {
//            qDebug() << "VideoPlayerPrivate::requestAudioSource fail!";
//            flag = false;
//        }
//    }
//    return flag;
//}

//void VideoPlayerPrivate::releaseAudioSource(const AudioSource source)
//{
//    qDebug() << "VideoPlayerPrivate::releaseAudioSource" << source;
//    m_Parent->releaseAudioSource(source);
//    QDBusInterface interface(ArkMicroAudioService,
//                             ArkMicroAudioPath,
//                             ArkMicroAudioInterface,
//                             QDBusConnection::sessionBus());
//    QDBusReply<void> reply = interface.call(ArkMicroAudioRelease,
//                                            source);
//    if (reply.isValid()) {
//        qDebug() << "VideoPlayerPrivate::releaseAudioSource ok!";
//    } else {
//        qDebug() << "VideoPlayerPrivate::releaseAudioSource fail!";
//    }
//}

//mplayer -slave -idle -quiet -geometry 1280x720+0+0 -vo customfb -ao alsa -tvout -ss 0
void VideoPlayerPrivate::playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height, const int millesimal)
{
    QList<QString> temp = getPathList(type);
    qDebug() << "playVideoIndex" << index << m_VideoPlayer->state() << temp.size();
    if ((VideoPlayerPrivate::CT_Undefine == m_LastCommand)
            && (temp.size() > index)
            && (QFile(temp.at(index))).exists()
            /*&& (requestAudioSource(AS_Video))*/) {
        m_DiskType = type;
        m_ElapsedTime = -1;
        m_EndTime = -1;
        m_PlayIndex = index;
        m_Suspend = false;
        m_Millesimal = millesimal;
        m_X = x;
        m_Y = y;
        m_Width = width;
        m_Height = height;
        if (QProcess::NotRunning == m_VideoPlayer->state()) {
            QString cmd = QString("mplayer");
            QStringList arguments;
//            arguments << QString("-debug");
//            arguments << QString("-framedrop");
//            arguments << QString("-hardframedrop");
            arguments << QString("-slave");
            arguments << QString("-idle");
            arguments << QString("-quiet");
            arguments << QString("-geometry");
            arguments << QString(QString::number(m_Width)
                                 + QString("x")
                                 + QString::number(m_Height)
                                 + QString("+")
                                 + QString::number(m_X)
                                 + QString("+")
                                 + QString::number(m_Y));
            arguments << QString("-vo");
#ifndef gcc
            arguments << QString("customfb");
#else
            arguments << QString("xv");
#endif
            arguments << QString("-ao");
            arguments << QString("alsa");
//            arguments << QString("-cache");
//            arguments << QString("8192");
//            arguments << QString("-autosync");
//            arguments << QString("30");
            if (!qgetenv("ARKTVOUT").isEmpty()) {
                arguments << QString("-tvout");
            }
//            arguments << QString("-idx");
//            arguments << QString("-v");
            if (0 != millesimal) {
                arguments << QString("-ss");
                arguments << QString::number(millesimal);
            }
            m_VideoPlayer->start(cmd, arguments);
            m_VideoPlayer->waitForStarted();
            qWarning() << cmd << arguments;
        }
        QString cmd1 = QString("loadfile \"") + temp.at(m_PlayIndex) + QString("\"\n");
        m_VideoPlayer->write(cmd1.toLocal8Bit().constData());
        m_VideoPlayer->waitForBytesWritten();
//        qWarning() << "startvideo" << m_VideoPlayer->state() << millesimal << cmd1;
        setPlayStatus(VPPS_Start);
//        qWarning() << "emit m_Parent->onVideoPlayerPlayStatus" << m_PlayStatus;
        emit m_Parent->onVideoPlayerElapsedInformation(0, 0);
        QFileInfo fileInfo(temp.at(m_PlayIndex));
        MultimediaPersistent::setVideoPathInfo(m_DiskType, fileInfo.filePath() + QString("/") + fileInfo.created().toString(QString("yyyyMMddhhmmss")) + fileInfo.lastModified().toString(QString("yyyyMMddhhmmss")) + QString::number(fileInfo.size()));
        MultimediaPersistent::setMultimediaType(m_DiskType, MT_Video);
        MultimediaPersistent::setVideoMillesmial(m_DiskType, millesimal);
    }
}

void VideoPlayerPrivate::setPlayStatus(const VideoPlayerPlayStatus status)
{
    if (status != m_PlayStatus) {
        m_PlayStatus = status;
    }
    emit m_Parent->onVideoPlayerPlayStatus(status);
}

void VideoPlayerPrivate::pauseToggleHandler(const QString &output)
{
    qDebug() << "VideoPlayeronReadyReadStandardOutput" << output;
    if (output.contains(QString("yes"))) {
        setPlayStatus(VPPS_Pause);
    } else if (output.contains(QString("no"))) {
        setPlayStatus(VPPS_Play);
        if (VideoPlayerPrivate::CT_Seek == m_LastCommand) {
//            m_LastCommand = VideoPlayerPrivate::CT_Undefine;
        }
    }
//    qWarning() << "drop_caches";
//    QFile file(QString("/proc/sys/vm/drop_caches"));
//    if (file.open(QIODevice::WriteOnly)) {
//        file.write("3");
//        file.flush();
//        file.close();
//    }
}

void VideoPlayerPrivate::startHandler(const QString &output)
{
    //    m_ElapsedTime = 0;
    //    if (-1 == m_EndTime) {
    //    m_VideoPlayer->write("pausing_keep_force get_time_length\n");
    //    m_VideoPlayer->waitForBytesWritten();
    //    }
    //    if (0 != m_Millesimal) {
    //        QString cmd("seek %1.%2% 1\n");
    //        cmd = cmd.arg(m_Millesimal / 10, 3, 10, QChar(' ')).arg(m_Millesimal % 10, 1, 10, QChar('0'));
    //        m_VideoPlayer->write(cmd.toLocal8Bit().constData());
    //        m_VideoPlayer->waitForBytesWritten();
    //    }
    //    m_PositionTimer->start();
}

void VideoPlayerPrivate::endTimePositionHandler(const QString &output)
{
    qDebug() << "VideoPlayerPrivate::endTimePositionHandler" << output;
    QString keyWord("ANS_LENGTH=");
    int startPos = output.indexOf(keyWord);
    int length = keyWord.length();
    QString endTime;
    endTime.clear();
    QList<QString> temp = getPathList(m_DiskType);
    if (temp.size() > m_PlayIndex) {
        m_EndTime = 0;
        if (-1 != startPos) {
            for (int i = 0; i < (output.length() - startPos); ++i) {
                if (QChar('\n') == output.at(startPos + length + i)) {
                    m_EndTime = static_cast<int>(endTime.toFloat());
//                    qDebug() << "m_EndTime" << m_EndTime;
                    break;
                }
                endTime += output.at(startPos + length + i);
            }
        }
        emit m_Parent->onVideoPlayerInformation(m_DiskType, m_PlayIndex, QFileInfo(temp.at(m_PlayIndex)).fileName(), m_EndTime);
        setPlayStatus(VPPS_Play);
//        qWarning() << "m_EndTime" << m_EndTime;
    } else {
        qCritical() << temp.size() << m_PlayIndex;
    }
}

void VideoPlayerPrivate::millesimalHandler(const QString &output)
{
    int start = output.indexOf(QChar('=')) + 1;
    int end = output.indexOf(QChar('\n'));
    if ((-1 != start)
            && (-1 != end)) {
        bool ok(false);
        int millesimal = static_cast<int>(output.mid(start, end - start).toFloat(&ok) * 1000);
        if (ok) {
            m_Millesimal = millesimal;
        }
    }
}

void VideoPlayerPrivate::timePositionHandler(const QString &output)
{
    if (output.startsWith(QString("ANS_TIME_POSITION="), Qt::CaseSensitive)) {
        int start = output.indexOf(QChar('=')) + 1;
        int end = output.indexOf(QChar('\n'));
        if ((-1 != start)
                && (-1 != end)) {
            bool ok = true;
            int elapsed = output.mid(start, end - start).toInt(&ok);
            if (ok) {
                if (((qAbs(m_ElapsedTime - elapsed) > 5))
                        || (elapsed % 5)) {
                    MultimediaPersistent::setVideoMillesmial(m_DiskType, elapsed);
//                    QFile file(QString("/proc/sys/vm/drop_caches"));
//                    if (file.open(QIODevice::WriteOnly)) {
//                        file.write("3");
//                        file.flush();
//                        file.close();
//                    }
//                    m_Parent->videoPlayerSeekToMillesimal(float(qrand() % 300) / m_EndTime * 1000);
                }
                m_ElapsedTime = elapsed;
                emit m_Parent->onVideoPlayerElapsedInformation(m_ElapsedTime, m_Millesimal);
                qDebug() << "m_ElapsedTime" << m_ElapsedTime << "m_Millesimal" << m_Millesimal;
#ifndef gcc
//                qWarning() << "drop_caches";
//                system("echo 3 > /proc/sys/vm/drop_caches");
#endif
            }
        }
    }
}

QList<QString> &VideoPlayerPrivate::getPathList(const int type)
{
    switch (type) {
    case DWT_SDDisk: {
        return m_SDPathList;
        break;
    }
    case DWT_USBDisk:
    default: {
        return m_USBPathList;
        break;
    }
    }
}

void VideoPlayerPrivate::endOfFileHandler()
{
    switch (m_PlayStatus) {
    case VPPS_Start:
    case VPPS_Unsupport:
    case VPPS_Pause:
    case VPPS_Stop:
    case VPPS_Play: {
        if ((getPathList(m_DiskType).size() - 1) > m_PlayIndex) {
            ++m_PlayIndex;
        } else {
            m_PlayIndex = 0;
        }
        playVideoIndex(m_DiskType, m_PlayIndex, m_X, m_Y, m_Width, m_Height, 0);
        break;
    }
    default: {
        break;
    }
    }
}

void VideoPlayerPrivate::unsupportHandler()
{
    QList<QString> temp = getPathList(m_DiskType);
    if (m_PlayIndex < temp.size()) {
        m_EndTime = 0;
        emit m_Parent->onVideoPlayerInformation(m_DiskType, m_PlayIndex, QFileInfo(temp.at(m_PlayIndex)).fileName(), m_EndTime);
        setPlayStatus(VPPS_Unsupport);
        m_Timer->start();
    }
}

void VideoPlayerPrivate::seekToMillesimal(const int millesimal)
{
    qDebug() << "seekToMillesimal" << millesimal / 10 << millesimal % 10;
    if ((VPPS_Pause == m_PlayStatus)
            || (VPPS_Play == m_PlayStatus)) {
        QString cmd("seek %1.%2 1\n");
        cmd = cmd.arg(millesimal / 10, 3, 10, QChar(' ')).arg(millesimal % 10, 1, 10, QChar('0'));
        m_VideoPlayer->write(cmd.toLocal8Bit().constData());
        m_VideoPlayer->waitForBytesWritten();
//        m_LastCommand = VideoPlayerPrivate::CT_Seek;
    } else {
        playVideoIndex(m_DiskType, m_PlayIndex, m_X, m_Y, m_Width, m_Height, 0);
    }
}

void VideoPlayerPrivate::createSDFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("VideoPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("VideoPlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("SDFileNames"));
    root.appendChild(fileNames);
    m_SDFileNamesXml.clear();
    QString sdPersistantPathInfo = MultimediaPersistent::getVideoPathInfo(DWT_SDDisk);
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
    QString data("");
    if (!persistantIndex.isEmpty()) {
        data = persistantIndex + QString("-") + QString::number(MultimediaPersistent::getVideoMillesmial(DWT_SDDisk));
    }
    persistant.appendChild(domDocument.createTextNode(data));
    QDomElement type = domDocument.createElement(QString("SDType"));
    root.appendChild(type);
    type.appendChild(domDocument.createTextNode(QString::number(MultimediaPersistent::getMultimediaType(DWT_SDDisk))));
    m_SDFileNamesXml = domDocument.toString();
    //    qDebug() << "asdsad m_SDFileNamesXml" << m_SDFileNamesXml;
}

void VideoPlayerPrivate::createUSBFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("VideoPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("VideoPlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("USBFileNames"));
    root.appendChild(fileNames);
    m_USBFileNamesXml.clear();
    QString usbPersistantPathInfo = MultimediaPersistent::getVideoPathInfo(DWT_USBDisk);
    QStringList stringList = usbPersistantPathInfo.split(QChar('/'));
    QString usbPersistantPath = usbPersistantPathInfo.left(usbPersistantPathInfo.length() - stringList.last().length() - 1);
    qDebug() << "usbPersistantPath" << usbPersistantPath << usbPersistantPathInfo;
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
    QString data("");
    if (!persistantIndex.isEmpty()) {
        data = persistantIndex + QString("-") + QString::number(MultimediaPersistent::getVideoMillesmial(DWT_USBDisk));
    }
    persistant.appendChild(domDocument.createTextNode(data));
    QDomElement type = domDocument.createElement(QString("USBType"));
    root.appendChild(type);
    type.appendChild(domDocument.createTextNode(QString::number(MultimediaPersistent::getMultimediaType(DWT_USBDisk))));
    m_USBFileNamesXml = domDocument.toString();
    //    qDebug() << "asdasdasdsad" << m_USBFileNamesXml;
}

void VideoPlayerPrivate::videoPlayerSetPlay()
{
    switch (m_PlayStatus) {
    case VPPS_Play: {
        break;
    }
    case VPPS_Pause: {
        m_VideoPlayer->write("u\n");
        m_VideoPlayer->waitForBytesWritten();
        //        m_VideoPlayer->write("pausing_keep_force get_property pause\n");
        //        m_VideoPlayer->waitForBytesWritten();
        break;
    }
    default: {
        return;
        break;
    }
    }
}

void VideoPlayerPrivate::videoPlayerSetSuspend()
{
    qWarning() << "VideoPlayerPrivate::videoPlayerSetSuspend" << m_Suspend << m_PlayStatus;
    if (m_Suspend) {
        m_Suspend = false;
        videoPlayerSetPlay();
    } else {
        if ((VPPS_Play == m_PlayStatus)) {
            m_Suspend = true;
            videoPlayerSetPause();
        } else if (VPPS_Pause == m_PlayStatus) {
            m_VideoPlayer->write("pausing_keep_force pause\n");
            m_VideoPlayer->waitForBytesWritten();
        }
    }
}

void VideoPlayerPrivate::videoPlayerSetPause()
{
    qDebug() << "VideoPlayerPrivate::videoPlayerSetPause" << m_PlayStatus;
    switch (m_PlayStatus) {
    case VPPS_Play: {
        m_VideoPlayer->write("pausing_keep_force pause\n");
        m_VideoPlayer->waitForBytesWritten();
        //m_VideoPlayer->write("pausing_keep_force get_property pause\n");
        //m_VideoPlayer->waitForBytesWritten();
        break;
    }
    case VPPS_Pause: {
        break;
    }
    default: {
        return;
        break;
    }
    }
}

void VideoPlayerPrivate::videoPlayerSetExit(const DeviceWatcherType type)
{
    qDebug() << "VideoPlayerPrivate::videoPlayerSetExit" << type << m_DiskType;
    if (type == m_DiskType) {
        exitVideoPlayer();
    }
}

void VideoPlayerPrivate::exitVideoPlayer()
{
    qDebug() << "exitVideoPlayer" << m_VideoPlayer->state();
//    VideoPlayerPlayStatus status = VPPS_Stop;
    if (QProcess::NotRunning != m_VideoPlayer->state()) {
        m_VideoPlayer->write("quit\n");
        m_VideoPlayer->waitForBytesWritten();
        m_VideoPlayer->waitForFinished();
//        status = VPPS_Exit;
    }
    //quitHandler();
    setPlayStatus(VPPS_Exit);
}
