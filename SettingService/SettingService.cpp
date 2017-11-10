#include "SettingService.h"
#include "ark_api.h"
#include "SettingPersistent.h"
#include "RunnableThread.h"
#include "Utility.h"
#include "UserInterfaceUtility.h"
#include <QCoreApplication>
#include <QTimer>

static const unsigned char brightnessStep(14);
static const unsigned char constrasStep(14);
static const unsigned char saturationStep(14);
static const unsigned char maximum(256 - 14);
static const unsigned char minimum(256 - 14 * 15);

static void initializeRunnableCallback(void *paramater);

//OSD1_LAYER,//ui
//OSD2_LAYER,//video
//OSD3_LAYER,
//VIDEO_LAYER,//scale
//VIDEO2_LAYER,

class SettingServicePrivate
{
    Q_DISABLE_COPY(SettingServicePrivate)
public:
    explicit SettingServicePrivate(SettingService* parent);
    ~SettingServicePrivate();
    void initialize();
    void connectAllSlots();
    bool openDVRFileFileDescriptor();
    bool switchDVRChannel(const dvr_source type);
    bool configDVR(const dvr_source type, const int width, const int height);
    bool closeDVRFileFileDescriptor();
    bool startDVRData();
    bool stopDVRData();
    bool openDVRFrameBufferFileDescriptor();
    bool closeDVRFrameBufferFileDescriptor();
    bool detectSignal();
    int m_DVRFileDescriptor = -1;
    int m_FrameBufferFileDescriptor = -1;
    AVType m_AVType = AVT_1;
    AVStatus m_AVStatus = AVS_NoDetact;
    int m_Width = 0;
    int m_Height = 0;
    bool m_DetactFlag = false;
    QTimer* m_Timer = NULL;
    LanguageType m_Language = SettingPersistent::getLanguage();
    unsigned char m_Brightness = minimum + brightnessStep * SettingPersistent::getBrightness();
    unsigned char m_Contrast = minimum + constrasStep * SettingPersistent::getContrast();
    unsigned char m_Saturation = minimum + saturationStep * SettingPersistent::getSaturation();
private:
    SettingService* m_Parent = NULL;
};

SettingService::SettingService(QObject *parent)
    : QObject(parent)
    , m_Private(new SettingServicePrivate(this))
{
}

SettingService::~SettingService()
{
}

void SettingService::synchronize()
{
    emit onLanguageChange(m_Private->m_Language);
    emit onBrightnessChange(m_Private->m_Brightness / brightnessStep);
    emit onContrastChange(m_Private->m_Contrast / constrasStep);
    emit onSaturationChange(m_Private->m_Saturation / saturationStep);
}

void SettingService::reset()
{
    qDebug() << "SettingService::reset";
    SettingPersistent::reset();
}

void SettingService::setLanguage(const LanguageType language)
{
    if (language != m_Private->m_Language) {
        m_Private->m_Language = language;
        SettingPersistent::setLanguage(m_Private->m_Language);
    }
    qDebug() << "SettingService::setLanguage" << m_Private->m_Language;
    emit onLanguageChange(m_Private->m_Language);
}

void SettingService::setBrightness(const SettingType type, const int value)
{
    qWarning() << "SettingService::setBrightness" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Brightness = minimum + value * brightnessStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Brightness < (maximum - brightnessStep)) {
            m_Private->m_Brightness += value * brightnessStep;
        } else {
            m_Private->m_Brightness = maximum;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Brightness >= (minimum + brightnessStep)) {
            m_Private->m_Brightness -= value * brightnessStep;
        } else {
            m_Private->m_Brightness = minimum;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_brightness(OSD1_LAYER, m_Private->m_Brightness);
    qDebug() << "arkapi_set_layer_brightness" << ret << arkapi_get_layer_brightness(OSD1_LAYER);
#endif
    int tempValue = (m_Private->m_Brightness - minimum) / brightnessStep;
    if ((value + 7) != tempValue) {
        SettingPersistent::setBrightness(tempValue);
    }
    qWarning() << "tempValue" << tempValue << m_Private->m_Brightness;
    emit onBrightnessChange(tempValue);
}

