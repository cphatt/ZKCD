#ifndef SETTING_H
#define SETTING_H

#include "SettingService.h"
#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class SettingPrivate;
class Setting
        : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Setting)
#ifdef g_Setting
#undef g_Setting
#endif
#define g_Setting (Setting::instance())
public:
    inline static Setting* instance() {
        static Setting* setting(new Setting(qApp));
        return setting;
    }
    void reset();
    void setLanguage(const int language);
    //    void setLanguage(const LanguageType language);
    void setBrightness(const int type, const int value);
    //    void setBrightness(const SetType type, const int value);
    void setContrast(const int type, const int value);
    //    void setContrast(const SetType type, const int value);
    void setSaturation(const int type, const int value);
    //    void setSaturation(const SetType type, const int value);
    void setDisplayScreen(const int type);
    //    void setDisplayScreen(const DisplayScreenType type);
    void startCalibrate();
    void startAV(const int type, const int width, const int height);
    //    void startAV(const AVType type, const int width, const int height);
    void stopAV(const int type);
    //    void stopAV(const AVType type);
signals:
    void onLanguageTranslateChange(const int language);
    //    void onLanguageTranslateChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onSaturationChange(const int value);
    void onDisplayScreenChange(const int type);
    //    void onDisplayScreenChange(const DisplayScreenType type);
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVStatus status);
private slots:
    void onLanguageChange(const int language);
//    void onLanguageChange(const LanguageType language);
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
private:
    explicit Setting(QObject *parent = NULL);
    ~Setting();
    void initializePrivate();
    friend class SettingPrivate;
    QScopedPointer<SettingPrivate> m_Private;
};

#endif // SETTING_H
