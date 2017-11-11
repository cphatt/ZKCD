#include "HomeWidget.h"
#include "TextWidget.h"
#include "BmpButton.h"
#include "UserInterfaceUtility.h"
#include "AutoConnect.h"
#include "Setting.h"
#include "BmpWidget.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include "RunnableThread.h"
#include "UserInterfaceUtility.h"
#include <QByteArray>
#include <QPainter>
#include <QMouseEvent>
#include <QMap>
#include <QByteArray>
#include <QDataStream>
#include <QFile>

namespace SourceString {
static const QString SD = QString(QObject::tr("SD"));
static const QString USB = QString(QObject::tr("USB"));
static const QString Link = QString(QObject::tr("Link"));
static const QString AV1 = QString(QObject::tr("AV1"));
static const QString AV2 = QString(QObject::tr("AV2"));
static const QString Setting = QString(QObject::tr("Setting"));
}

class HomeWidgetPrivate
{
    Q_DISABLE_COPY(HomeWidgetPrivate)
public:
    enum Type {
        T_Undefine = -1,
        T_SD = 0,
        T_USB = 1,
        T_Link = 2,
        T_AV1 = 3,
        T_AV2 = 4,
        T_Setting = 5
    };
    struct ToolButtonData {
        QRect touchRect;
        QRect textRect;
        QString text;
        QByteArray byteArray;
        QImage* normalImage = NULL;
        QImage pressImage;
        bool press = false;
    };
    explicit HomeWidgetPrivate(HomeWidget *parent);
    ~HomeWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    void onBmpButtonRelease(const HomeWidgetPrivate::Type type);
    QMap<HomeWidgetPrivate::Type, struct ToolButtonData> m_ToolButtonMap;
    HomeWidgetPrivate::Type m_Type = HomeWidgetPrivate::T_Undefine;
    QImage* m_Background = NULL;
    QByteArray m_ByteArray;
private:
    HomeWidget* m_Parent = NULL;
};

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new HomeWidgetPrivate(this))
{
    setVisible(true);
}

HomeWidget::~HomeWidget()
{
}

void HomeWidget::mousePressEvent(QMouseEvent *event)
{
    for (int i = 0; i < m_Private->m_ToolButtonMap.size(); ++i) {
        m_Private->m_Type = static_cast<HomeWidgetPrivate::Type>(i);
        if (m_Private->m_ToolButtonMap[m_Private->m_Type].touchRect.contains(event->pos())) {
            m_Private->m_ToolButtonMap[m_Private->m_Type].press = true;
            if (m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.isNull()) {
                switch (m_Private->m_Type) {
                case HomeWidgetPrivate::T_SD: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetSDDiskPress"));
                    break;
                }
                case HomeWidgetPrivate::T_USB: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetUSBDiskPress"));
                    break;
                }
                case HomeWidgetPrivate::T_Link: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetLinkPress"));
                    break;
                }
                case HomeWidgetPrivate::T_AV1: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetAVPress"));
                    break;
                }
                case HomeWidgetPrivate::T_AV2: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetAVPress"));
                    break;
                }
                case HomeWidgetPrivate::T_Setting: {
                    m_Private->m_ToolButtonMap[m_Private->m_Type].pressImage.load(QString(":/Images/Resources/Images/HomeWidgetSettingPress"));
                    break;
                }
                default: {
                    break;
                }
                }
            }
            update();
            qApp->flush();
            qApp->sendPostedEvents();
            return;
        }
    }
}

void HomeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_Private->m_ToolButtonMap[m_Private->m_Type].press = false;
    m_Private->onBmpButtonRelease(m_Private->m_Type);
    m_Private->m_Type = HomeWidgetPrivate::T_Undefine;
    update();
}

void HomeWidget::showEvent(QShowEvent *event)
{
}

void HomeWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, g_Widget->baseStatusBarHeight(), g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - g_Widget->baseStatusBarHeight() - g_Widget->baseTabBarHeight(), this);
}

void HomeWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void HomeWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
//        m_Private->connectAllSlots();
        break;
    }
    default: {
        break;
    }
    }
}

