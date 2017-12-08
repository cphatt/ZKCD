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
//    enum Key{
//        K_Control = 0x80,
//        K_Escape = 0x81,
//        K_VolumeMore = 0x82,
//        K_VolumeLess = 0x83,
//        K_Down = 0x86,
//        K_Up = 0x87,
//        K_Right = 0x88,
//        K_Enter = 0x89,
//        K_Left = 0x8A,
//        K_Menu = 0x8F,
//        K_BT = 0x90,
//        K_CMMB = 0x91,
//        K_GPS = 0x92,
//        K_Music = 0xA2,
//        K_Picture = 0xA3,
//        K_Video = 0xA4,
//        K_Home = 0xAA,
//    };
       //音源状态
    enum SoundStatus{
            CarPlayConnected = 0x1,
            MirrorConnected = 0x2,
            CarPlayDisConnected= 0x3,
            MirrorDisConnected=0x4,
            CarlifeConnected = 0x5,
            CarlifeDisConnected = 0x6,
    };

    //carlife向主控通讯
    enum CarlifeResponse {
            C_SoundStatus = 4,
            C_HideCarplay = 5,
            C_ShowCarplay = 6,
            C_BTCall = 9,
    };
    //carlife向主控通讯
    enum MemStatus {
        RGB = 0,       //正常
        IO = 1,         //高阻
    };
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
    };

    void handlerMCUData(const int type, const int size);
    int  responseMCU(const Port::CarlifeResponse type, char * buf, int len);
    void setStatus(Port::SoundStatus status);
    void setMemStatus(Port::MemStatus);

    inline static Port* instance() {
        static Port* port(new Port(qApp));
        return port;
    }
signals:
    void onMCUDataRecv( int type, int data);
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
    Port::SoundStatus soundStatus;

};

#endif // PORT_H
