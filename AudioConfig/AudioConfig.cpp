#include "AudioConfig.h"
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

static const QString persistentPath("/data/AudioConfig.ini");

static const QString FM("FM");
static const QString Volume("Volume");
static const QString FMStatus("FMStatus");
static const QString BTStatus("BTStatus");
static const QString BTName("BTName");
static const QString BTPairCode("BTPairCode");
static const QString InputAudioSource("InputAudioSource");
static const QString OutputAudioSource("OutputAudioSource");

static QSettings settings(persistentPath, QSettings::IniFormat, qApp);

AudioConfig::AudioConfig()
{
}

AudioConfig::~AudioConfig()
{
}

void AudioConfig::setFMFreqency(int nFreq)
{
    settings.setValue(FM, nFreq);
    settings.sync();
}

int AudioConfig::getFMGetFreqency(const bool reload)
{
    int defaultValue(885);
    bool flag(false);
    if (reload) {
        settings.sync();
    }
    int ret = settings.value(FM, defaultValue).toInt(&flag);
    if (!flag)
    {
        ret = defaultValue;
    }
    return ret;
}

void AudioConfig::setVolume(int value)
{
    settings.setValue(Volume, value);
    settings.sync();
}

int AudioConfig::getVolume(const bool reload)
{
    int defaultValue(35);
    bool flag(false);
    if (reload) {
        settings.sync();
    }
    int ret = settings.value(Volume, defaultValue).toInt(&flag);
    if (!flag)
    {
        ret = defaultValue;
    }
    qDebug() << "AudioConfig::getVolume" << ret;
    return ret;
}

void AudioConfig::setBTName(QString str)
{
    settings.setValue(BTName, str);
    settings.sync();
}

QString AudioConfig::getBTName(const bool reload)
{
    QString defaultValue("");
    if (reload) {
        settings.sync();
    }
    QString ret = settings.value(BTName, defaultValue).toString();
    return ret;
}

QString AudioConfig::getBTPairCode(const bool reload)
{
    QString defaultValue("");
    if (reload) {
        settings.sync();
    }
    QString ret = settings.value(BTPairCode, defaultValue).toString();
    return ret;
}

void AudioConfig::setBTPairCode(QString str)
{
    settings.setValue(BTPairCode, str);
    settings.sync();
}

int AudioConfig::getInputAudioSource(const bool reload)
{
    int defaultValue(0);
    bool flag(false);
    if (reload) {
        settings.sync();
    }
    int ret = settings.value(InputAudioSource, defaultValue).toInt(&flag);
    if (!flag)
    {
        ret = defaultValue;
    }
    return ret;
}

void AudioConfig::setInputAudioSource(int source)
{
    settings.setValue(InputAudioSource, source);
    settings.sync();
}

int AudioConfig::getOutputAudioSource(const bool reload)
{
    int defaultValue(3);
    bool flag(false);
    if (reload) {
        settings.sync();
    }
    int ret = settings.value(OutputAudioSource, defaultValue).toInt(&flag);
    if (!flag)
    {
        ret = defaultValue;
    }
    return ret;
}

void AudioConfig::setOutputAudioSource(int source)
{
    settings.setValue(OutputAudioSource, source);
    settings.sync();
}

void AudioConfig::clearLog()
{
    settings.clear();
}