void HomeWidget::paintEvent(QPaintEvent *event)
{
    if ((NULL != m_Private)
            && (NULL != m_Private->m_Background)
            && (!m_Private->m_Background->isNull())) {
        QPainter painter(this);
        painter.drawImage(g_Widget->geometryFit(0, 0, m_Private->m_Background->width(), m_Private->m_Background->height()), *m_Private->m_Background);
        for (int i = 0; i < m_Private->m_ToolButtonMap.size(); ++i) {
            painter.setPen(Qt::white);
            QFont font;
            font.setPointSize(25 * g_Widget->widthScalabilityFactor());
            if (!m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].press) {
                if (!m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage->isNull()) {
                    int x = m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.x() + (m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.width() - m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage->width() * g_Widget->widthScalabilityFactor()) * 0.5;
                    int y = m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.y() + (m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.height() - m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage->height() * g_Widget->heightScalabilityFactor()) * 0.5;
                    painter.drawImage(QRect(x, y, m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage->width() * g_Widget->widthScalabilityFactor(), m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage->height() * g_Widget->heightScalabilityFactor()), *m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].normalImage);
                }
            } else {
                if (!m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage.isNull()) {
                    int x = m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.x() + (m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.width() - m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage.width() * g_Widget->widthScalabilityFactor()) * 0.5;
                    int y = m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.y() + (m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].touchRect.height() - m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage.height() * g_Widget->heightScalabilityFactor()) * 0.5;
                    painter.drawImage(QRect(x, y, m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage.width() * g_Widget->widthScalabilityFactor(), m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage.height() * g_Widget->heightScalabilityFactor()), m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].pressImage);
                }
            }
            painter.drawText(m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].textRect, Qt::AlignLeft | Qt::AlignVCenter, QObject::tr(m_Private->m_ToolButtonMap[static_cast<HomeWidgetPrivate::Type>(i)].text.toLocal8Bit().constData()));
        }
    }
}

void HomeWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Home: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            lower();
            setVisible(true);
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    }
}

HomeWidgetPrivate::HomeWidgetPrivate(HomeWidget *parent)
    : m_Parent(parent)
{
    m_ToolButtonMap.clear();
    initialize();
    connectAllSlots();
    receiveAllCustomEvent();

  //   g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
}

HomeWidgetPrivate::~HomeWidgetPrivate()
{
}

static void initializeRunnableCallback(void *paramater)
{
    qWarning() << "initializeRunnableCallback" << paramater;
    HomeWidgetPrivate *ptr = static_cast<HomeWidgetPrivate *>(paramater);
    if (NULL != ptr) {
        QTime time;
        qWarning() << "ptr->initializeRunnableCallback";
        time.start();
        if (NULL == ptr->m_Background) {
            QFile file(":/Images/Resources/Images/HomeWidgetBackground.dat");
            if (file.open(QIODevice::ReadOnly)) {
                QDataStream stream(&file);
                stream >> ptr->m_ByteArray;
                file.close();
                ptr->m_Background = new QImage((const uchar *)ptr->m_ByteArray.data(), 1280, 576, QImage::Format_RGB32);
            }
        }
        //        if (ptr->m_Background->isNull()) {
        //            ptr->m_Background->load(QString(":/Images/Resources/Images/HomeWidgetBackground"));
        //        }
        qWarning() << time.elapsed() << "-------2222";
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_SD].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_SD].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetSDDiskNormall"));
        }
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_USB].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_USB].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetUSBDiskNormall"));
        }
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_Link].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_Link].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetLinkNormall"));
        }
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_AV1].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_AV1].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetAVNormall"));
        }
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_AV2].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_AV2].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetAVNormall"));
        }
        if (ptr->m_ToolButtonMap[HomeWidgetPrivate::T_Setting].normalImage->isNull()) {
            ptr->m_ToolButtonMap[HomeWidgetPrivate::T_Setting].normalImage->load(QString(":/Images/Resources/Images/HomeWidgetSettingNormal"));
        }
    }
}

