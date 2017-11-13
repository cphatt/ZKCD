#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QEvent>
#include <QRect>
#include <QScopedPointer>
#include <QCoreApplication>
#include "Widget.h"
#include "Multimedia.h"


class PortPrivate;
class Port : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Port)
#ifdef g_Port
#undef g_Port
#endif
#define g_Port (Port::instance())
public:
    enum Type {
        T_OpenCarPlay,
        T_CloseCarPlay,
        D_NAVI,
        D_Volume
    };
    enum Key{
        K_Control = 0x80,
        K_Escape = 0x81,
        K_VolumeMore = 0x82,
        K_VolumeLess = 0x83,
        K_Down = 0x86,
        K_Up = 0x87,
        K_Right = 0x88,
        K_Enter = 0x89,
        K_Left = 0x8A,
        K_Menu = 0x8F,
        K_BT = 0x90,
        K_CMMB = 0x91,
        K_GPS = 0x92,
        K_Music = 0xA2,
        K_Picture = 0xA3,
        K_Video = 0xA4,
        K_Home = 0xAA,
    };

    enum CarlifeResponse {
            C_SoundStatus = 4,
            C_Close = 5,
            C_Open = 6,
            C_BTCall = 9,
    };

    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onMCUDataRecv(const Port::Type type, const char *buffer, const int size) = 0;
    };

    void handlerMCUData(const Port::Type type, const char *buffer, const int size);
    int  responseMCU(const Port::CarlifeResponse type, char * buf, int len);

    inline static Port* instance() {
        static Port* port(new Port(qApp));
        return port;
    }
signals:
    void onMCUDataRecv(const int type, const char *buffer, const int size);
    void read_port_data(const int type);
protected:
//    void customEvent(QEvent* event);

protected slots:
    void handlerData(int type);
        void onTimeOut();
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);

public:
    explicit Port(QObject *parent = NULL);
    ~Port();
    friend class PortPrivate;
    QScopedPointer<PortPrivate> m_Private;
};

#endif // PORT_H
