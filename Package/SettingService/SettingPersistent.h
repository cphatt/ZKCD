#ifndef SETTINGPERSISTENT_H
#define SETTINGPERSISTENT_H

#include <QtGlobal>

class SettingService;
class MainWidget;
class SettingPersistent
{
    Q_DISABLE_COPY(SettingPersistent)
public:
    static QString getLanguageResources();
    static bool restoreBrightness();
    static bool restoreContrast();
    static bool restoreSaturation();
    static bool getCalibrate();
    static int getLanguage(const bool reload = false);
    static int getBrightness(const bool reload = false);
    static int getContrast(const bool reload = false);
    static int getSaturation(const bool reload = false);
protected:
    friend class SettingService;
    friend class MainWidget;
    static void setCalibrate(const bool flag);
    static void setLanguage(const int value);
    static void setBrightness(const int value);
    static void setContrast(const int value);
    static void setSaturation(const int value);
    static void reset();
private:
    SettingPersistent();
    ~SettingPersistent();
};

#endif // SETTINGPERSISTENT_H