void SettingService::setContrast(const SettingType type, const int value)
{
    qDebug() << "SettingService::setContrast" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Contrast = minimum + value * constrasStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Contrast < (maximum - constrasStep)) {
            m_Private->m_Contrast += value * constrasStep;
        } else {
            m_Private->m_Contrast = maximum;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Contrast >= (minimum + constrasStep)) {
            m_Private->m_Contrast -= value * constrasStep;
        } else {
            m_Private->m_Contrast = minimum;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_contrast(OSD1_LAYER, m_Private->m_Contrast);
    qDebug() << "arkapi_get_layer_contrast" << ret << arkapi_get_layer_contrast(OSD1_LAYER);
#endif
    int tempValue = (m_Private->m_Contrast - minimum) / constrasStep;
    if ((value + 7) != tempValue) {
        SettingPersistent::setContrast(tempValue);
    }
    emit onContrastChange(tempValue);
}

void SettingService::setSaturation(const SettingType type, const int value)
{
    qDebug() << "SettingService::setSaturation" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Saturation = minimum + value * saturationStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Saturation < (maximum - saturationStep)) {
            m_Private->m_Saturation += value * saturationStep;
        } else {
            m_Private->m_Saturation = maximum;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Saturation >= (minimum + saturationStep)) {
            m_Private->m_Saturation -= value * saturationStep;
        } else {
            m_Private->m_Saturation = minimum;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_saturation(OSD1_LAYER, m_Private->m_Saturation);
    qDebug() << "arkapi_set_layer_saturation" << ret << arkapi_get_layer_saturation(OSD1_LAYER);
#endif
    int tempValue = (m_Private->m_Saturation - minimum) / saturationStep;
    qDebug() << "SettingPersistent::setSaturation" << tempValue << value;
    if ((value + 7) != tempValue) {
        SettingPersistent::setSaturation(tempValue);
    }
    emit onSaturationChange(tempValue);
}

void SettingService::setDisplayScreen(const DisplayScreenType type)
{
    qDebug() << "SettingService::setDisplayScreen" << type;
    int ret(0);
    switch (type) {
    case DST_On: {
#ifndef gcc
        ret = system("echo 30 > /sys/devices/platform/pwm-backlight/backlight/pwm-backlight/brightness");
#endif
        break;
    }
    case DST_Off: {
#ifndef gcc
        ret = system("echo 0 > /sys/devices/platform/pwm-backlight/backlight/pwm-backlight/brightness");
#endif
        break;
    }
    case DST_Toggle:
    default: {
        break;
    }
    }
    if (0 == ret) {
        emit onDisplayScreenChange(type);
    } else {
        qDebug() << "Call system method failed!";
    }
}

static void initializeRunnableCallback(void *paramater)
{
    startCalibratre();
}

void SettingService::startCalibrate()
{
    qDebug() << "SettingService::startCalibrate";
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(initializeRunnableCallback, NULL);
    QThreadPool::globalInstance()->start(runnable);
}

void SettingService::startAV(const AVType type, const int width, const int height)
{
    dvr_source avType(DVR_SOURCE_CAMERA);
    if (AVT_1 == type) {
        avType = DVR_SOURCE_CAMERA;
    } else if (AVT_2 == type) {
        avType = DVR_SOURCE_AUX;
    } else {
        return ;
    }
    m_Private->m_AVType = type;
    qDebug() << "m_Private->m_AVStatus1" << m_Private->m_AVStatus << m_Private->m_DVRFileDescriptor;
    if (AVS_NoDetact == m_Private->m_AVStatus) {
        if (-1 == m_Private->m_DVRFileDescriptor) {
            if (m_Private->openDVRFileFileDescriptor()) {
                if (m_Private->switchDVRChannel(avType)) {
                    m_Private->m_Width = width;
                    m_Private->m_Height = height;
                    m_Private->m_AVStatus = AVS_Detacting;
                    m_Private->m_DetactFlag = true;
                    m_Private->m_Timer->setInterval(11);
                    m_Private->m_Timer->start();
                } else {
                    m_Private->closeDVRFileFileDescriptor();
                }
            } else {
                m_Private->m_AVStatus = AVS_NoDetact;
            }
        }
    }
    qDebug() << "m_Private->m_AVStatus2" << m_Private->m_AVStatus;
    emit onAVStatus(type, m_Private->m_AVStatus);
}