void HomeWidgetPrivate::initialize()
{
    int bmpWidth(418);
    int bmpHeight(348 - 73);
    struct ToolButtonData toolButtonData;
    toolButtonData.press = false;
    toolButtonData.text = SourceString::SD;
    toolButtonData.touchRect = g_Widget->geometryFit(0, 73 - 73 + 7, bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(0 + 52, 73 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_SD, toolButtonData);
    toolButtonData.text = SourceString::USB;
    toolButtonData.touchRect = g_Widget->geometryFit(1 + 0 + 418 + 12, 73 - 73 + 7, bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(1 + 0 + 418 + 12 + 52, 73 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_USB, toolButtonData);
    toolButtonData.text = SourceString::Link;
    toolButtonData.touchRect = g_Widget->geometryFit(1 + 431 + 418 + 12, 73 - 73 + 7,  bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(1 + 431 + 418 + 12 + 52, 73 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_Link, toolButtonData);
    toolButtonData.text = SourceString::AV1;
    toolButtonData.touchRect = g_Widget->geometryFit(0, 361 - 73 + 7, bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(0 + 52, 361 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_AV1, toolButtonData);
    toolButtonData.text = SourceString::AV2;
    toolButtonData.touchRect = g_Widget->geometryFit(1 + 0 + 418 + 12, 361 - 73 + 7, bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(1 + 0 + 418 + 12 + 52, 361 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_AV2, toolButtonData);
    toolButtonData.text = SourceString::Setting;
    toolButtonData.touchRect = g_Widget->geometryFit(1 + 431 + 418 + 12, 361 - 73 + 7, bmpWidth, bmpHeight);
    toolButtonData.textRect = g_Widget->geometryFit(1 + 431 + 418 + 12 + 52, 361 - 73 + 7 + 275 - 55, bmpWidth * 0.75, 40);
    m_ToolButtonMap.insert(HomeWidgetPrivate::T_Setting, toolButtonData);
    QTime time;
    time.start();
    qWarning() << "ptr->initializeRunnableCallback";
    if (NULL == m_Background) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetBackground.dat"), m_ByteArray)) {
        //            m_Background = new QImage(HomeWidgetBackground, 1280, 576, QImage::Format_RGB32);
        m_Background = new QImage(QString(":/Images/Resources/Images/HomeWidgetBackground.png"));
        //        }
    }
    qWarning() << time.elapsed() << "-------2222";
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_SD].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetSDDiskNormall.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_SD].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_SD].normalImage = new QImage(HomeWidgetSDDiskNormall, 82, 101, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_SD].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetSDDiskNormall.png"));
        //        }
    }
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_USB].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetUSBDiskNormall.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_USB].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_USB].normalImage = new QImage(HomeWidgetUSBDiskNormall, 182, 74, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_USB].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetUSBDiskNormall.png"));
        //        }
    }
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_Link].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetLinkNormall.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_Link].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_Link].normalImage = new QImage(HomeWidgetLinkNormall, 124, 111, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_Link].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetLinkNormall.png"));
        //        }
    }
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_AV1].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetAVNormall.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_AV1].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_AV1].normalImage = new QImage(HomeWidgetAVNormall, 109, 109, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_AV1].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetAVNormall.png"));
        //        }
    }
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_AV2].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetAVNormall.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_AV2].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_AV2].normalImage = new QImage(HomeWidgetAVNormall, 109, 109, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_AV2].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetAVNormall.png"));
        //        }
    }
    if (NULL == m_ToolButtonMap[HomeWidgetPrivate::T_Setting].normalImage) {
        //        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/HomeWidgetSettingNormal.dat"), m_ToolButtonMap[HomeWidgetPrivate::T_Setting].byteArray)) {
        //            m_ToolButtonMap[HomeWidgetPrivate::T_Setting].normalImage = new QImage(HomeWidgetSettingNormal, 113, 113, QImage::Format_ARGB32);
        m_ToolButtonMap[HomeWidgetPrivate::T_Setting].normalImage = new QImage(QString(":/Images/Resources/Images/HomeWidgetSettingNormal.png"));
        //        }
    }
    qWarning() << time.elapsed() << "-------3333";
}

void HomeWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}

void HomeWidgetPrivate::onBmpButtonRelease(const HomeWidgetPrivate::Type type)
{
    if (m_Parent->isVisible()) {
        switch (type) {
        case HomeWidgetPrivate::T_SD: {
            g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::RequestShow);
            break;
        }
        case HomeWidgetPrivate::T_USB: {
            g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::RequestShow);
            break;
        }
        case HomeWidgetPrivate::T_Link: {
            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
            break;
        }
        case HomeWidgetPrivate::T_AV1: {
            g_Widget->setWidgetType(Widget::T_AV1, WidgetStatus::RequestShow);
            break;
        }
        case HomeWidgetPrivate::T_AV2: {
            g_Widget->setWidgetType(Widget::T_AV2, WidgetStatus::RequestShow);
            break;
        }
        case HomeWidgetPrivate::T_Setting: {
            g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::RequestShow);
            break;
        }
        default: {
            break;
        }
        }
    }
}
