#include "AVProxy.h"

/*
 * Implementation of interface class LocalAVInterface
 */

LocalAVInterface::LocalAVInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

LocalAVInterface::~LocalAVInterface()
{
}

