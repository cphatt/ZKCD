#include "BT.h"
#include "AutoConnect.h"
#include "BTServiceProxy.h"
#include "RunnableThread.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"

class BTPrivate
{
public:
    explicit BTPrivate(BT* parent);
    ~BTPrivate();
    void initialize();
    void connectAllSlots();
    Local::DbusServer::Bluetooth* m_BluetoothProxy = NULL;
private:
    BT* m_Parent = NULL;
};

void BT::synchronize()
{
    qDebug() << "BT::synchronize";
    initializePrivate();
    QDBusPendingReply<> reply = m_Private->m_BluetoothProxy->synchronize();
    reply.waitForFinished();
    qDebug() << "Dbus call BT::synchronize" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call BT::synchronize failed" << reply.error();
    }
}

void BT::requestRest()
{
    initializePrivate();
}

void BT::requestConnectBT(int connect)
{
    initializePrivate();
}

void BT::requestBTStatus()
{
    initializePrivate();
}

void BT::requestBTName(QString name)
{
    initializePrivate();
}

void BT::requsetBTPairCode(QString paircode)
{
    initializePrivate();
}

void BT::requestBTToggle()
{
    initializePrivate();
}

void BT::requestPairPhoneName()
{
    qDebug() << "BT::requestPairPhoneName";
}

void BT::onServiceRegistered(const QString &service)
{
    qDebug() << "BT::onServiceRegistered" << service;
}

void BT::onServiceUnregistered(const QString &service)
{
    qDebug() << "BT::onServiceUnregistered" << service;
}

static void bluetoothStarting(void* parameter)
{
    QDBusInterface interface(ArkMicroBluetoothService,
                             ArkMicroBluetoothPath,
                             ArkMicroBluetoothInterface,
                             QDBusConnection::sessionBus());
    QDBusReply<void> reply = interface.call(QString("synchronize"));
    if (reply.isValid()) {
        qDebug() << "bluetoothStarting::synchronize ok!";
    } else {
        qDebug() << "bluetoothStarting::synchronize fail!";
    }
}

BT::BT(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    qDebug() << "BT::BT";
    g_DbusService->addWatchedService(ArkMicroBluetoothService);
    connectSignalAndSlotByNamesake(g_DbusService, this);
    initializePrivate();
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(bluetoothStarting, NULL);
    QThreadPool::globalInstance()->start(runnable);
}

BT::~BT()
{
    qDebug() << "BT::~BT";
}

void BT::initializePrivate()
{
    qDebug() << "BT::initializePrivate";
    if (NULL == m_Private) {
        m_Private.reset(new BTPrivate(this));
    }
}

BTPrivate::BTPrivate(BT *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

BTPrivate::~BTPrivate()
{
}

void BTPrivate::initialize()
{
    if (NULL == m_BluetoothProxy) {
        m_BluetoothProxy = new Local::DbusServer::Bluetooth(ArkMicroBluetoothService,
                                                            ArkMicroBluetoothPath,
                                                            QDBusConnection::sessionBus(),
                                                            m_Parent);
    }
}

void BTPrivate::connectAllSlots()
{
    if (NULL != m_BluetoothProxy) {
        connectSignalAndSignalByNamesake(m_BluetoothProxy, m_Parent);
    }
}
