#include "Link.h"
#include "Widget.h"
#include "MirrorLinkProxy.h"
#include "CarplayLinkProxy.h"
#include "CarlifeLinkProxy.h"
#include "Utility.h"
#include "AutoConnect.h"
#include "AudioService.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"
#include "BT.h"
#include "RunnableThread.h"
#include "Audio.h"

#define ArkMicroMirrorService         QString("com.arkmicro.mirror")
#define ArkMicroMirrorPath            QString("/com/arkmicro/mirror")
#define ArkMicroMirrorInterface       QString("Local.DbusServer.Mirror")
#define ArkMicroCarplayService        QString("com.arkmicro.carplay")
#define ArkMicroCarplayPath           QString("/com/arkmicro/carplay")
#define ArkMicroCarplayInterface      QString("Local.DbusServer.Carplay")
#define ArkMicroCarlifeService        QString("com.arkmicro.carlife")
#define ArkMicroCarlifePath           QString("/com/arkmicro/carlife")
#define ArkMicroCarlifeInterface      QString("Local.DbusServer.Carlife")

class LinkPrivate
{
public:
    explicit LinkPrivate(Link *parent);
    ~LinkPrivate();
    void initialize();
    void connectAllSlots();
    void linkExit(const AudioSource source);
    void requestMirrorHandler(const Link_STATUS status);
    void requestCarlifeHandler(const Link_STATUS status);
    void requestCarplayHandler(const Link_STATUS status);
    void mirrorSourceHandler(const Link_STATUS status);
    void carplaySourceHandler(const Link_STATUS status);
    void carlifeSourceHandler(const Link_STATUS status);
    HANDLER m_Callback = NULL;
    Local::DbusServer::Mirror* m_MirrorLinkProxy = NULL;
    Local::DbusServer::Carplay* m_CarplayLinkProxy = NULL;
	Local::DbusServer::Carlife* m_CarlifeLinkProxy = NULL;
private:
    Link* m_Parent = NULL;
};

static void releaseMirrorSource(void* paramater)
{
    qWarning() << "releaseMirrorSource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Mirror);
    }
}

static void releaseCarplaySource(void* paramater)
{
    qWarning() << "releaseCarplaySource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Carplay);
    }
}

static void releaseCarlifeSource(void* paramater)
{
    qWarning() << "releaseCarlifeSource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Carlife);
    }
}

static void requestSourceCallback(void* parameter)
{
    qWarning() << "requestSourceCallback" << QThread::currentThread();
    int* ptr = (int*)parameter;
    if (NULL != ptr) {
        QDBusInterface interface(ArkMicroAudioService,
                                 ArkMicroAudioPath,
                                 ArkMicroAudioInterface,
                                 QDBusConnection::sessionBus());
        QDBusReply<void> reply = interface.call(ArkMicroAudioRequest, *ptr);
        if (reply.isValid()) {
            qWarning() << "requestSourceCallbakc::requestAudioSource ok!";
        } else {
            qWarning() << "requestSourceCallbakc::requestAudioSource fail!";
        }
        delete ptr;
        ptr = NULL;
    }
}

static void releaseSourceCallback(void* parameter)
{
    qWarning() << "releaseSourceCallback" << QThread::currentThread();
    QDBusInterface interface(ArkMicroAudioService,
                             ArkMicroAudioPath,
                             ArkMicroAudioInterface,
                             QDBusConnection::sessionBus());
    if (NULL != parameter) {
        int* ptr = (int*)parameter;
        QDBusReply<void> reply = interface.call(ArkMicroAudioRelease, *ptr);
        if (reply.isValid()) {
            qWarning() << "requestSourceCallbakc::ArkMicroAudioRelease ok!";
        } else {
            qWarning() << "requestSourceCallbakc::ArkMicroAudioRelease fail!";
        }
        delete ptr;
        ptr = NULL;
    }
}

void Link::requestLinkStatus(const Link_Type type, const Link_STATUS status)
{
    qWarning() << "requestLinkStatus" << type << status;
    initializePrivate();
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->requestMirrorHandler(status);
        break;
    }
    case CARPLAY: {
        m_Private->requestCarplayHandler(status);
        break;
    }
    case CARLIFE: {
        m_Private->requestCarlifeHandler(status);
        break;
    }
    default: {
        qWarning() << "unsupport command:" << type << status;
    }
    }
}

