#ifndef SETTINGSERVICE_H
#define SETTINGSERVICE_H

#define SettingApplication           QString("-setting")
#define ArkMicroSettingService       QString("com.arkmicro.setting")
#define ArkMicroSettingPath          QString("/com/arkmicro/setting")
#define ArkMicroSettingInterface     QString("Local.DbusServer.Setting")

#include "SettingServiceProxy.h"
#include <QObject>
#include <QScopedPointer>

enum LanguageType {
    LT_English = 0,
    LT_Chinese = 1,
    LT_Japaness = 2,
    LT_Korean = 3,
    LT_Spanish = 4,
    LT_Portuguese = 5,
    LT_Russian = 6,
    LT_German = 7,
    LT_French = 8,
};
#define LanguageType int

enum SettingType {
    ST_Value = 0,
    ST_Plus = 1,
    ST_Minus = 2,
};
#define SettingType int

enum CalibrateType {
    CT_Start = 0,
    CT_Finish = 1
};
#define CalibrateType int

enum DisplayScreenType {
    DST_On = 0,
    DST_Off = 1,
    DST_Toggle = 2
};
#define DisplayScreenType int

enum AVType {
    AVT_1 = 0,
    AVT_2 = 1
};
#define AVType int

enum AVStatus {
    AVS_NoDetact = 0,
    AVS_Detacting = 1,
    AVS_Detacted = 2,
    AVS_Play = 3
};
#define AVStatus int

class SettingServicePrivate;
class SettingService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Setting")
public:
    explicit SettingService(QObject* parent = NULL);
    ~SettingService();
public slots:
    void synchronize();
    void reset();
    void setLanguage(const int language);
    //    void setLanguage(const LanguageType language);
    void setBrightness(const int type, const int value);
    //    void setBrightness(const SettingType type, const int value);
    void setContrast(const int type, const int value);
    //    void setContrast(const SettingType type, const int value);
    void setSaturation(const int type, const int value);
    //    void setSaturation(const SettingType type, const int value);
    void setDisplayScreen(const int type);
    //    void setDisplayScreen(const DisplayScreenType type);
    void startCalibrate();
    void startAV(const int type, const int width, const int height);
    //    void startAV(const AVType type, const int width, const int height);
    void stopAV(const int type);
    //    void stopAV(const AVType type);
signals:
    void onLanguageChange(const int language);
    //    void onLanguageChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onSaturationChange(const int value);
    void onDisplayScreenChange(const int type);
    //    void onDisplayScreenChange(const DisplayScreenType type);
    void onCalibrateChange(const int status, const QString& data);
    //    void onCalibrateChange(const CalibrateType status);
    void onAVStatus(const int type, const int status);
//        void onStartAV(const AVType type, const AVStatus status);
private slots:
    void onTimeout();
private:
    friend class SettingServicePrivate;
    QScopedPointer<SettingServicePrivate> m_Private;
};

#endif // SETTINGSERVICE_H
