#ifndef AUDIOSERVICEPROXY_H_1490929325
#define AUDIOSERVICEPROXY_H_1490929325

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface Local.DbusServer.AudioManager
 */
class LocalDbusServerAudioManagerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "Local.DbusServer.AudioManager"; }

public:
    LocalDbusServerAudioManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalDbusServerAudioManagerInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> releaseAudioSource(int source)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(source);
        return asyncCallWithArgumentList(QLatin1String("releaseAudioSource"), argumentList);
    }

    inline QDBusPendingReply<> reqesetRest()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("reqesetRest"), argumentList);
    }

    inline QDBusPendingReply<bool> requestAudioSource(int source)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(source);
        return asyncCallWithArgumentList(QLatin1String("requestAudioSource"), argumentList);
    }

    inline QDBusPendingReply<> requestDecreaseVolume()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestDecreaseVolume"), argumentList);
    }

    inline QDBusPendingReply<> requestFMToggle()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestFMToggle"), argumentList);
    }

    inline QDBusPendingReply<> requestIRMode(int mode)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(mode);
        return asyncCallWithArgumentList(QLatin1String("requestIRMode"), argumentList);
    }

    inline QDBusPendingReply<> requestIRToggle()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestIRToggle"), argumentList);
    }

    inline QDBusPendingReply<> requestIncreaseVolume()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestIncreaseVolume"), argumentList);
    }

    inline QDBusPendingReply<> requestOpenFM(int open)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(open);
        return asyncCallWithArgumentList(QLatin1String("requestOpenFM"), argumentList);
    }

    inline QDBusPendingReply<> requestSetFreqency(int freq)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(freq);
        return asyncCallWithArgumentList(QLatin1String("requestSetFreqency"), argumentList);
    }

    inline QDBusPendingReply<> requestSetVolume(int volume)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(volume);
        return asyncCallWithArgumentList(QLatin1String("requestSetVolume"), argumentList);
    }

    inline QDBusPendingReply<> requestStart()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestStart"), argumentList);
    }

    inline QDBusPendingReply<> requsetIsOpenFM()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requsetIsOpenFM"), argumentList);
    }

    inline QDBusPendingReply<> synchronize()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("synchronize"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onIRChange(int mode);
    void onIRIsOpen(int open);
    void onVolumeChange(int type, int volume);
    void onVolumeRangeChange(int min, int max);
};

namespace Local {
  namespace DbusServer {
    typedef ::LocalDbusServerAudioManagerInterface AudioManager;
  }
}
#endif
