#ifndef ALSADBUS_H
#define ALSADBUS_H

#include <QObject>
#include"audioconfig.h"
#include "bluetooth.h"

#define ArkMicroAlsaService     "com.arkmicro.audiomanager"
#define ArkMicroAlsaPath        "/com/arkmicro/audiomanager"
#define ArkMicroAlsaInterface   "Local.DbusServer.AudioManager"

#define VOL_MAX_LEVEL 40
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

class AlsaDbus : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AlsaDbus)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.AudioManager")
#define g_Link (AlsaDbus::instance())
public:
    explicit AlsaDbus(QObject *parent = 0);

    ~AlsaDbus();
    inline static AlsaDbus& instance() {
        static AlsaDbus AlsaDbus;
        return AlsaDbus;
    }

    void initialize();

    void sendVolume(int type, const int volume);

    void sendVolumeRange(const int min, const int max);

    void sendFM(const int freq);

    void sendIR(const int mode);

    void sendIsOpenFM(int open);

    void sendIsOpenBT(int open);

    void sendIsOpenIR(int open);


    void SetInputAudio(AudioSource source);

    void SetOutputAudio(OutPutSource source, int volume);
protected:
    void timerEvent(QTimerEvent* event);
private:
    int	m_nMinVol;
    int	m_nMaxVol;
    int m_nCurVol;
    int m_nCurFreq;
    int m_nCurIRMode;
    AudioSource m_AudioSource;
    OutPutSource m_OpsSource;

    int volume2pos(int volume);
    int pos2volume(int pos/* 0 ~ 40*/);
signals:
    void onVolumeChange(int type, const int volume);

    void onVolumeRangeChange(const int min, const int max);

    void onFMChange(int freq);

    void onIRChange(int mode);

    void onFMIsOpen(int open);

    void onIRIsOpen(int open);
public slots:
    void requestStart();

    void synchronize();

    void reqesetRest();

    bool requestAudioSource(const int source);

    void releaseAudioSource(const int source);

    void requestIncreaseVolume();

    void requestDecreaseVolume();

    void requsetIsOpenFM();

    void requestFMToggle();

    void requestIRToggle();

    void requestIRMode(int mode);

    void requestOpenFM(int open);

    void requestSetVolume(const int volume);

    void requestSetFreqency(int freq);
};

#endif // ALSADBUS_H

