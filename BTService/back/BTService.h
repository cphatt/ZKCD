#ifndef DBUSSERVER_H
#define DBUSSERVER_H

#include <QObject>
#include <QTimer>
#include "bluetooth.h"

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

class DbusServer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DbusServer)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Bluetooth")

#define g_Link (DbusServer::instance())
public:
    explicit DbusServer(QObject *parent = NULL);
    ~DbusServer();
    inline static DbusServer& instance() {
        static DbusServer dbusServer;
        return dbusServer;
    }

    void initialize();

    void sendBTStatus(int status);

    void sendBTPairCode(QString paircode);

    void sendBTName(QString name);

signals:
    void onBTStatus(int status);

    void onBTPairCode(QString code);

    void onBTName(QString name);

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

protected:
    BlueTooth m_bt;
    QString m_strCode;
    QString m_strName;
    int     m_fd;

public slots:
//  void releaseAudioSource(const int source);

};

#endif // DBUSSERVER_H
