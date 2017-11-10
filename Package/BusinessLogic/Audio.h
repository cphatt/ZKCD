#ifndef AUDIO_H
#define AUDIO_H

#include "AudioService.h"
#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class AudioPrivate;
class Audio
        : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Audio)
#ifdef g_Audio
#undef g_Audio
#endif
#define g_Audio (Audio::instance())
public:
    inline static Audio* instance() {
        static Audio* audio(new Audio(qApp));
        return audio;
    }
    bool requestAudioSource(const int source);
    //    bool requestAudioSource(const AudioSource source);
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
    void reqesetRest();
    void requestIncreaseVolume();
    void requestDecreaseVolume();
    void requsetIsOpenFM();
    void requestFMToggle();
    void requestIRToggle();
    void requestIRMode(int mode);
//            void requestIRMode(IR_Mode mode);
    void requestOpenFM(int open);
    void requestSetVolume(const int volume);
    void requestSetFreqency(int freq);
signals:
    void onVolumeChange(int type, const int volume);
//    void onVolumeChange(OutPutSource type, const int volume);
    void onVolumeRangeChange(const int min, const int max);
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onIRIsOpen(int open);
    void onIRChange(int mode);
//    void onIRChange(IR_Mode mode);
private slots:
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
private:
    explicit Audio(QObject* parent = NULL);
    ~Audio();
    void initializePrivate();
    friend class AudioPrivate;
    QScopedPointer<AudioPrivate> m_Private;
};

#endif // AUDIO_H
