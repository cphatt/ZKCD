#include "Multimedia.h"
#include "BusinessLogicUtility.h"
#include "Widget.h"
#include "ArkApplication.h"
#include "MultimediaService.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include "AudioService.h"
#include "Utility.h"
#include "Audio.h"
#include "UserInterfaceUtility.h"
#include <QProcess>
#include <QFile>
#include <unistd.h>

class MultimediaPrivate
{
    Q_DISABLE_COPY(MultimediaPrivate)
public:
    explicit MultimediaPrivate(Multimedia* parent);
    ~MultimediaPrivate();
    void initializeProxy();
    bool requestAudioSource(const AudioSource source);
    void releaseAudioSource(const AudioSource source);
    void multimediaExit(const AudioSource source);
    void connectAllSlots();
    HANDLER m_Callback = NULL;
    Local::DbusServer::Multimedia* m_MultimediaServiceProxy = NULL;
private:
    Multimedia* m_Parent = NULL;
};

static void releaseMusicSource(void* paramater)
{
    qDebug() << "releaseMusicSource" << paramater;
    MultimediaPrivate* ptr = static_cast<MultimediaPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->multimediaExit(AS_Music);
    }
}

static void releaseIdleSource(void* paramater)
{
    qDebug() << "releaseIdleSource" << paramater;
    MultimediaPrivate* ptr = static_cast<MultimediaPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->multimediaExit(AS_Idle);
    }
}

static void releaseVideoSource(void* paramater)
{
    qDebug() << "releaseVideoSource" << paramater;
    MultimediaPrivate* ptr = static_cast<MultimediaPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->multimediaExit(AS_Video);
    }
}

void Multimedia::reset()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->reset();
    }
}

void Multimedia::deviceWatcherCheckStatus(const int type)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->deviceWatcherCheckStatus(type);
    }
}