void Link::requestTouchStatus(const Link_Type deviceType, const TouchType touchType, const QString &touchPointXml)
{
    qWarning() << "Link::requestTouchStatus" << deviceType << touchType << touchPointXml;
    initializePrivate();
    switch (deviceType) {
    case ANDROID_MIRROR: {
        QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qWarning() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    case CARPLAY: {
        QDBusPendingReply<> reply = m_Private->m_CarplayLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qWarning() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    case CARLIFE: {
        QDBusPendingReply<> reply = m_Private->m_CarlifeLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qWarning() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    default: {
        break;
    }
    }
}

void Link::requestKeyValue(const LinkKeyValue type)
{
    qWarning() << "Link::requestKeyValue" << type;
    initializePrivate();
    QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestKeyValue(type);
    reply.waitForFinished();
    qWarning() << "requestKeyValue" << reply.isFinished();
    if (reply.isError()) {
        qWarning() << "method call requestKeyValue failed" << reply.error();
    }
}

//void Link::releaseAudioSource(const int source)
//{
//    qWarning() << "Link::releaseAudioSource";
//}

void Link::onServiceRegistered(const QString &service)
{
    qWarning() << "Link::onServiceRegistered" << service;
}

void Link::onServiceUnregistered(const QString &service)
{
    qWarning() << "Link::onServiceUnregistered" << service;
    if (ArkMicroMirrorService == service) {
        UserInterfaceUtility::elapsed(QString("Attach ArkMicroMirrorService<<<<<<"));
        g_DbusService->startService(ArkMicroMirrorService);
        UserInterfaceUtility::elapsed(QString("Attach ArkMicroMirrorService>>>>"));
        //        QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_START_PROCESS);
    } else if (ArkMicroCarplayService == service) {
        g_DbusService->startService(ArkMicroCarplayService);
        //        QDBusPendingReply<> reply = m_Private->m_CarplayLinkProxy->requestLinkStatus(CARPLAY, LINK_START_PROCESS);
    }else if (ArkMicroCarlifeService == service) {
        g_DbusService->startService(ArkMicroCarlifeService);

    }
}

void Link::linkStatusChange(const int type, const int status)
{
    qWarning() << "Link::linkStatusChange" << type << status;
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->mirrorSourceHandler(status);
        break;
    }
    case CARPLAY: {
        m_Private->carplaySourceHandler(status);
        break;
    }
    case CARLIFE: {
        m_Private->carlifeSourceHandler(status);
        break;
    }

    default: {
        break;
    }
    }
}

Link::Link(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    g_DbusService->addWatchedService(ArkMicroMirrorService);
    connectSignalAndSlotByNamesake(g_DbusService, this);
}

Link::~Link()
{
}

void Link::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new LinkPrivate(this));
    }
}

LinkPrivate::LinkPrivate(Link *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

LinkPrivate::~LinkPrivate()
{
}

void LinkPrivate::initialize()
{
    if (NULL == m_MirrorLinkProxy) {
        m_MirrorLinkProxy = new Local::DbusServer::Mirror(ArkMicroMirrorService,
                                                          ArkMicroMirrorPath,
                                                          QDBusConnection::sessionBus(),
                                                          m_Parent);
    }
    if (NULL == m_CarplayLinkProxy) {
        m_CarplayLinkProxy = new Local::DbusServer::Carplay(ArkMicroCarplayService,
                                                            ArkMicroCarplayPath,
                                                            QDBusConnection::sessionBus(),
                                                            m_Parent);
    }
    if (NULL == m_CarlifeLinkProxy) {
        m_CarlifeLinkProxy = new Local::DbusServer::Carlife(ArkMicroCarlifeService,
                                                            ArkMicroCarlifePath,
                                                            QDBusConnection::sessionBus(),
                                                            m_Parent);
    }
}

void LinkPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DbusService, m_Parent);
    if (NULL != m_MirrorLinkProxy) {
        connectSignalAndSignalByNamesake(m_MirrorLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_MirrorLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,          SLOT(linkStatusChange(int, int)),
                         type);
    }
    if (NULL != m_CarplayLinkProxy) {
        connectSignalAndSignalByNamesake(m_CarplayLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_CarplayLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,           SLOT(linkStatusChange(int, int)),
                         type);
    }
    if (NULL != m_CarlifeLinkProxy) {
        connectSignalAndSignalByNamesake(m_CarlifeLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_CarlifeLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,           SLOT(linkStatusChange(int, int)),
                         type);
    }
}

