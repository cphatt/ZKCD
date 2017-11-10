#include "BTServiceProxy.h"

/*
 * Implementation of interface class LocalDbusServerBluetoothInterface
 */

LocalDbusServerBluetoothInterface::LocalDbusServerBluetoothInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

LocalDbusServerBluetoothInterface::~LocalDbusServerBluetoothInterface()
{
}

