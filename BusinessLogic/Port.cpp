#include "Port.h"
#include <QDebug>
#include "RunnableThread.h"
#include "AutoConnect.h"
#include <QThreadPool>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <termios.h>

#include "Setting.h"
#include<QTimer>

static int fd;
static int input_fd;
bool isUSBAlive;
bool isSDAlive;
class PortPrivate
{
    Q_DISABLE_COPY(PortPrivate)
public:
     explicit PortPrivate(Port* parent);
    virtual ~PortPrivate();
    void initialize();
    void connectAllSlots();
    bool isOpen();
    void setPortName(const QString &name);
    QString portName() ;
    void setBaudRate(int baudRate);
    int baudRate();
    void doHanderData();
    ssize_t  readData(void *buffer, size_t n);
    ssize_t writeData(const void *buffer, size_t n);
    int write(char ch);
    static void SerialPortReadThread(void *);
    bool isLinkCommand(const char *buff, void * paramater);
    QTimer *m_Timer  = NULL;
public:
    Port* m_Parent;

};

void Port::handlerMCUData(const Port::Type type, const char *buffer, const int size)
{
    qDebug() <<"Port::handlerMCUData";
    emit onMCUDataRecv(type,buffer,size);
}

//void Port::handlerData(const Port::Type type)
//{
//        qDebug() <<"Port::handlerData" <<type;
//        if(Port::T_OpenCarPlay == type){
//                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestShow);
//        }else if(Port::T_CloseCarPlay == type){
//                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestHide);
//        }
//}
void Port::handlerData(int type)
{
        qDebug() <<"Port::handlerData" <<type;
        if(1== type){
                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestShow);
        }else if(2 == type){
                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestHide);
        }
}
Port::Port(QObject *parent)
    : QObject(parent)
    , m_Private(new PortPrivate(this))
{
     qDebug() <<"Port::Port";
}

Port::~Port()
{

}

