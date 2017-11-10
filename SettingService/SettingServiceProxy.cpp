#include "SettingServiceProxy.h"

/*
 * Implementation of interface class LocalDbusServerSettingInterface
 */

LocalDbusServerSettingInterface::LocalDbusServerSettingInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

LocalDbusServerSettingInterface::~LocalDbusServerSettingInterface()
{
}

