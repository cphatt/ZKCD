#include "Port.h"
#include <QDebug>
#include "RunnableThread.h"
#include "AutoConnect.h"
#include "Setting.h"
#include<QTimer>
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
#include <sys/mman.h>

#define SYS_REG_BASE	0xE4900000
#define GPIO_REG_BASE	0xE4600000
#define REG_SIZE		0x1000
typedef unsigned int  u32;

static int fd;
static int input_fd;
static int ret;
int mem_fd = -1;
u32 *sysio = (u32 *)MAP_FAILED, *gpio =(u32 *) MAP_FAILED;

bool isUSBAlive;
bool isSDAlive;

class PortPrivate
{
    Q_DISABLE_COPY(PortPrivate)
public:
     explicit PortPrivate(Port* parent);
    virtual ~PortPrivate();
    void initialize();
    void initializeSerial();
    void initializeMem();
    void initializeInput();
    void connectAllSlots();
    bool isOpen();
    void setPortName(const QString &name);
    QString portName() ;
    void setBaudRate(int baudRate);
    int baudRate();
    void doHanderData();
    ssize_t  readData(char *buffer, size_t n);
    ssize_t writeData(const void *buffer, size_t n);
    int write(char ch);
    static void SerialPortReadThread(void *);
    bool isLinkCommand(const char *buff, void * paramater);
    bool isTouchCommand(const char *buff, void * paramater);
    QTimer *m_Timer  = NULL;

public:
    Port* m_Parent;

};

//void Port::handlerMCUData(const Port::Type type, const char *buffer, const int size)
//{
//    qDebug() <<"Port::handlerMCUData";
//    emit onMCUDataRecv(type,buffer,size);
//}

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

        qWarning()<< "send"<< m_Private->writeData("6666", 5) << "byte";
//        m_Private->m_Timer->start();
}

/**
 * @brief Port::handlerData 用于处理线程中无法发送带参信号
 * @param type  界面跳转类型
 */
void Port::handlerData(int type)
{
        qDebug() <<"Port::handlerData" <<type;
        if(1== type){
                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestShow);
        }else if(2 == type){
                g_Widget->setWidgetType(Widget::T_Carplay,  WidgetStatus::RequestHide);
        }
}
/**
该函数用于向串口中写入数据
type -------- 事件类型
data---------数据
len ----------长度
**/
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
/**
 * @brief Port::setStatus   用于保存当前音源状态
 * @param status
 */
void Port::setStatus(Port::SoundStatus status){
    soundStatus = status;
    qWarning()<<"Port::setStatus : " << soundStatus;
}

/**
 * @brief Port::setMemStatus    设置屏幕状态
 */
void Port::setMemStatus(Port::MemStatus status){
        qWarning() << " Port::setMemStatus " << status;
        switch (status) {
            case Port::IO:
                *(sysio + 0x1C0 / 4) = 0;
                *(sysio + 0x1C4 / 4) = 0;
                *(sysio + 0x1C8 / 4) = 0;
                *(sysio + 0x1CC / 4) &= ~0xFFFF;
                *(gpio + 0) |= (0xFFFFFFF << 2);
                break;
            case Port::RGB:
            default:
                *(sysio + 0x1C0 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1C4 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1C8 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1CC / 4) = (1<<12) |(1<<8) | (1<<4) |(1<<0);
                break;
            }
}

/**
 * @brief Port::onDeviceWatcherStatus   用于保存当前媒体设备的状态
 * @param type  设备类型
 * @param status    设备状态
 */
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
    m_Timer->start();

#ifndef gcc
    initialize();
#endif
    connectAllSlots();
}

/**
 * @brief PortPrivate::isTouchCommand
 * @param buff
 * @param paramater
 * @return
 */
