#include "BTService.h"
#include "BTServiceProxy.h"

class BTServicePrivate
{
public:
    explicit BTServicePrivate(BTService* parent);
    ~BTServicePrivate();
private:
    BTService* m_Parent = NULL;
};

BTService::BTService(QObject *parent)
    : QObject(parent)
    , m_Private(new BTServicePrivate(this))
{
}

BTService::~BTService()
{
}

void BTService::synchronize()
{

}

void BTService::requestRest()
{

}

void BTService::requestConnectBT(int connect)
{

}

void BTService::requestBTStatus()
{

}

void BTService::requestBTName(QString name)
{

}

void BTService::requsetBTPairCode(QString paircode)
{

}

void BTService::requestBTToggle()
{

}

void BTService::requestPairPhoneName()
{

}

BTServicePrivate::BTServicePrivate(BTService *parent)
    : m_Parent(parent)
{
}

BTServicePrivate::~BTServicePrivate()
{
}