void Multimedia::musicPlayerRequestFileNames()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerRequestFileNames();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayModeToggle()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayModeToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayModeToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayModeToggle failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayMode(const int mode)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayMode(mode);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayMode" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayMode failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayStatusToggle()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayStatusToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayStatusToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayStatusToggle failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayStatus(const int status)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayStatus failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayListViewIndex(const int type, const int index, const int millesimal)
{
    initializePrivate();
    m_Private->requestAudioSource(AS_Music);
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayListViewIndex(type, index, millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayPreviousListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayPreviousListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayPreviousListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayNextListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSeekToMillesimal(const int millesimal)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSeekToMillesimal(millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSeekToMillesimal" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSeekToMillesimal failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerExit()
{
    qDebug() << "Multimedia::musicPlayerExit";
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerExit();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerExit" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerExit failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerRequestFileNames(const int type)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerRequestFileNames(type);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayListViewIndex(const int type, const int index)
{
    initializePrivate();
    m_Private->requestAudioSource(AS_Idle);
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayListViewIndex(type, index);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayPreviousListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayNextListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerRotateImage()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerRotateImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerRotateImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerRotateImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerZoomInImage()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerZoomInImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerZoomInImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerZoomInImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerZoomOutImage()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerZoomOutImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerZoomOutImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerZoomOutImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerSetPlayStatusToggle()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->imagePlayerSetPlayStatusToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerSetPlayStatusToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerSetPlayStatusToggle failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerSetPlayStatus(const int status)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->imagePlayerSetPlayStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerSetPlayStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerSetPlayStatus failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerExit()
{
    qDebug() << "Multimedia::imagePlayerExit";
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->imagePlayerExit();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerExit" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerExit failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerRequestFileNames(const DeviceWatcherType type)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerRequestFileNames(type);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetPlayStatusToggle()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetPlayStatusToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetPlayStatusToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetPlayStatusToggle failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetShowStatus(const VideoPlayerShowStatus status)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetShowStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetShowStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetShowStatus failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetPlayStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetPlayStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetPlayStatus failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height, const int millesimal)
{
    initializePrivate();
    m_Private->requestAudioSource(AS_Video);
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayListViewIndex(type, index, x, y, width, height, millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayPreviousListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayPreviousListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayPreviousListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayNextListViewIndex()
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSeekToMillesimal(const int millesimal)
{
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSeekToMillesimal(millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSeekToMillesimal" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSeekToMillesimal failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerExit()
{
    qDebug() << "Multimedia::videoPlayerExit";
    initializePrivate();
    if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->videoPlayerExit();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerExit" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerExit failed" << reply.error();
        }
    }
}

void Multimedia::onServiceRegistered(const QString &service)
{
    qDebug() << "Multimedia::onServiceRegistered" << service;
    //    if (ArkMicroMultimediaService == service) {
    //        if (NULL != m_Private->m_MultimediaService) {
    //            m_Private->m_MultimediaService->synchronize();
    //        } else if (NULL != m_Private->m_MultimediaServiceProxy) {
    //            QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->synchronize();
    //            reply.waitForFinished();
    //            qDebug() << "Dbus call Multimedia::setLanguage" << reply.isFinished();
    //            if (reply.isError()) {
    //                qDebug() << "method call Multimedia::setLanguage failed" << reply.error();
    //            }
    //        }
    //    }
}

void Multimedia::onServiceUnregistered(const QString &service)
{
    qDebug() << "Multimedia::onServiceUnregistered" << service;
    if (ArkMicroMultimediaService == service) {
        UserInterfaceUtility::elapsed(QString("<<<<<<<<<<<"));
        g_DbusService->startService(ArkMicroMultimediaService);
        UserInterfaceUtility::elapsed(QString(">>>>>>>>>>>>>>>>>>>>"));
    }
}

void Multimedia::onMusicPlayerPlayStatusHandler(const MusicPlayerPlayStatus status)
{
    qDebug() << "Multimedia::onMusicPlayerPlayStatusHandler";
    if (MPPS_Exit == status) {
        qDebug() << "MPPS_Exit == status";
        if (releaseMusicSource == m_Private->m_Callback) {
            m_Private->releaseAudioSource(AS_Music);
        }
    }
}

void Multimedia::onImagePlayerPlayStatusHandler(const ImagePlayerPlayStatus status)
{
    qDebug() << "Multimedia::onImagePlayerPlayStatusHandler";
    if (IPPS_Exit == status) {
        qDebug() << "IPPS_Exit == status";
        if (releaseIdleSource == m_Private->m_Callback) {
            m_Private->releaseAudioSource(AS_Idle);
        }
    }
}

void Multimedia::onVideoPlayerPlayStatusHandler(const VideoPlayerPlayStatus status)
{
    qDebug() << "Multimedia::onVideoPlayerPlayStatusHandler";
    if (VPPS_Exit == status) {
        qDebug() << "VPPS_Exit == status";
        if (releaseVideoSource == m_Private->m_Callback) {
            m_Private->releaseAudioSource(AS_Video);
        }
    }
}

Multimedia::Multimedia(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    g_DbusService->addWatchedService(ArkMicroMultimediaService);
    connectSignalAndSlotByNamesake(g_DbusService, this);
    initializePrivate();
}

Multimedia::~Multimedia()
{

}

void Multimedia::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new MultimediaPrivate(this));
    }
}

MultimediaPrivate::MultimediaPrivate(Multimedia *parent)
    : m_Parent(parent)
{
    initializeProxy();
    connectAllSlots();
}

MultimediaPrivate::~MultimediaPrivate()
{
}

void MultimediaPrivate::initializeProxy()
{
    if (NULL == m_MultimediaServiceProxy) {
        m_MultimediaServiceProxy = new Local::DbusServer::Multimedia(ArkMicroMultimediaService,
                                                                     ArkMicroMultimediaPath,
                                                                     QDBusConnection::sessionBus(),
                                                                     qApp);
    }
}

bool MultimediaPrivate::requestAudioSource(const AudioSource source)
{
    qDebug() << "MusicPlayerPrivate::requestAudioSource" << source;
    bool flag(true);
    HANDLER callback(NULL);
    switch (source) {
    case AS_Music: {
        callback = releaseMusicSource;
        break;
    }
    case AS_Video: {
        callback = releaseVideoSource;
        break;
    }
    case AS_Idle:
    default: {
        callback = releaseIdleSource;
        break;
    }
    }
    const HANDLER ptr = acquirePreemptiveResource(callback, static_cast<void*>(this));
    qDebug() << "callback != ptr" << (m_Callback != ptr);
    if (callback != ptr) {
        m_Callback = callback;
        flag = g_Audio->requestAudioSource(source);
    }
    return flag;
}

void MultimediaPrivate::releaseAudioSource(const AudioSource source)
{
    qDebug() << "MusicPlayerPrivate::releaseAudioSource" << source;
    clearOwner();
    g_Audio->releaseAudioSource(source);
}

void MultimediaPrivate::multimediaExit(const AudioSource source)
{
    qDebug() << "MultimediaPrivate::multimediaExit" << source;
    switch (source) {
    case AS_Music: {
        m_Parent->musicPlayerExit();
        m_Callback = NULL;
        break;
    }
    case AS_Video: {
        m_Parent->videoPlayerExit();
        m_Callback = NULL;
        break;
    }
    case AS_Idle: {
        m_Parent->imagePlayerExit();
        m_Callback = NULL;
        break;
    }
    default: {
        break;
    }
    }
}

void MultimediaPrivate::connectAllSlots()
{
    if (NULL != m_MultimediaServiceProxy) {
        connectSignalAndSignalByNamesake(m_MultimediaServiceProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_MultimediaServiceProxy, SIGNAL(onMusicPlayerPlayStatus(int)),
                         m_Parent,                 SLOT(onMusicPlayerPlayStatusHandler(int)),
                         type);
        QObject::connect(m_MultimediaServiceProxy, SIGNAL(onImagePlayerPlayStatus(int)),
                         m_Parent,                 SLOT(onImagePlayerPlayStatusHandler(int)),
                         type);
        QObject::connect(m_MultimediaServiceProxy, SIGNAL(onVideoPlayerPlayStatus(int)),
                         m_Parent,                 SLOT(onVideoPlayerPlayStatusHandler(int)),
                         type);
    }
}
