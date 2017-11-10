#include "Audio.h"
#include "AutoConnect.h"
#include "BusinessLogicUtility.h"
#include "AudioServiceProxy.h"
#include "Utility.h"
#include "UserInterfaceUtility.h"
#include <QDBusConnection>
#include <QDBusMessage>

class AudioPrivate
{
public:
    explicit AudioPrivate(Audio* parent);
    ~AudioPrivate();
    void initialize();
    void connectAllSlots();
    Local::DbusServer::AudioManager* m_AudioManagerProxy = NULL;
private:
    Audio* m_Parent = NULL;
};

static void releaseSourceCallback(void* parameter)
{
    qDebug() << "releaseSourceCallback" << QThread::currentThread();
    QDBusInterface interface(ArkMicroAudioService,
                             ArkMicroAudioPath,
                             ArkMicroAudioInterface,
                             QDBusConnection::sessionBus());
    if (NULL != parameter) {
        int* ptr = (int*)parameter;
        QDBusReply<void> reply = interface.call(ArkMicroAudioRelease, *ptr);
        if (reply.isValid()) {
            qDebug() << "releaseSourceCallback::releaseAudioSource ok!";
        } else {
            qDebug() << "releaseSourceCallback::releaseAudioSource fail!";
        }
        delete ptr;
        ptr = NULL;
    }
}

bool Audio::requestAudioSource(const AudioSource source)
{
    qDebug() << "Audio::requestAudioSource" << source;
    initializePrivate();
    EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
    g_EventEngine->sendCustomEvent(event);
    QDBusPendingReply<bool> reply = m_Private->m_AudioManagerProxy->requestAudioSource(source);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    bool flag(true);
    if (reply.isValid()) {
        flag = reply.value();
    } else {
        qDebug() << "Audio::requestAudioSource fail!";
        flag = false;
    }
    return flag;
}

void Audio::releaseAudioSource(const AudioSource source)
{
    qDebug() << "Audio::releaseAudioSource" << source;
    initializePrivate();
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->releaseAudioSource(source);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
    //    CustomRunnable* runnable = new CustomRunnable();
    //    int* type = new int(source);
    //    runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
    //    QThreadPool::globalInstance()->start(runnable);
}

void Audio::reqesetRest()
{
    qDebug() << "Audio::reqesetRest";
    initializePrivate();
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->reqesetRest();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestIncreaseVolume()
{
    initializePrivate();
    qDebug() << "Audio::requestIncreaseVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestIncreaseVolume();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestDecreaseVolume()
{
    initializePrivate();
    qDebug() << "Audio::requestDecreaseVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestDecreaseVolume();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requsetIsOpenFM()
{
    initializePrivate();
    qDebug() << "Audio::requsetIsOpenFM";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requsetIsOpenFM();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestOpenFM(int open)
{
    initializePrivate();
    qDebug() << "Audio::requestOpenFM";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestOpenFM(open);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestFMToggle()
{
    initializePrivate();
    qDebug() << "Audio::requestFMToggle";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestFMToggle();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestIRToggle()
{
    initializePrivate();
    qDebug() << "Audio::requestIRToggle";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestIRToggle();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestIRMode(IR_Mode mode)
{
    initializePrivate();
    qDebug() << "Audio::requestIRMode";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestIRMode(mode);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestSetVolume(const int volume)
{
    initializePrivate();
    qDebug() << "Audio::requestSetVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestSetVolume(volume);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestSetFreqency(int freq)
{
    initializePrivate();
    qDebug() << "AudioManager::requestSetFreqency";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestSetFreqency(freq);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::onServiceRegistered(const QString &service)
{
    qDebug() << "Audio::onServiceRegistered" << service;
    //    if (ArkMicroAudioService == service) {
    //        if (NULL != m_Private->m_AudioManagerProxy) {
    //            QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->synchronize();
    //        }
    //    }
}

void Audio::onServiceUnregistered(const QString &service)
{
    qDebug() << "Audio::onServiceUnregistered" << service;
    if (ArkMicroAudioService == service) {
        //        g_DbusService->startService(ArkMicroAudioService);
    }
}

Audio::Audio(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    qDebug() << "Audio::Audio";
    g_DbusService->addWatchedService(ArkMicroAudioService);
    connectSignalAndSlotByNamesake(g_DbusService, this);
    initializePrivate();
}

Audio::~Audio()
{
}

void Audio::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new AudioPrivate(this));
    }
}

static void test(void * ptr)
{

}

AudioPrivate::AudioPrivate(Audio *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

AudioPrivate::~AudioPrivate()
{
}

void AudioPrivate::initialize()
{
    if (NULL == m_AudioManagerProxy) {
        m_AudioManagerProxy = new Local::DbusServer::AudioManager(ArkMicroAudioService,
                                                                  ArkMicroAudioPath,
                                                                  QDBusConnection::sessionBus(),
                                                                  m_Parent);
    }
}

void AudioPrivate::connectAllSlots()
{
    if (NULL != m_AudioManagerProxy) {
        connectSignalAndSignalByNamesake(m_AudioManagerProxy, m_Parent);
    }
}
