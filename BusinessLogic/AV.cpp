#include "AV.h"
#include "AutoConnect.h"
#include "Audio.h"
#include "Utility.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"

class AVPrivate
{
public:
    explicit AVPrivate(AV* parent);
    ~AVPrivate();
    void initialize();
    void connectAllSlots();
    bool requestAudioSource(const AudioSource source);
    void releaseAudioSource(const AudioSource source);
    void avExit(const AudioSource source);
    HANDLER m_Callback = NULL;
private:
    AV* m_Parent = NULL;
};

static void releaseAV1Source(void* paramater)
{
    qDebug() << "releaseAV1Source" << paramater;
    AVPrivate* ptr = static_cast<AVPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->avExit(AS_AV1);
    }
}

static void releaseAV2Source(void* paramater)
{
    qDebug() << "releaseAV2Source" << paramater;
    AVPrivate* ptr = static_cast<AVPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->avExit(AS_AV2);
    }
}

void AV::startAV(const AVType type, const int width, const int height)
{
    initializePrivate();
    g_Setting->startAV(type, width, height);
}

void AV::stopAV(const AVType type)
{
    initializePrivate();
    if (AVT_1 == type) {
        m_Private->releaseAudioSource(AS_AV1);
    } else if (AVT_2 == type) {
        m_Private->releaseAudioSource(AS_AV2);
    } else {
        return ;
    }
    g_Setting->stopAV(type);
}

void AV::onAVStatusHandler(const AVType type, const AVStatus status)
{
    qDebug() << " AV::onAVStatusHandler" << type << status;
    if (AVS_Detacted == status) {
        m_Private->requestAudioSource(AS_Idle);
    } else if (AVS_Play == status) {
        switch (type) {
        case AVT_1: {
            m_Private->requestAudioSource(AS_AV1);
            break;
        }
        case AVT_2: {
            m_Private->requestAudioSource(AS_AV2);
            break;
        }
        default: {
            break;
        }
        }
    } else if (AVS_NoDetact == status) {
        switch (type) {
        case AVT_1: {
            m_Private->releaseAudioSource(AS_AV1);
            break;
        }
        case AVT_2: {
            m_Private->releaseAudioSource(AS_AV2);
            break;
        }
        default: {
            break;
        }
        }
    }
}

AV::AV(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    qDebug() << "AV::AV";
}

AV::~AV()
{
    qDebug() << "AV::~AV";
}

void AV::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new AVPrivate(this));
    }
}

AVPrivate::AVPrivate(AV *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

AVPrivate::~AVPrivate()
{
}

void AVPrivate::initialize()
{
}

void AVPrivate::connectAllSlots()
{
    connectSignalAndSignalByNamesake(g_Setting, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(g_Setting, SIGNAL(onAVStatus(const int, const int)),
                     m_Parent,  SLOT(onAVStatusHandler(const int, const int)),
                     type);
}

bool AVPrivate::requestAudioSource(const AudioSource source)
{
    qDebug() << "AVPrivate::requestAudioSource" << source;
    bool flag(true);
    HANDLER callback(NULL);
    switch (source) {
    case AS_AV1: {
        callback = releaseAV1Source;
        break;
    }
    case AS_AV2: {
        callback = releaseAV2Source;
        break;
    }
    case AS_Idle: {
        callback = NULL;
        break;
    }
    default: {
        return false;
        break;
    }
    }
    const HANDLER ptr = acquirePreemptiveResource(callback, static_cast<void*>(this));
    qDebug() << "callback != ptr" << (callback != ptr);
    if ((AS_Idle == source)
            || (callback != ptr)) {
        m_Callback = callback;
        flag = g_Audio->requestAudioSource(source);
    }
    return flag;
}

void AVPrivate::releaseAudioSource(const AudioSource source)
{
    qDebug() << "AVPrivate::releaseAudioSource" << source;
    if (NULL != m_Callback) {
        qDebug() << "AVPrivate :: NULL != m_Callback";
        m_Callback = NULL;
        clearOwner();
        g_Audio->releaseAudioSource(source);
    }
}

void AVPrivate::avExit(const AudioSource source)
{
    qDebug() << "AVPrivate::avExit" << source;
    switch (source) {
    case AS_AV1: {
        if (releaseAV1Source == m_Callback) {
            //            m_AVService->stopAV(AVT_1);
            m_Callback = NULL;
        }
        break;
    }
    case AS_AV2: {
        if (releaseAV2Source == m_Callback) {
            //            m_AVService->stopAV(AVT_2);
            m_Callback = NULL;
        }
        break;
    }
    default: {
        return;
        break;
    }
    }
}