bool PortPrivate::isTouchCommand(const char *buff, void * paramater){
    struct input_event ev; //input
    int x_val,y_val, i;
    bool ret = false;
    unsigned char checksum=buff[0];
    unsigned char temp =buff[2] + 4;

    for(i = 1; i < temp; i++)
    {
        checksum = checksum ^buff[i];
    }
    printf("isTouchCommand temp = %d,0x%x,0x%x,0x%x,0x%x,0x%x,checksum 0x%x, buff[temp] 0x%x\n",temp,buff[4], buff[5], buff[6], buff[7], buff[8], checksum,buff[temp]);
    if(checksum ==buff[temp]){
        if(buff[8] == 0x01 || buff[8] == 0x02 )//header -- touch event
        {
                        ret = true;
            x_val = (buff[4] << 8) | (buff[5] << 0);
            y_val = (buff[6] << 8) | (buff[7] << 0);
             printf("x:%d,y:%d\n", x_val, y_val);

            if(buff[8] == 0x02) //release
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
                qWarning()<< "UP";
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
                qWarning() << "MOVE";
            }

        }
        //
        //        else
        //        {
        //            printf("###### data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
        //        //	printf("###### x:%d y:%d\n",(buff[2] << 8) | (buff[1] << 0),(buff[4] << 8) | (buff[3] << 0));
        //        }
    }

    return ret;
}

/**
 * @brief PortPrivate::isLinkCommand    判断MCU数据并处理
 * @param buff  包含数据的数组 数字固定为6
 * @param paramater PortPrivate 对象
 * @return  该协议是否执行
 */
bool PortPrivate:: isLinkCommand(const char *buff, void * paramater){   //
    unsigned char checksum=buff[0];
    unsigned char temp =buff[2] + 4;
    unsigned char type_data =buff[4];
    int i,flag =0;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    for(i = 1; i < temp; i++)
        checksum = checksum ^buff[i];

     qWarning() << "isLinkCommand" << checksum << buff[temp];
//    printf("isLinkCommand 0x%x,0x%x,0x%x,0x%x,0x%x,checksum 0x%x, buff[temp] 0x%x\n",buff[0], buff[1], buff[2], buff[3], buff[4], checksum,buff[temp]);
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


            }else if(buff[3] == 0x7){       //xuanniu
                    //open
            }else if(buff[3] == 0x8){       //request carlife status
                char data = (char)m_Parent->soundStatus;
                m_Parent->responseMCU(Port::C_SoundStatus, &data , 1);
            }
     }
    return  flag;
}

/**
 * @brief isCommand     判断触摸数据
 * @param buff
 * @return
 */
//bool isCommand(const char *buff){
//    struct input_event ev; //input

//    char checksum;
//    int x_val,y_val,i;
//    bool ret = false;

//        checksum = 0;
//        for(i=0; i<5; i++)
//            checksum += buff[i];
//        checksum = ~checksum;
//        //qDebug() << checksum << buff[i];

//        if(checksum == buff[i])
//        {
//            if(buff[0] == 0x61 || buff[0] == 0xa1 || buff[0] == 0xe1)//header -- touch event
//            {
//                x_val = (buff[2] << 8) | (buff[1] << 0);
//                y_val = (buff[4] << 8) | (buff[3] << 0);

//                if(buff[0] == 0xe1) //release
//                {
//                    //presure
//                    ev.type = EV_ABS;
//                    ev.code = ABS_PRESSURE;
//                    ev.value = 0x0;
//                    ::write(input_fd, &ev, sizeof(struct input_event));

//                    //sync
//                    ev.type = EV_SYN;
//                    ev.code = SYN_REPORT;
//                    ev.value = 0x0;
//                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
//                   // qDebug() << "UP";
//                }
//                else	//push
//                {
//                    //x axis
//                    ev.type = EV_ABS;
//                    ev.code = ABS_X;
//                    ev.value = x_val;
//                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
//                    if(ret < 0)
//                    {
//                        qDebug() << "write X axis failed";
//                    }
//                    //y axis
//                    ev.type = EV_ABS;
//                    ev.code = ABS_Y;
//                    ev.value = y_val;
//                    ::write(input_fd, &ev, sizeof(struct input_event));
//                    //presure
//                    ev.type = EV_ABS;
//                    ev.code = ABS_PRESSURE;
//                    ev.value = 0xFFF;
//                   ::write(input_fd, &ev, sizeof(struct input_event));