void SettingService::stopAV(const AVType type)
{
    qDebug() << "AVService::stopAV" << type;
    m_Private->m_Timer->stop();
    if ((AVS_Detacted == m_Private->m_AVStatus)
            || (AVS_Play == m_Private->m_AVStatus)) {
        m_Private->closeDVRFrameBufferFileDescriptor();
        m_Private->stopDVRData();
    }
    m_Private->closeDVRFileFileDescriptor();
    qDebug() << "AVService::m_DVRFileDescriptor" << m_Private->m_DVRFileDescriptor;
    m_Private->m_AVStatus = AVS_NoDetact;
    emit onAVStatus(type, m_Private->m_AVStatus);
}

void SettingService::onTimeout()
{
    qDebug() << "SettingService::onTimeout";
    if (-1 != m_Private->m_DVRFileDescriptor) {
        bool ret = m_Private->detectSignal();
        switch (m_Private->m_Timer->interval()) {
        case 11: {
            if (m_Private->m_DetactFlag) {
                m_Private->m_DetactFlag = false;
                m_Private->m_AVStatus = AVS_Detacted;
                if (ret) {
                    emit onAVStatus(m_Private->m_AVType, m_Private->m_AVStatus);
                }
                m_Private->m_Timer->start(1500);
            } else {
                if (!ret) {
                    m_Private->m_DetactFlag = false;
                    bool filter(true);
                    if (AVS_Play == m_Private->m_AVStatus) {
                        m_Private->m_DetactFlag = true;
                        m_Private->m_AVStatus = AVS_NoDetact;
                        m_Private->closeDVRFrameBufferFileDescriptor();
                        m_Private->stopDVRData();
                        filter = false;
                    } else if (AVS_Detacted == m_Private->m_AVStatus) {
                        m_Private->m_AVStatus = AVS_NoDetact;
                        filter = false;
                    }
                    if (!filter) {
                        emit onAVStatus(m_Private->m_AVType, m_Private->m_AVStatus);
                    }
                } else {
                    if (AVS_NoDetact == m_Private->m_AVStatus) {
                        m_Private->m_DetactFlag = true;
                    }
                }
            }
            break;
        }
        case 1500: {
            if (ret) {
                bool filter(true);
                if (AVS_Play != m_Private->m_AVStatus) {
                    if (AVS_Detacted == m_Private->m_AVStatus) {
                        emit onAVStatus(m_Private->m_AVType, m_Private->m_AVStatus);
                        if (AVT_1 == m_Private->m_AVType) {
                            m_Private->configDVR(DVR_SOURCE_CAMERA, m_Private->m_Width, m_Private->m_Height);
                        } else {
                            m_Private->configDVR(DVR_SOURCE_AUX, m_Private->m_Width, m_Private->m_Height);
                        }
                        m_Private->startDVRData();
                        filter = false;
                        if (m_Private->openDVRFrameBufferFileDescriptor()) {
                            m_Private->m_AVStatus = AVS_Play;
                        } else {
                            m_Private->stopDVRData();
                            m_Private->m_AVStatus = AVS_NoDetact;
                        }
                    }
                }
                if (!filter) {
                    emit onAVStatus(m_Private->m_AVType, m_Private->m_AVStatus);
                }
            } else {
                m_Private->m_AVStatus = AVS_NoDetact;
                emit onAVStatus(m_Private->m_AVType, m_Private->m_AVStatus);
            }
            m_Private->m_Timer->start(11);
            break;
        }
        default: {
            break;
        }
        }
    }
}

