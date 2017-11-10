#include "StatusBarWidget.h"
#include "BmpWidget.h"
#include "TextWidget.h"
#include "Utility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QEvent>
#include <QVariant>
#include <QByteArray>
#include <QDataStream>
#include <QFile>

namespace SourceString {
static const QString Home = QString(QObject::tr("Home"));
static const QString SD_Files = QString(QObject::tr("SD>Files"));
static const QString USB_Files = QString(QObject::tr("USB>Files"));
static const QString Music = QString(QObject::tr("Music"));
static const QString Link = QString(QObject::tr("Link"));
static const QString Setting_General = QString(QObject::tr("Setting>General"));
static const QString Setting_Language = QString(QObject::tr("Setting>Language"));
static const QString Setting_Effect = QString(QObject::tr("Setting>Effect"));
static const QString Setting_Field = QString(QObject::tr("Setting>Field"));
static const QString Setting_Version = QString(QObject::tr("Setting>Version"));
static const QString AV1 = QString(QObject::tr("AV1"));
static const QString AV2 = QString(QObject::tr("AV2"));
}

class StatusBarWidgetPrivate
{
    Q_DISABLE_COPY(StatusBarWidgetPrivate)
public:
    explicit StatusBarWidgetPrivate(StatusBarWidget *parent);
    ~StatusBarWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
//    BmpWidget* m_Background = NULL;
    TextWidget* m_TitleText = NULL;
    QByteArray m_ByteArray;
    QImage* m_Background = NULL;
private:
    StatusBarWidget* m_Parent = NULL;
};

StatusBarWidget::StatusBarWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new StatusBarWidgetPrivate(this))
{
    setVisible(true);
}

StatusBarWidget::~StatusBarWidget()
{
}

void StatusBarWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseStatusBarHeight(), this);
}

void StatusBarWidget::customEvent(QEvent* event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::StatusBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void StatusBarWidget::paintEvent(QPaintEvent *event)
{
    if ((NULL != m_Private)
            && (NULL != m_Private->m_Background)
            && (!m_Private->m_Background->isNull())) {
        QPainter painter(this);
        painter.drawImage(g_Widget->geometryFit(0, 0, m_Private->m_Background->width(), m_Private->m_Background->height()), *m_Private->m_Background);
    }
}

void StatusBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_Home: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Home);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Link: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Link);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Music: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Music);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SDDisk:
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::SD_Files);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_USBDisk:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::USB_Files);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingGeneral: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_General);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingLanguage: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Language);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingEffect: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Effect);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingField: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Field);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingVersion: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Version);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV1: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::AV1);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV1FullScreen: {
            setVisible(false);
//            m_Private->m_Background->setVisible(false);
            m_Private->m_TitleText->setVisible(false);
            break;
        }
        case Widget::T_AV2: {
//            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::AV2);
            m_Private->m_TitleText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV2FullScreen: {
            setVisible(false);
//            m_Private->m_Background->setVisible(false);
            m_Private->m_TitleText->setVisible(false);
            break;
        }
        case Widget::T_Mirror:
        case Widget::T_Carplay:
        case Widget::T_Video:
        case Widget::T_VideoFullScreen:
        case Widget::T_Image:
        case Widget::T_ImageFullScreen: {
            setVisible(false);
//            m_Private->m_Background->setVisible(false);
            m_Private->m_TitleText->setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
    }
}

StatusBarWidgetPrivate::StatusBarWidgetPrivate(StatusBarWidget* parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
}

StatusBarWidgetPrivate::~StatusBarWidgetPrivate()
{
}

void StatusBarWidgetPrivate::initialize()
{
    if (NULL == m_Background) {
        QFile file(":/Images/Resources/Images/StatusBarWidgetBackground.dat");
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);
            stream >> m_ByteArray;
            file.close();
            m_Background = new QImage((const uchar *)m_ByteArray.data(), 1280, 60, QImage::Format_RGB32);
        }
//        m_Background = new QImage();
//        m_Background = new BmpWidget(m_Parent);
//        m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackground"));
//        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), height, m_Background);
//        m_Background->setVisible(true);
    }
//    if (NULL == m_Background) {
//        m_Background = new BmpWidget(m_Parent);
//        m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/StatusBarWidgetBackground"));
//        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), 60, m_Background);
//        m_Background->setVisible(true);
//    }
    if (NULL == m_TitleText) {
        m_TitleText = new TextWidget(m_Parent);
        m_TitleText->setFontPointSize(26 * g_Widget->widthScalabilityFactor());
        m_TitleText->setText(SourceString::Home);
        g_Widget->geometryFit(426, 0, 426, 60, m_TitleText);
        m_TitleText->setVisible(true);
    }
}

void StatusBarWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void StatusBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}

