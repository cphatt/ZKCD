#ifndef AUTOCONNECT_H
#define AUTOCONNECT_H

#include <QList>
#include <QString>
class QObject;

void connectSignalAndSlotByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list = QList<QString>(), const Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));
void connectSignalAndSignalByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list = QList<QString>(), const Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection));

#endif // AUTOCONNECT_H
