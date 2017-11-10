#ifndef BTSERVICE_H
#define BTSERVICE_H

#include <QObject>
#include <QScopedPointer>

#define ArkMicroBluetoothService     "com.arkmicro.bluetooth"
#define ArkMicroBluetoothPath        "/com/arkmicro/bluetooth"
#define ArkMicroBluetoothInterface   "Local.DbusServer.Bluetooth"

enum BT_STATUS {
    BT_READY = 1,
    BT_CONNECTING = 2,
    BT_CONNECTED = 3,
    BT_INCOMINGCALL = 4,
    BT_OUTGOINGCALL = 5,
    BT_ACTIVECALL = 6,
};

class BTServicePrivate;
class BTService : public QObject
{
    Q_OBJECT
public:
    explicit BTService(QObject* parent = NULL);
    ~BTService();
public slots:
    void synchronize();
    void requestRest();
//  void releaseAudioSource(const int source);
//  void releaseAudioSource(const AudioSource source);
    void requestConnectBT(int connect);
    void requestBTStatus();
    void requestBTName(QString name);
    void requsetBTPairCode(QString paircode);
    void requestBTToggle();
    void requestPairPhoneName();
//  bool requestAudioSource(const AudioSource source);
signals:
    void onBTStatus(int status);
    void onBTPairCode(QString code);
    void onBTName(QString name);
private:
    friend class BTServicePrivate;
    QScopedPointer<BTServicePrivate> m_Private;
};

#endif // BTSERVICE_H