void Port::onTimeOut()
{

        qDebug() << "send"<< m_Private->writeData("6666", 5) << "byte";
        m_Private->m_Timer->start();
}
/*
该函数用于向串口中写入数据
type -------- 事件类型
data---------数据
len ----------长度
*/
int  Port::responseMCU(const Port::CarlifeResponse type, char *data,int len){
        char buff[10] = {0};
        char checksum;
        int size = 0;
        int temp = len + 4;
        int i = 0;
        qDebug() << "Port::responseMCU" << type << len;
        //整合一下直接用
        buff[0] = 0x5c;
        buff[1] = 0x00;
        buff[2] = len;
        buff[3] = type;
        size = len;
        checksum = buff[0];
        while(size--)
            buff[4 + size ] = data[size];

        for(i = 1; i < temp; i++)
        {
            checksum = checksum ^buff[i];
        }
       buff[temp] = checksum;

       return m_Private->writeData(buff, len + 5);
}
void Port::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "HomeWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
            case DWS_Empty: {
                isSDAlive= false;
                break;
            }
            case DWS_Busy: {
                isSDAlive = true;
                break;
            }
            case DWS_Ready: {
                isSDAlive= true;
                break;
            }
            case DWS_Remove: {
                isSDAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
    if (DWT_USBDisk == type) {
        switch (status) {
            case DWS_Empty: {
                isUSBAlive = false;
                break;
            }
            case DWS_Busy: {
                isUSBAlive = true;
                break;
            }
            case DWS_Ready: {
                isUSBAlive = true;
                break;
            }
            case DWS_Remove: {
                isUSBAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
}
PortPrivate::~PortPrivate()
{

}

PortPrivate::PortPrivate(Port* parent)
    : m_Parent(parent)
{
    fd = -1;
    input_fd = -1;
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(1000);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeOut()),
                     type);
//    m_Timer->start();

#ifndef gcc
    initialize();
#endif
    connectAllSlots();
}
bool isTouchCommand(const char *buff){

}

bool PortPrivate::isLinkCommand(const char *buff, void * paramater){   //
    unsigned char checksum=buff[0];
    unsigned char temp =buff[2] + 4;
    unsigned char type_data =buff[4];
    int i,flag =0;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    for(i = 1; i < temp; i++)
    {
        checksum = checksum ^buff[i];
    }
    // qWarning() << "isLinkCommand" << checksum << buff[temp];
    printf("0x%x,0x%x,0x%x,0x%x,0x%x,checksum 0x%x, buff[temp] 0x%x\n",buff[0], buff[1], buff[2], buff[3], buff[4], checksum,buff[temp]);
    if(checksum ==buff[temp])
    {       flag = 1;
            qWarning() << "type" <<buff[3] <<",data" << type_data;
            if(buff[3] == 0x2){
                    if(type_data == 0x1){       //turn on carlife
                        emit m_Private->m_Parent->read_port_data(1);
                    }else if(type_data == 0x2){     //turn on carplay
                        emit m_Private->m_Parent->read_port_data(2);
                    }
            }else if(buff[3] == 0x3){       //set Laguage
                    switch(type_data){
                        case 0x1:   //LT_English
                            g_Setting->setLanguage(LT_English);
                            break;
                        case 0x2:   //LT_Chinese
                            g_Setting->setLanguage(LT_Chinese);
                            break;
                        case 0x3:
                            g_Setting->setLanguage(LT_Japaness);
                            break;
                        case 0x4:
                            g_Setting->setLanguage(LT_Korean);
                            break;
                        case 0x5:
                            g_Setting->setLanguage(LT_Spanish);
                            break;
                        case 0x6:
                            g_Setting->setLanguage(LT_Portuguese);
                            break;
                        case 0x7:
                            g_Setting->setLanguage(LT_Russian);
                            break;
                        case 0x8:
                            g_Setting->setLanguage(LT_German);
                            break;
                        case 0x9:
                            g_Setting->setLanguage(LT_French);
                            break;
                    default:
                        break;
                    }


            }else if(buff[3] == 0x7){       //request carlife status
                    //open
            }else if(buff[3] == 0x8){       //旋钮

            }
     }
    return  flag;
}

bool isCommand(const char *read_buf){
    struct input_event ev; //input

    char checksum;
    int x_val,y_val,i;
    bool ret = false;

        checksum = 0;
        for(i=0; i<5; i++)
            checksum += read_buf[i];
        checksum = ~checksum;
        //qDebug() << checksum << read_buf[i];

        if(checksum == read_buf[i])
        {
            if(read_buf[0] == 0x61 || read_buf[0] == 0xa1 || read_buf[0] == 0xe1)//header -- touch event
            {
                x_val = (read_buf[2] << 8) | (read_buf[1] << 0);
                y_val = (read_buf[4] << 8) | (read_buf[3] << 0);

                if(read_buf[0] == 0xe1) //release
                {
                    //presure
                    ev.type = EV_ABS;
                    ev.code = ABS_PRESSURE;
                    ev.value = 0x0;
                    ::write(input_fd, &ev, sizeof(struct input_event));

                    //sync
                    ev.type = EV_SYN;
                    ev.code = SYN_REPORT;
                    ev.value = 0x0;
                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
                   // qDebug() << "UP";
                }
                else	//push
                {
                    //x axis
                    ev.type = EV_ABS;
                    ev.code = ABS_X;
                    ev.value = x_val;
                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
                    if(ret < 0)
                    {
                        qDebug() << "write X axis failed";
                    }
                    //y axis
                    ev.type = EV_ABS;
                    ev.code = ABS_Y;
                    ev.value = y_val;
                    ::write(input_fd, &ev, sizeof(struct input_event));
                    //presure
                    ev.type = EV_ABS;
                    ev.code = ABS_PRESSURE;
                    ev.value = 0xFFF;
                   ::write(input_fd, &ev, sizeof(struct input_event));

                    //sync
                    ev.type = EV_SYN;
                    ev.code = SYN_REPORT;
                    ev.value = 0x0;
                    ::write(input_fd, &ev, sizeof(struct input_event));
                    //qDebug() << "MOVE";
                }
                ret = true;
            }
            else  if(read_buf[0] == 0x51 || read_buf[0] == 0x91 || read_buf[0] == 0xd1)//header -- touch event
            {
                //printf("#Key data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",read_buf[0], read_buf[1], read_buf[2], read_buf[3], read_buf[4], read_buf[5]);
                switch (read_buf[2]) {
                case Port::K_Control :

                    break;
                case Port::K_Escape :
                    g_Widget->setWidgetType(Widget::T_Back, WidgetStatus::RequestShow);
                    break;
                case Port::K_VolumeMore :

                    break;
                case Port::K_VolumeLess :

                    break;
                case Port::K_Down :

                    break;
                case Port::K_Up :

                    break;
                case Port::K_Right :

                    break;
                case Port::K_Enter :

                    break;
                case Port::K_Left :

                    break;
                case Port::K_Menu :

                    break;
                case Port::K_BT :

                    break;
                case Port::K_CMMB :

                    break;
                case Port::K_GPS :

                    break;
                case Port::K_Music :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::RequestShow);
                    break;
                case Port::K_Picture :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::RequestShow);
                    break;
                case Port::K_Video :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::RequestShow);
                    break;
                case Port::K_Home :
                    g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            printf("###### data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",read_buf[0], read_buf[1], read_buf[2], read_buf[3], read_buf[4], read_buf[5]);
        //	printf("###### x:%d y:%d\n",(read_buf[2] << 8) | (read_buf[1] << 0),(read_buf[4] << 8) | (read_buf[3] << 0));
        }
        return ret;
}
/**
 * @brief PortPrivate::SerialPortReadThread 该函数的作用于处理MCU数据，但是在线程中发送带参数的信号会报错
 * @param paramater
 */
