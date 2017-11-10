#include "AutoConnect.h"
#include "UserInterfaceUtility.h"

#include <QMetaMethod>
#include <QObject>

#ifndef QLOCATION
#define QLOCATION "\0"__FILE__":"QTOSTRING(__LINE__)
#endif

enum AutoConnectType {
    ACT_Signal = 0,
    ACT_Slot,
};

void autoConnect(QObject *sender, QObject *receiver, const AutoConnectType autoConnectionType, const QList<QString>& list, const Qt::ConnectionType connectType)
{
#define METASIGNAL 2
#define METASLOT   1
    Q_ASSERT(sender);
    Q_ASSERT(receiver);
    const QMetaObject *instanceMeta = sender->metaObject();
    Q_ASSERT(instanceMeta);
    for (int i = 0; i < instanceMeta->methodCount(); ++i) {
        if (QMetaMethod::Signal == instanceMeta->method(i).methodType()) {
            const char *signal = instanceMeta->method(i).signature();
            Q_ASSERT(signal);
            if (-1 != instanceMeta->indexOfSignal(signal)) {
                const QMetaObject *dispatcherMeta = receiver->metaObject();
                Q_ASSERT(dispatcherMeta);
                for (int j = 0; j < dispatcherMeta->methodCount(); ++j) {
                    QMetaMethod::MethodType methodType;
                    if (autoConnectionType == ACT_Slot) {
                        methodType = QMetaMethod::Slot;
                    } else {
                        methodType = QMetaMethod::Signal;
                    }
                    if (methodType == dispatcherMeta->method(j).methodType()) {
                        const char *slot = dispatcherMeta->method(j).signature();
                        Q_ASSERT(slot);
                        int ret = -1;
                        if (autoConnectionType == ACT_Slot) {
                            ret = dispatcherMeta->indexOfSlot(slot);
                        } else {
                            ret = dispatcherMeta->indexOfSignal(slot);
                        }
                        if (-1 != ret) {
                            if (QString(signal) ==  QString(slot)) {
                                QString signalStr = QString(METASIGNAL) + QString(signal) + QString(QLOCATION);
                                QString slotStr;
                                if (autoConnectionType == ACT_Slot) {
                                    slotStr = qPrintable(QString(METASLOT) + QString(slot) + QString(QLOCATION));
                                } else {
                                    slotStr = qPrintable(QString(METASIGNAL) + QString(slot) + QString(QLOCATION));
                                }
//                                Qt::ConnectionType connectType = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
                                if (0 ==  list.size()) {
                                    QObject::connect(sender,
                                                     qFlagLocation(qPrintable(signalStr)),
                                                     receiver,
                                                     qFlagLocation(qPrintable(slotStr)),
                                                     connectType);
                                } else {
                                    if (list.contains(slotStr)) {
                                        QObject::connect(sender,
                                                         qFlagLocation(qPrintable(signalStr)),
                                                         receiver,
                                                         qFlagLocation(qPrintable(slotStr)),
                                                         connectType);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void connectSignalAndSlotByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list, const Qt::ConnectionType type)
{
    autoConnect(sender, receiver, ACT_Slot, list, type);
}

void connectSignalAndSignalByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list, const Qt::ConnectionType type)
{
    autoConnect(sender, receiver, ACT_Signal, list, type);
}
