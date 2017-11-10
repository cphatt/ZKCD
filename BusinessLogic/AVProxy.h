#ifndef AVPROXY_H_1501063672
#define AVPROXY_H_1501063672

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "AV.h"

/*
 * Proxy class for interface local.AV
 */
class LocalAVInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "local.AV"; }

public:
    LocalAVInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalAVInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> startAV(int type, int width, int height)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(width) << qVariantFromValue(height);
        return asyncCallWithArgumentList(QLatin1String("startAV"), argumentList);
    }

    inline QDBusPendingReply<> stopAV(int type)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type);
        return asyncCallWithArgumentList(QLatin1String("stopAV"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void onAVStatus(int type, int status);
};

namespace local {
  typedef ::LocalAVInterface AV;
}
#endif
