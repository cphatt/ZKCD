#ifndef SETTINGSERVICEPROXY_H_1505377192
#define SETTINGSERVICEPROXY_H_1505377192

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "SettingService.h"

/*
 * Proxy class for interface Local.DbusServer.Setting
 */
class LocalDbusServerSettingInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "Local.DbusServer.Setting"; }

public:
    LocalDbusServerSettingInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalDbusServerSettingInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> reset()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("reset"), argumentList);
    }

    inline QDBusPendingReply<> setBrightness(int type, int value)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(value);
        return asyncCallWithArgumentList(QLatin1String("setBrightness"), argumentList);
    }

    inline QDBusPendingReply<> setContrast(int type, int value)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(value);
        return asyncCallWithArgumentList(QLatin1String("setContrast"), argumentList);
    }

    inline QDBusPendingReply<> setDisplayScreen(int type)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type);
        return asyncCallWithArgumentList(QLatin1String("setDisplayScreen"), argumentList);
    }

    inline QDBusPendingReply<> setLanguage(int language)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(language);
        return asyncCallWithArgumentList(QLatin1String("setLanguage"), argumentList);
    }

    inline QDBusPendingReply<> setSaturation(int type, int value)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(value);
        return asyncCallWithArgumentList(QLatin1String("setSaturation"), argumentList);
    }

    inline QDBusPendingReply<> startAV(int type, int width, int height)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(width) << qVariantFromValue(height);
        return asyncCallWithArgumentList(QLatin1String("startAV"), argumentList);
    }

    inline QDBusPendingReply<> startCalibrate()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("startCalibrate"), argumentList);
    }

    inline QDBusPendingReply<> stopAV(int type)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type);
        return asyncCallWithArgumentList(QLatin1String("stopAV"), argumentList);
    }

    inline QDBusPendingReply<> synchronize()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("synchronize"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void onAVStatus(int type, int status);
    void onBrightnessChange(int value);
    void onCalibrateChange(int status, const QString &data);
    void onContrastChange(int value);
    void onDisplayScreenChange(int type);
    void onLanguageChange(int language);
    void onSaturationChange(int value);
};

namespace Local {
  namespace DbusServer {
    typedef ::LocalDbusServerSettingInterface Setting;
  }
}
#endif
