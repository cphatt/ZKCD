#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#define AudioApplication             QString("-audiomanager")
#define ArkMicroAudioService         QString("com.arkmicro.audiomanager")
#define ArkMicroAudioPath            QString("/com/arkmicro/audiomanager")
#define ArkMicroAudioInterface       QString("Local.DbusServer.AudioManager")
#define ArkMicroAudioRequest         QString("requestAudioSource")
#define ArkMicroAudioRelease         QString("releaseAudioSource")

#include <QObject>
#include <QScopedPointer>

enum EffectType {
    ET_Undefine = -1,
    ET_Default = 0,
    ET_Classical = 1,
    ET_Jazz = 2,
    ET_Rock = 3,
    ET_Pop = 4,
    ET_Custom = 5,
};
#define EffectType int

typedef enum
{
    LEFT = 0x01,
    RIGHT = 0x2,
}TYPE_VOLUME;

typedef enum
{
    IR_A = 0,
    IR_B = 1,
}IR_Mode;
#define IR_Mode int

enum AudioSource {
    AS_Idle = 0,
    AS_Music = 1,
    AS_Video = 2,
    AS_Mirror = 3,
    AS_Carplay = 4,
    AS_AV1 = 5,
    AS_AV2 = 6,
};
#define AudioSource int

enum OutPutSource {
    OPS_FM = 1,
    OPS_IR ,
    OPS_Speak,
};
#define OutPutSource int

class AudioServicePrivate;
class AudioService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.AudioManager")
public:
    explicit AudioService(QObject* parent = NULL);
    ~AudioService();
public slots:
    bool requestAudioSource(const int source);
    //    bool requestAudioSource(const AudioSource source, const QString &destination, const QString &path, const QString &Interface, const QString &method);
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
    void synchronize();
    void reqesetRest();
    void requestIncreaseVolume();
    void requestDecreaseVolume();
    void requsetIsOpenFM();
    void requestFMToggle();
    void requestIRToggle();
    void requestIRMode(int mode);
//    void requestIRMode(IR_Mode mode);
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
private:
    friend class AudioServicePrivate;
    QScopedPointer<AudioServicePrivate> m_Private;
};

#endif // AUDIOSERVICE_H