//                    //sync
//                    ev.type = EV_SYN;
//                    ev.code = SYN_REPORT;
//                    ev.value = 0x0;
//                    ::write(input_fd, &ev, sizeof(struct input_event));
//                    //qDebug() << "MOVE";
//                }
//                ret = true;
//            }
//
//        else
//        {
//            printf("###### data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
//        //	printf("###### x:%d y:%d\n",(buff[2] << 8) | (buff[1] << 0),(buff[4] << 8) | (buff[3] << 0));
//        }
//        return ret;
//}
/**
 * @brief PortPrivate::SerialPortReadThread 该函数的作用于处理MCU数据，但是在线程中发送带枚举参数的信号会报错
 * @param paramater PortPrivate
 */
void PortPrivate::SerialPortReadThread(void *paramater)
{
    qDebug() << "SerialPortReadThread" << paramater;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    int nwrite,i;
    int n;
    unsigned char buff[256]={0};
    char rbuff[1024+128]={0};
    int count = 0;

    forever{
        printf("wait data and count=%d.\n", count);
//        n= m_Private->readData(rbuff, 10);
        n = read(fd,rbuff + count,10 );

        printf("%d data has been read\n ", n);
        if(n > 0)
               count += n;
        for(i =0 ; i < count; i++)
            printf("0x%x, ", rbuff[i]);
        printf("\n");
        sleep(1);

//        emit m_Private->m_Parent->read_port_data(QByteArray());
        while(count >= 6)
        {
            printf("head data = 0x%x \n",  rbuff[0]);
            printf("count=%d.\n", count);
//            for(i =0 ; i < count; i++)
//                printf("0x%x, ", rbuff[i]);
//            printf("\n");

            //为什么会出现这样的情况,执行了ncpy后变成0.用memcpy就OK了，奇怪。
            if( rbuff[0]== 0x5c ){

                if(rbuff[2]== 0x1 && m_Private->isLinkCommand(rbuff ,paramater)){
                    memcpy(rbuff, rbuff+6, count );
                    count -= 6;
                }else if(count >= 10 && m_Private->isTouchCommand(rbuff, paramater)){
                    memcpy(rbuff, rbuff+10, count );
                    count -= 10;
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
    if(comport < 2)
        sprintf(dev, "/dev/ttyHS%d", comport);
    else
        sprintf(dev, "/dev/ttyS%d", comport);
    printf("openning%s\n", dev);

    fd = open(dev, O_RDWR|O_NOCTTY|O_NDELAY);//|O_NOCTTY|O_NDELAY
    if (fd < 0) {
        printf("Can't Open Serial Port ttyS%d", comport);
        return -1;
    }
    //消除非阻塞
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
    newtio.c_cc[VMIN] = 1; //至少6个的时候，就得返回了

    tcflush(fd,TCIFLUSH);


    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
        perror("com set error");
        return -1;
    }
    printf("set done!\n");
    return 0;
}
/**
 * @brief DWLMapRegisters   映射屏幕内存地址
 * @param mem_dev
 * @param base
 * @param regSize
 * @param write
 * @return
 */
u32 *DWLMapRegisters(int mem_dev, unsigned int base,
                     unsigned int regSize, u32 write)
{
    const int pageSize = getpagesize();
    const int pageAlignment = pageSize - 1;

    size_t mapSize;
    const char *io =(char *) MAP_FAILED;

    /* increase mapping size with unaligned part */
    mapSize = regSize + (base & pageAlignment);

    /* map page aligned base */
    if(write)
        io = (char *) mmap(0, mapSize, PROT_READ | PROT_WRITE,
                           MAP_SHARED, mem_dev, base & ~pageAlignment);
    else
        io = (char *) mmap(0, mapSize, PROT_READ, MAP_SHARED,
                           mem_dev, base & ~pageAlignment);

    /* add offset from alignment to the io start address */
    if(io != MAP_FAILED)
        io += (base & pageAlignment);

    return (u32 *) io;
}

void DWLUnmapRegisters(const void *io, unsigned int regSize)
{
    const int pageSize = getpagesize();
    const int pageAlignment = pageSize - 1;

    munmap((void *) ((int) io & (~pageAlignment)),
           regSize + ((int) io & pageAlignment));
}


/**
 * @brief PortPrivate::initializeSerial   串口初始化函数
 */
void PortPrivate::initializeSerial(){
    //初始化串口
     int dev = 3;
    fd = open_port(dev);
    if (fd < 0){
        perror("open_port error");

        exit(1);
    }
    //设置串口
    if (set_opt(fd, 115200, 8, 'N', 1) < 0) {
        perror("set_opt error");
        ::close(fd);
       return;
    }
    printf("fd=%d\n",fd);
}

void  PortPrivate::initializeInput(){
    input_fd = ::open("/dev/input/event0", O_RDWR);
    if(input_fd < 0)
    {
        perror("Can not open input node\n");
    }else{
        qDebug()<< "open input success!";
    }
}

void PortPrivate::initializeMem(){
    //初始化屏幕内存映射
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(mem_fd == -1) {
        printf("failed to open /dev/mem, error %d is %s\n", errno, strerror(errno));
        return;
    }
    sysio = DWLMapRegisters(mem_fd, SYS_REG_BASE, REG_SIZE, 1);
    if(sysio == MAP_FAILED) {
        printf("failed to mmap sys regs. error %d is %s\n", errno, strerror(errno));
        DWLUnmapRegisters(sysio, REG_SIZE);
        close(mem_fd);
    }
    gpio = DWLMapRegisters(mem_fd, GPIO_REG_BASE, REG_SIZE, 1);
    if(gpio == MAP_FAILED) {
        printf("failed to mmap gpio regs. error %d is %s\n", errno, strerror(errno));
        DWLUnmapRegisters(gpio, REG_SIZE);
        close(mem_fd);
    }
}

void PortPrivate::initialize()
{
    initializeSerial();
    initializeInput();
    initializeMem();

   //初始化线程
    m_Parent->soundStatus = Port::CarPlayDisConnected;
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

//这个函数可以改一下,做个测试
//ssize_t PortPrivate::readData(void *buffer, size_t n)
//{
//    ssize_t numRead = 0;
//    size_t totRead = 0;
//    char *buf;
//    buf = (char *)buffer;

//    for (totRead = 0; totRead < n; ) {
//        numRead = read(fd, buf, n - totRead);
//        if (numRead == 0)
//            return totRead;
//        if (numRead == -1) {
//            if (errno == EINTR) {printf("\033[;31m%s:%d  numRead=%d\033[0m\n", __func__, __LINE__, numRead);
//                continue;
//            } else {
//                return -1;
//            }
//        }
//        totRead += numRead;
//        buf += numRead;
//    }

//    return totRead;
//}

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


//ssize_t safe_write(int fd, const void *vptr, size_t n)
//{
//    size_t  nleft;
//    ssize_t nwritten;
//    const char *ptr;

//    ptr = vptr;
//    nleft = n;

//    while(nleft > 0)
//    {
//    if((nwritten = write(fd, ptr, nleft)) <= 0)
//        {
//            if(nwritten < 0&&errno == EINTR)
//                nwritten = 0;
//            else
//                return -1;
//        }
//        nleft -= nwritten;
//        ptr   += nwritten;
//    }
//    return(n);
//}


ssize_t safe_read(int fd,char *vptr,size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr=vptr;
    nleft=n;

    while(nleft > 0)
    {
        if((nread = read(fd,ptr,nleft)) < 0)
        {
            if(errno == EINTR)//被信号中断
                nread = 0;
            else
                return -1;
        }
        else
        if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n-nleft);
}


ssize_t PortPrivate::readData(char *r_buf, size_t len)
{
    ssize_t cnt = 0;
    fd_set rfds;
    struct timeval time;

    /*将文件描述符加入读描述符集合*/
    FD_ZERO(&rfds);
    FD_SET(fd,&rfds);

    /*设置超时为15s*/
    time.tv_sec = 15;
    time.tv_usec = 0;

    /*实现串口的多路I/O*/
    ret = select(fd+1,&rfds,NULL,NULL,&time);
    switch(ret)
    {
        case -1:
            fprintf(stderr,"select error!\n");
            return -1;
        case 0:
            fprintf(stderr,"time over!\n");
            return -1;
        default:
            cnt = safe_read(fd,r_buf,len);
            if(cnt == -1)
            {
                fprintf(stderr,"read error!\n");
                return -1;
            }
            return cnt;
    }
}

//int uart_write(int fd,const char *w_buf,size_t len)
//{
//    ssize_t cnt = 0;

//    cnt = safe_write(fd,w_buf,len);
//    if(cnt == -1)
//    {
//        fprintf(stderr,"write error!\n");
//        return -1;
//    }

//    return cnt;
//}