void LinkPrivate::linkExit(const AudioSource source)
{
    qWarning() << "LinkPrivate::linkExit" << source << m_Callback;
    qWarning() << "releaseMirrorSource == m_Callback" << (releaseMirrorSource == m_Callback);
    qWarning() << "releaseCarplaySource == m_Callback" << (releaseCarplaySource == m_Callback);
    qWarning() << "releaseCarlifeSource == m_Callback" << (releaseCarlifeSource == m_Callback);
    qWarning() << "NULL == m_Callback" << (NULL == m_Callback);
    switch (source) {
    case AS_Mirror: {
        if (releaseMirrorSource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_EXITED);
        }
        break;
    }
    case AS_Carplay: {
        if (releaseCarplaySource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(CARPLAY, LINK_EXITED);
        }
        break;
    }
    case AS_Carlife: {
        if (releaseCarlifeSource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(CARLIFE, LINK_EXITED);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void LinkPrivate::requestMirrorHandler(const Link_STATUS status)
{
    qWarning() << "requestMirrorHandler" << status;
    QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, status);
    //    switch (status) {
    //    case LINK_STARTING: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_STARTING);
    //        break;
    //    }
    //    case LINK_EXITING: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_EXITING);
    //        break;
    //    }
    //    case LINK_EXITED: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_EXITED);
    //        break;
    //    }
    //    default: {
    //        break;
    //    }
    //    }
}
void LinkPrivate::requestCarlifeHandler(const Link_STATUS status)
{
    qWarning() << "requestCarlifeHandler" << status;
    QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, status);
//    switch (status) {
//    case LINK_STARTING: {
//        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_STARTING);
//        break;
//    }
//    case LINK_EXITING: {
//        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_EXITING);
//        break;
//    }
//    case LINK_EXITED: {
//        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_EXITED);
//        break;
//    }
//    default: {
//        break;
//    }
//    }
}

void LinkPrivate::requestCarplayHandler(const Link_STATUS status)
{
    QDBusPendingReply<> reply = m_CarplayLinkProxy->requestLinkStatus(CARPLAY, status);
    //    switch (status) {
    //    case LINK_STARTING: {
    //        QDBusPendingReply<> reply = m_CarplayLinkProxy->requestLinkStatus(CARPLAY, LINK_STARTING);
    //        break;
    //    }
    //    default: {
    //        break;
    //    }
    //    }
}

static void mirrorStarting(void* parameter)
{
    int* type = new int(AS_Idle);
    requestSourceCallback(static_cast<void*>(type));
    qWarning() << "mirrorStarting" << QThread::currentThread();
    QDBusInterface interface(ArkMicroBluetoothService,
                             ArkMicroBluetoothPath,
                             ArkMicroBluetoothInterface,
                             QDBusConnection::sessionBus());
    QDBusReply<void> reply = interface.call(QString("synchronize"));
    if (reply.isValid()) {
        qWarning() << "mirrorStarting::synchronize ok!";
    } else {
        qWarning() << "mirrorStarting::synchronize fail!";
    }
}

void LinkPrivate::mirrorSourceHandler(const Link_STATUS status)
{
    qWarning() << " LinkPrivate::mirrorSourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
        if (NULL != ptr) {
            g_Audio->requestAudioSource(AS_Idle);
        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(mirrorStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseMirrorSource, static_cast<void*>(this));
        if (releaseMirrorSource != ptr) {
            m_Callback = releaseMirrorSource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Mirror);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseMirrorSource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Mirror);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}

static void carplayStarting(void* parameter)
{
    int* type = new int(AS_Idle);
    requestSourceCallback(static_cast<void*>(type));
}

void LinkPrivate::carplaySourceHandler(const Link_STATUS status)
{
    qWarning() << " LinkPrivate::carplaySourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
        if (NULL != ptr) {
            g_Audio->requestAudioSource(AS_Idle);
        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(carplayStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseCarplaySource, static_cast<void*>(this));
        if (releaseCarplaySource != ptr) {
            m_Callback = releaseCarplaySource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carplay);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseCarplaySource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carplay);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}
static void carlifeStarting(void* parameter)
{
    int* type = new int(AS_Idle);
    requestSourceCallback(static_cast<void*>(type));
}

void LinkPrivate::carlifeSourceHandler(const Link_STATUS status)
{
    qWarning() << " LinkPrivate::carlifeSourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
        if (NULL != ptr) {
            g_Audio->requestAudioSource(AS_Idle);
        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(carlifeStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseCarlifeSource, static_cast<void*>(this));
        if (releaseCarlifeSource != ptr) {
            m_Callback = releaseCarlifeSource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carlife);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseCarlifeSource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carlife);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}

