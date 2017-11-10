#ifndef BT_H
#define BT_H

#include "BTService.h"
#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class BTPrivate;
class BT
        : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(BT)
#ifdef g_BT
#undef g_BT
#endif
#define g_BT (BT::instance())
public:
    inline static BT* instance() {
        static BT* bt(new BT(qApp));
        return bt;
    }
public slots:
    void synchronize();
    void requestRest();
    void requestConnectBT(int connect);
    void requestBTStatus();
    void requestBTName(QString name);
    void requsetBTPairCode(QString paircode);
    void requestBTToggle();
    void requestPairPhoneName();
signals:
    void onBTStatus(int status);
    void onBTPairCode(QString code);
    void onBTName(QString name);
private slots:
    void onServiceRegistered(const QString &service);
    void onServiceUnregistered(const QString &service);
private:
    explicit BT(QObject *parent = NULL);
    ~BT();
    void initializePrivate();
    friend class BTPrivate;
    QScopedPointer<BTPrivate> m_Private;
};

#endif // BT_H

