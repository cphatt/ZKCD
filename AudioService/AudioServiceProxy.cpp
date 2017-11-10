#include "AudioServiceProxy.h"

/*
 * Implementation of interface class LocalDbusServerAudioManagerInterface
 */

LocalDbusServerAudioManagerInterface::LocalDbusServerAudioManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

LocalDbusServerAudioManagerInterface::~LocalDbusServerAudioManagerInterface()
{
}

