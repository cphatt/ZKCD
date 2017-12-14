#include "Port.h"
#include <QDebug>
#include "RunnableThread.h"
#include "AutoConnect.h"
#include "Setting.h"
#include "Audio.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
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
    void receiveAllCustomEvent();


    void doHanderData();
    ssize_t  readData(char *buffer, size_t n);
    ssize_t writeData(const void *buffer, size_t n);
    int write(char ch);
//    static void SerialPortReadThread(void *);
    bool isLinkCommand(const char *buff);
    bool isTouchCommand(const char *buff, void * paramater);
    QTimer *m_Timer  = NULL;

public:
    Port* m_Parent;

};

//向外传递
void Port::handlerMCUData(const int type, const int size)
{
    qWarning() << "Port::handlerMCUData" <<type << size ;
    emit onMCUDataRecv(type, size);
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

//        qWarning()<< "send"<< m_Private->writeData("6666", 5) << "byte";
//        m_Private->m_Timer->start();

}

/**
 * @brief Port::handlerData 用于处理线程中无法发送带参信号
 * @param type  界面跳转类型
 */
void Port::handlerData(int type)
{

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
            case Port::IO:{
                *(sysio + 0x1C0 / 4) = 0;
                *(sysio + 0x1C4 / 4) = 0;
                *(sysio + 0x1C8 / 4) = 0;
                *(sysio + 0x1CC / 4) &= ~0xFFFF;
                *(gpio + 0) |= (0xFFFFFFF << 2);
            //拉黑
//                EventEngine::CustomEvent<QString> event(CustomEventType::IdleWidgetStatus, new QString(WidgetStatus::RequestShow));
//                g_EventEngine->sendCustomEvent(event);
                break;
            }
            case Port::RGB:
            default:{
                *(sysio + 0x1C0 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1C4 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1C8 / 4) = (1<<28) |(1<<24) |(1<<20) |(1<<16) |(1<<12) |(1<<8) | (1<<4) |(1<<0);
                *(sysio + 0x1CC / 4) = (1<<12) |(1<<8) | (1<<4) |(1<<0);
            //正常
//                EventEngine::CustomEvent<QString> event1(CustomEventType::IdleWidgetStatus, new QString(WidgetStatus::RequestHide));
//                g_EventEngine->sendCustomEvent(event1);
                break;
            }
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
//    m_Timer->start();

#ifndef gcc
    initialize();
#endif
    connectAllSlots();
    receiveAllCustomEvent();
}


/**
 * @brief PortPrivate::isLinkCommand    判断MCU数据并处理
 * @param buff  包含数据的数组 数字固定为6
 * @param paramater PortPrivate 对象
 * @return  该协议是否执行
 */
bool PortPrivate:: isLinkCommand(const char *buff){   //
    unsigned char checksum=buff[0];
    unsigned char temp =buff[2] + 4;
    unsigned char type_data =buff[4];
    int i,flag =0;

    if(buff[0] != 0x5c)
        return flag;
    for(i = 1; i < temp; i++)
        checksum = checksum ^buff[i];

//     qWarning() << "isLinkCommand" << checksum << buff[temp];
//    printf("isLinkCommand 0x%x,0x%x,0x%x,0x%x,0x%x,checksum 0x%x, buff[temp] 0x%x\n",buff[0], buff[1], buff[2], buff[3], buff[4], checksum,buff[temp]);
    if(checksum ==buff[temp])
    {       flag = 1;
//            qWarning() << "type" <<buff[3] <<",data" << type_data;
//            printf("type = 0x%x, data = 0x%x\n", buff[3],  type_data);
            if(buff[3] == 0x2){
                    if(type_data == 0x1){
//                        emit m_Private->m_Parent->read_port_data(1);
                        //延时
                        m_Parent->setMemStatus(Port::RGB);
//                        m_Timer->start();
                        char data = m_Parent->soundStatus;
                        m_Parent->responseMCU(Port::C_SoundStatus, &data, 1);
                    }else if(type_data == 0x2){     //turn on carplay
//                        emit m_Private->m_Parent->read_port_data(2);
                        m_Parent->setMemStatus(Port::IO);
                    }
            }else if(buff[3] == 0x100){       //set Laguage
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
            }else if(buff[3] == 0x10){       //set volume
                //设置底板的声音
                m_Parent->handlerMCUData(0,type_data);
            }else if(buff[3] == 0x11){      //answer phone
                m_Parent->handlerMCUData(1,type_data);
            }
     }
    return  flag;
}

/**
 * @brief isCommand     判断触摸数据
 * @param buff
 * @return
 */
bool isCommand(const char *buff){
    struct input_event ev; //input
    int x_val,y_val,i;
    bool ret = false;
    char checksum = buff[0];

        for(i = 1; i < 5; i++)
            checksum = checksum ^buff[i];

        if(checksum == buff[i])
        {           
                x_val = (buff[1] << 8) | (buff[2] );
                y_val = (buff[3] << 8) | (buff[4] );

                if(buff[0] == 0x61)	//push
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
                    ret = true;
                }else if(buff[0] == 0xe1) //release
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
                    ret = true;
                }                
            }       
        return ret;
}


/**
 * @brief PortPrivate::SerialPortReadThread 该函数的作用于处理MCU数据，但是在线程中发送带枚举参数的信号会报错
 * @param paramater PortPrivate
 */
static void SerialPortReadThread(void *paramater)
{
    qDebug() << "SerialPortReadThread" << paramater;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    char data = 0x1;
    g_Port->responseMCU(Port::C_ShowCarplay, &data, 1);
    g_Port->responseMCU(Port::C_HideCarplay, &data, 1);
    g_Port->setMemStatus(Port::IO);
    int n;

    char rbuff[1024+128]={0};
    int count = 0;
    g_Audio->requestSetVolume(38);
//    system("./test.sh");
    forever{
//        printf("wait data and count=%d.\n", count);
//        n= m_Private->readData(rbuff, 10);
        n = read(fd,rbuff + count,128 );
        qWarning() << n;
//        printf("%d data has been read\n ", n);
        if(n > 0)
               count += n;

        while(count >= 6)
        {
            if( isCommand(rbuff) || m_Private->isLinkCommand(rbuff)  ){
                memcpy(rbuff, rbuff+6, count );
                count -= 6;
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

//    munmap((void *) ((int) io & (~pageAlignment)),
//           regSize + ((int) io & pageAlignment));
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

    qWarning() << QThreadPool::globalInstance()->maxThreadCount() << "maxThreadCount";
    //set MaxThreadCount
    QThreadPool::globalInstance()->setMaxThreadCount(2);
    qWarning() << QThreadPool::globalInstance()->maxThreadCount() << "maxThreadCount";
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(SerialPortReadThread, this);
    QThreadPool::globalInstance()->start(runnable);

}
void PortPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
void PortPrivate::connectAllSlots(){
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);


    QObject::connect(m_Parent, SIGNAL(read_port_data(int)),
                     m_Parent,  SLOT(handlerData(int)),
                     type);

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



