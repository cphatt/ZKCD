#ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <QtGlobal>

class AudioConfig
{
    Q_DISABLE_COPY(AudioConfig)
public:

    static int getFMGetFreqency(const bool reload = false);
    static void setFMFreqency(int nFreq);

    static int getVolume(const bool reload = false);
    static void setVolume(int value);

    static QString getBTName(const bool reload = false);
    static void setBTName(QString str);

    static QString getBTPairCode(const bool reload = false);
    static void setBTPairCode(QString str);

    static int getInputAudioSource(const bool reload = false);
    static void setInputAudioSource(int source);

    static int getOutputAudioSource(const bool reload = false);
    static void setOutputAudioSource(int source);
    static void clearLog();
private:
    AudioConfig();
    ~AudioConfig();
};

#endif // AUDIOCONFIG_H
