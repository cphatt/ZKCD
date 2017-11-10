#include "AudioService.h"
#include "AudioServiceProxy.h"
#include "AutoConnect.h"
#include "AudioConfig.h"
#include "UserInterfaceUtility.h"
#include <QDBusMessage>
#include <QTimerEvent>

class AudioServicePrivate
{
public:
    explicit AudioServicePrivate(AudioService* parent);
    ~AudioServicePrivate();
    void initialize();
    void synchronize();
    bool m_FMToggle = false;
    bool m_IRToggle = false;
    IR_Mode m_IRMode = IR_A;
    int m_CurrentFrequency = AudioConfig::getFMGetFreqency();
    int m_CurrentVolume = AudioConfig::getVolume(true);
    OutPutSource m_CurrentOutPutSource = OPS_Speak;
    AudioSource m_AudioSource = AS_Idle;
private:
    AudioService* m_Parent = NULL;
};

AudioService::AudioService(QObject *parent)
    : QObject(parent)
    , m_Private(new AudioServicePrivate(this))
{
}

AudioService::~AudioService()
{
}

bool AudioService::requestAudioSource(const AudioSource source)
{
    qDebug() << "AudioService::requestAudioSource" << source;
    bool flag(true);
    m_Private->m_AudioSource = source;
    emit onVolumeChange(m_Private->m_CurrentOutPutSource, m_Private->m_CurrentVolume);
    return flag;
}

void AudioService::releaseAudioSource(const AudioSource source)
{
    qDebug() << "AudioService::releaseAudioSource" << source;
    m_Private->m_AudioSource = AS_Idle;
}
void AudioService::synchronize()
{
    m_Private->synchronize();
}

void AudioService::reqesetRest()
{
    AudioConfig::clearLog();
}

void AudioService::requestIncreaseVolume()
{
    if (m_Private->m_CurrentVolume < 40) {
        ++m_Private->m_CurrentVolume;
    }
    AudioConfig::setVolume(m_Private->m_CurrentVolume);
    emit onVolumeChange(m_Private->m_CurrentOutPutSource, m_Private->m_CurrentVolume);
}

void AudioService::requestDecreaseVolume()
{
    if (m_Private->m_CurrentVolume > 0) {
        --m_Private->m_CurrentVolume;
    }
    AudioConfig::setVolume(m_Private->m_CurrentVolume);
    emit onVolumeChange(m_Private->m_CurrentOutPutSource, m_Private->m_CurrentVolume);
}

void AudioService::requsetIsOpenFM()
{
}

void AudioService::requestOpenFM(int open)
{
}

void AudioService::requestFMToggle()
{
    m_Private->m_FMToggle = !m_Private->m_FMToggle;
    m_Private->synchronize();
}

void AudioService::requestIRToggle()
{
    m_Private->m_IRToggle = !m_Private->m_IRToggle;
    m_Private->synchronize();
}

void AudioService::requestIRMode(IR_Mode mode)
{
    m_Private->m_IRToggle = true;
    m_Private->m_IRMode = mode;
    m_Private->synchronize();
}

void AudioService::requestSetVolume(const int volume)
{
    if (volume > 40) {
        m_Private->m_CurrentVolume = 40;
    } else if (volume < 0) {
        m_Private->m_CurrentVolume = 0;
    } else {
        m_Private->m_CurrentVolume = volume;
    }
    AudioConfig::setVolume(m_Private->m_CurrentVolume);
    m_Private->synchronize();
}

void AudioService::requestSetFreqency(int freq)
{
    m_Private->m_FMToggle = true;
    m_Private->m_CurrentFrequency = freq;
    m_Private->synchronize();
}

AudioServicePrivate::AudioServicePrivate(AudioService *parent)
    : m_Parent(parent)
{
    initialize();
}

AudioServicePrivate::~AudioServicePrivate()
{
}

void AudioServicePrivate::initialize()
{
    if (ArkMicroAudioService == qApp->applicationName()) {
        bool ret = QDBusConnection::sessionBus().registerService(ArkMicroAudioService);
        ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroAudioPath,
                                                                  m_Parent,
                                                                  QDBusConnection::ExportNonScriptableSignals
                                                                  | QDBusConnection::ExportNonScriptableSlots);
        if (!ret) {
            qCritical() << "AudioService Register QDbus failed!";
            exit(EXIT_FAILURE);
        }
        qDebug() << "AudioService Register QDbus ok!";
    }
}

void AudioServicePrivate::synchronize()
{
    int fmFlag(0);
    if (m_FMToggle) {
        fmFlag = 1;
        emit m_Parent->onFMChange(m_CurrentFrequency);
        m_CurrentOutPutSource = OPS_FM;
    } else if (m_IRToggle) {
        m_CurrentOutPutSource = OPS_IR;
    } else {
        m_CurrentOutPutSource = OPS_Speak;
    }
    int irFlag(0);
    if (m_IRToggle) {
        irFlag = 1;
        emit m_Parent->onIRChange(m_IRMode);
    }
    emit m_Parent->onIRIsOpen(irFlag);
    emit m_Parent->onFMIsOpen(fmFlag);
    emit m_Parent->onVolumeChange(m_CurrentOutPutSource, m_CurrentVolume);
}