void PortPrivate::SerialPortReadThread(void *paramater)
{
    qDebug() << "SerialPortReadThread" << paramater;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    int nwrite,i;
    int dev;
    unsigned char buff[256]={0};
    char rbuff[1024+128]={0};
    int count = 0;

    forever{
        printf("wait data and count=%d.\n", count);
        count += read(fd, rbuff+count, 32);
        for(i =0 ; i < count; i++)
            printf("0x%x, ", rbuff[i]);
        printf("\n");
        sleep(1);

//        emit m_Private->m_Parent->read_port_data(QByteArray());
        while(count >= 6)
        {
            printf("head data = 0x%x \n",  rbuff[0]);
            printf("count=%d.\n", count);
            for(i =0 ; i < count; i++)
                printf("0x%x, ", rbuff[i]);
            printf("\n");

            //为什么会出现这样的情况,执行了ncpy后变成0.用memcpy就OK了，奇怪。
            if( rbuff[0]== 0x5c ){
                if(m_Private->isLinkCommand(rbuff ,paramater)){
                    memcpy(rbuff, rbuff+6, count );
                    count -= 6;
                }else if(count >= 10 && isTouchCommand(rbuff)){
                            //触摸数据先放在这里
                }else{
                    memcpy(rbuff, rbuff+1, count );
                    count -= 1;
                }
            }else{
                memcpy(rbuff, rbuff+1, count );
                count -= 1;
            }
        }

    }
}

static int open_port(int comport)
{
    char dev[16];
    long vdisable;
    int fd = -1, ret = -1;

    if (comport > 4)
        return -1;

    sprintf(dev, "/dev/ttyHS%d", comport);
    printf("openning%s\n", dev);

    fd = open(dev, O_RDWR | O_NOCTTY);//|O_NOCTTY|O_NDELAY
    if (fd < 0) {
        printf("Can't Open Serial Port ttyS%d", comport);
        return -1;
    }

    if (fcntl(fd, F_SETFL, 0) < 0) {
        printf("fcntl failed!\n");
        goto exit;
    }
#if 0
    if(isatty(STDIN_FILENO) == 0) {
        printf("standard input is not a terminal device\n");
        goto exit;O_NOCTTY
    } else {
        printf("isatty success!\n");
    }
#endif
    printf("fd-open=%d\n", fd);
    ret = 0;
exit:
    if (ret < 0)
        close(fd);
    return fd;
}


static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio;

    bzero(&newtio, sizeof(newtio));
    if (tcgetattr(fd, &newtio) != 0) {
        perror("SetupSerial 1");
        return -1;
    }

    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch(nBits) {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch(nEvent) {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch(nSpeed) {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;

    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;

    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;

    case 19200:
        cfsetispeed(&newtio, B19200);
        cfsetospeed(&newtio, B19200);
        break;

    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;

    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;

    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

    if (nStop == 1)
        newtio.c_cflag &= ~CSTOPB;
    else if (nStop == 2)
        newtio.c_cflag |= CSTOPB;

    newtio.c_lflag &= ~(ICANON | ISIG | ECHO | IEXTEN);
    newtio.c_iflag &= ~(INPCK|BRKINT|ICRNL|ISTRIP|IXON);
    newtio.c_oflag  &= ~OPOST;

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 6; //至少6个的时候，就得返回了

    tcflush(fd,TCIFLUSH);


    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
        perror("com set error");
        return -1;
    }
    printf("set done!\n");
    return 0;
}
/**
 * @brief PortPrivate::initialize   串口初始化函数
 */

void PortPrivate::initialize()
{

    int dev = 1;
    fd = open_port(dev);
    if (fd < 0){
        perror("open_port error");
        return ;
    }

    if (set_opt(fd, 115200, 8, 'N', 1) < 0) {
        perror("set_opt error");
        ::close(fd);
       return;
    }
    printf("fd=%d\n",fd);


    input_fd = ::open("/dev/input/event0", O_RDWR);
    if(input_fd < 0)
    {
        perror("Can not open input node\n");
        exit(1);
    }else{
        qDebug()<< "open input success!";
    }
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(SerialPortReadThread, this);
    QThreadPool::globalInstance()->start(runnable);
}

void PortPrivate::connectAllSlots(){
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);


    QObject::connect(m_Parent, SIGNAL(read_port_data(int)),
                     m_Parent,  SLOT(handlerData(int)),
                     type);

}

//这个函数可以改一下
ssize_t PortPrivate::readData(void *buffer, size_t n)
{
    ssize_t numRead = 0;
    size_t totRead = 0;
    char *buf;
    buf = (char *)buffer;

    for (totRead = 0; totRead < n; ) {
        numRead = read(fd, buf, n - totRead);
        if (numRead == 0)
            return totRead;
        if (numRead == -1) {
            if (errno == EINTR) {printf("\033[;31m%s:%d  numRead=%d\033[0m\n", __func__, __LINE__, numRead);
                continue;
            } else {
                return -1;
            }
        }
        totRead += numRead;
        buf += numRead;
    }

    return totRead;
}

ssize_t PortPrivate::writeData( const void *buffer, size_t n)
{
    ssize_t numWritten;
    size_t totWritten = 0;
    const char *buf;
    buf = (char *)buffer;

    for (totWritten = 0; totWritten < n; ) {
        numWritten =:: write(fd, buf, n - totWritten);
        if (numWritten <= 0) {
            if (numWritten == -1 && errno == EINTR)
                continue;
            else
                return -1;
        }
        totWritten += numWritten;
        buf += numWritten;
    }
    return totWritten;
}