SettingServicePrivate::SettingServicePrivate(SettingService *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

SettingServicePrivate::~SettingServicePrivate()
{
}

void SettingServicePrivate::initialize()
{
    qDebug() << "SettingServicePrivate::initialize" << qApp->arguments();
    if (ArkMicroSettingService == qApp->applicationName()) {
        bool ret = QDBusConnection::sessionBus().registerService(ArkMicroSettingService);
        ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroSettingPath,
                                                                  m_Parent,
                                                                  QDBusConnection::ExportNonScriptableSignals
                                                                  | QDBusConnection::ExportNonScriptableSlots);
        if (!ret) {
            qCritical() << "SettingService Register QDbus failed!";
            exit(EXIT_FAILURE);
        }
        qDebug() << "SettingService Register QDbus ok!";
    } else {
        qDebug() << "SettingService inner";
    }
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(false);
    m_Timer->setInterval(10);
}

void SettingServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

bool SettingServicePrivate::openDVRFileFileDescriptor()
{
    bool ret(false);
    if (-1 == m_DVRFileDescriptor) {
        m_DVRFileDescriptor = arkapi_open_dvr();
        qDebug() << "arkapi_open_dvr" << m_DVRFileDescriptor;
        if (m_DVRFileDescriptor < 0) {
            printf("open dvr device failure.\n");
        } else {
//            qDebug() << arkapi_dvr_tvout(m_DVRFileDescriptor, 1);
            ret = true;
        }
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool SettingServicePrivate::switchDVRChannel(const dvr_source type)
{
    bool ret(false);
    if (-1 != m_DVRFileDescriptor) {
        if (arkapi_dvr_switch_channel(m_DVRFileDescriptor, type) < 0) {
            printf("switch dvr failure.\n");
        } else {
            ret = true;
        }
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool SettingServicePrivate::configDVR(const dvr_source type, const int width, const int height)
{
    bool ret(false);
    if (-1 != m_DVRFileDescriptor) {
//        char *endptr = "tvout";
//        int tvout = strtoul("tvout", &endptr, 10);
        if (arkapi_dvr_config(m_DVRFileDescriptor, type, width, height, 1) < 0) {
            printf("config dvr failure.\n");
        } else {
            ret = true;
        }
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool SettingServicePrivate::closeDVRFileFileDescriptor()
{
    bool ret(false);
    if (-1 != m_DVRFileDescriptor) {
#ifndef gcc
//        arkapi_dvr_tvout(m_DVRFileDescriptor, 0);
        arkapi_close_dvr(m_DVRFileDescriptor);
#endif
        m_DVRFileDescriptor = -1;
        ret = true;
    }
    return ret;
}

bool SettingServicePrivate::startDVRData()
{
    bool ret(false);
    if (-1 != m_DVRFileDescriptor) {
        if (arkapi_dvr_start(m_DVRFileDescriptor) < 0) {
            printf("open start dvr failure.\n");
        } else {
            ret = true;
        }
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool SettingServicePrivate::stopDVRData()
{
    bool ret(false);
    if (-1 != m_DVRFileDescriptor) {
        arkapi_dvr_stop(m_DVRFileDescriptor);
        ret = true;
    }
    return ret;
}

bool SettingServicePrivate::openDVRFrameBufferFileDescriptor()
{
    bool ret(false);
    if (-1 == m_FrameBufferFileDescriptor) {
        m_FrameBufferFileDescriptor = arkapi_open_video_fb();
        qDebug() << "arkapi_open_video_fb" << m_FrameBufferFileDescriptor;
        if (m_FrameBufferFileDescriptor < 0) {
            printf("open video fb device failure.\n");
        } else {
            ret = true;
        }
    }
    qDebug() << __FUNCTION__ << ret;
    return ret;
}

bool SettingServicePrivate::closeDVRFrameBufferFileDescriptor()
{
    bool ret(false);
    if (-1 != m_FrameBufferFileDescriptor) {
#ifndef gcc
        arkapi_close_video_fb(m_FrameBufferFileDescriptor);
#endif
        m_FrameBufferFileDescriptor = -1;
        ret = true;
    }
    return ret;
}

bool SettingServicePrivate::detectSignal()
{
    int ret = arkapi_dvr_detect_signal(m_DVRFileDescriptor);
    qDebug() << __FUNCTION__ << ret;
    return (0 != ret);
}
