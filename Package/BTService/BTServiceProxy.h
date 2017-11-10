#ifndef BTSERVICEPROXY_H_1489744431
#define BTSERVICEPROXY_H_1489744431

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface Local.DbusServer.Bluetooth
 */
class LocalDbusServerBluetoothInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "Local.DbusServer.Bluetooth"; }

public:
    LocalDbusServerBluetoothInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalDbusServerBluetoothInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> requestBTName(const QString &name)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(name);
        return asyncCallWithArgumentList(QLatin1String("requestBTName"), argumentList);
    }

    inline QDBusPendingReply<> requestBTStatus()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestBTStatus"), argumentList);
    }

    inline QDBusPendingReply<> requestBTToggle()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestBTToggle"), argumentList);
    }

    inline QDBusPendingReply<> requestConnectBT(int connect)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(connect);
        return asyncCallWithArgumentList(QLatin1String("requestConnectBT"), argumentList);
    }

    inline QDBusPendingReply<> requestPairPhoneName()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestPairPhoneName"), argumentList);
    }

    inline QDBusPendingReply<> requestRest()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("requestRest"), argumentList);
    }

    inline QDBusPendingReply<> requsetBTPairCode(const QString &paircode)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(paircode);
        return asyncCallWithArgumentList(QLatin1String("requsetBTPairCode"), argumentList);
    }

    inline QDBusPendingReply<> synchronize()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("synchronize"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void onBTName(const QString &name);
    void onBTPairCode(const QString &code);
    void onBTStatus(int status);
};

namespace Local {
  namespace DbusServer {
    typedef ::LocalDbusServerBluetoothInterface Bluetooth;
  }
}
#endif
