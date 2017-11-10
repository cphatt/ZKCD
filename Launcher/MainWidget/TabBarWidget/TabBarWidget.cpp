#include "TabBarWidget.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "UserInterfaceUtility.h"
#include "Widget.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "AutoConnect.h"
#include "Audio.h"
#include "UserInterfaceUtility.h"
#include "RunnableThread.h"
#include <QEvent>
#include <QPainter>
#include <QVariant>
#include <QByteArray>

class TabBarWidgetPrivate
{
    Q_DISABLE_COPY(TabBarWidgetPrivate)
public:
    explicit TabBarWidgetPrivate(TabBarWidget *parent);
    ~TabBarWidgetPrivate();
    void initializeBasicWidget();
    void initializeOtherWidget();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_TurnOffDisplayBtn = NULL;
    BmpButton* m_HomeBtn = NULL;
    BmpButton* m_BackBtn = NULL;
    BmpButton* m_FMBtn = NULL;
    BmpButton* m_IRBtn = NULL;
    BmpButton* m_VolumeBtn = NULL;
//    BmpWidget* m_Background = NULL;
    QByteArray m_ByteArray;
    QImage* m_Background = NULL;
private:
    TabBarWidget* m_Parent = NULL;
};

TabBarWidget::TabBarWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new TabBarWidgetPrivate(this))
{
    setVisible(true);
}

TabBarWidget::~TabBarWidget()
{
}

void TabBarWidget::resizeEvent(QResizeEvent *event)
{
    int height(g_Widget->baseTabBarHeight());
    g_Widget->geometryFit(0, g_Widget->baseWindowHeight() - height, g_Widget->baseWindowWidth(), height, this);
}

void TabBarWidget::customEvent(QEvent *event)
{
    qDebug() << "TabBarWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::TabBarWidgetAddChild: {
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

void TabBarWidget::paintEvent(QPaintEvent *event)
{
    if ((NULL != m_Private)
            && (NULL != m_Private->m_Background)
            && (!m_Private->m_Background->isNull())) {
        QPainter painter(this);
        painter.drawImage(g_Widget->geometryFit(0, 0, m_Private->m_Background->width(), m_Private->m_Background->height()), *m_Private->m_Background);
    }
}

void TabBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status)
        switch (type) {
        case Widget::T_Home: {
            m_Private->initializeOtherWidget();
            m_Private->m_TurnOffDisplayBtn->setVisible(true);
            m_Private->m_HomeBtn->setVisible(false);
            m_Private->m_BackBtn->setVisible(false);
            m_Private->m_FMBtn->setVisible(true);
            m_Private->m_IRBtn->setVisible(true);
            m_Private->m_VolumeBtn->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SDDisk:
        case Widget::T_USBDisk:
        case Widget::T_Music:
        case Widget::T_AV1:
        case Widget::T_AV2:
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo:
        case Widget::T_Link:
        case Widget::T_SettingGeneral:
        case Widget::T_SettingLanguage:
        case Widget::T_SettingEffect:
        case Widget::T_SettingField:
        case Widget::T_SettingVersion: {
            m_Private->initializeOtherWidget();
            m_Private->m_TurnOffDisplayBtn->setVisible(false);
            m_Private->m_HomeBtn->setVisible(true);
            m_Private->m_BackBtn->setVisible(true);
            m_Private->m_FMBtn->setVisible(true);
            m_Private->m_IRBtn->setVisible(true);
            m_Private->m_VolumeBtn->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Mirror:
        case Widget::T_Carplay:
        case Widget::T_AV1FullScreen:
        case Widget::T_AV2FullScreen:
        case Widget::T_Image:
        case Widget::T_ImageFullScreen:
        case Widget::T_Video:
        case Widget::T_VideoFullScreen: {
            setVisible(false);
            m_Private->m_TurnOffDisplayBtn->setVisible(false);
            m_Private->m_HomeBtn->setVisible(false);
            m_Private->m_BackBtn->setVisible(false);
            m_Private->m_FMBtn->setVisible(false);
            m_Private->m_IRBtn->setVisible(false);
            m_Private->m_VolumeBtn->setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
}

void TabBarWidget::onTabBarButtonRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if(ptr == m_Private->m_TurnOffDisplayBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::IdleWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_HomeBtn) {
        g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
    } else if (ptr == m_Private->m_FMBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_IRBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::IRWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_VolumeBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_BackBtn) {
        g_Widget->setWidgetType(Widget::T_Back, WidgetStatus::RequestShow);
    }
}

TabBarWidgetPrivate::TabBarWidgetPrivate(TabBarWidget *parent)
    : m_Parent(parent)
{
    initializeBasicWidget();
    receiveAllCustomEvent();
}

TabBarWidgetPrivate::~TabBarWidgetPrivate()
{
}

void TabBarWidgetPrivate::initializeBasicWidget()
{
    int width(84);
    int height(g_Widget->baseTabBarHeight());
    if (NULL == m_Background) {
//        if (UserInterfaceUtility::loadFromdata(QString(":/Images/Resources/Images/TabBarWidgetBackground.dat"), m_ByteArray)) {
//            m_Background = new QImage(TabBarWidgetBackground, 1280, 84, QImage::Format_RGB32);
            m_Background = new QImage(QString(":/Images/Resources/Images/TabBarWidgetBackground.png"));
//        }
    }
    if (NULL == m_TurnOffDisplayBtn) {
        m_TurnOffDisplayBtn = new BmpButton(m_Parent);
        m_TurnOffDisplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetTurnOffDisplayBtnNormal"));
        m_TurnOffDisplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetTurnOffDisplayBtnNormal"));
        g_Widget->geometryFit(1112 + (1196 - 1112 - width) * 0.5, 0, width, height, m_TurnOffDisplayBtn);
        m_TurnOffDisplayBtn->setVisible(true);
    }
    if (NULL == m_FMBtn) {
        m_FMBtn = new BmpButton(m_Parent);
        m_FMBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetFMBtnNormal"));
        m_FMBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetFMBtnNormal"));
        g_Widget->geometryFit(608 + (692 - 608 - width) * 0.5, 0, width, height, m_FMBtn);
        m_FMBtn->setVisible(true);
    }
    if (NULL == m_IRBtn) {
        m_IRBtn = new BmpButton(m_Parent);
        m_IRBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetIRBtnNormal"));
        m_IRBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetIRBtnNormal"));
        g_Widget->geometryFit(776 + (860 - 776 - width) * 0.5, 0, width, height, m_IRBtn);
        m_IRBtn->setVisible(true);
    }
    if (NULL == m_VolumeBtn) {
        m_VolumeBtn = new BmpButton(m_Parent);
        m_VolumeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
        m_VolumeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
        g_Widget->geometryFit(944 + (1028 - 944 - width) * 0.5, 0, width, height, m_VolumeBtn);
        m_VolumeBtn->setVisible(true);
    }
}

void TabBarWidgetPrivate::initializeOtherWidget()
{
    int width(84);
    int height(g_Widget->baseTabBarHeight());
    if (NULL == m_HomeBtn) {
        m_HomeBtn = new BmpButton(m_Parent);
        m_HomeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetHomeBtnNormal"));
        m_HomeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetHomeBtnNormal"));
        g_Widget->geometryFit(84 + (168 - 84 - width) * 0.5, 0, width, height, m_HomeBtn);
    }
    if (NULL == m_BackBtn) {
        m_BackBtn = new BmpButton(m_Parent);
        m_BackBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackBtnNormal"));
        m_BackBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackBtnNormal"));
        g_Widget->geometryFit(1112 + (1196 - 1112 - width) * 0.5, 0, width, height, m_BackBtn);
    }
    connectAllSlots();
}

void TabBarWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void TabBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    if (NULL != m_TurnOffDisplayBtn) {
        QObject::connect(m_TurnOffDisplayBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,            SLOT(onTabBarButtonRelease()),
                         type);
    }
    if (NULL != m_HomeBtn) {
        QObject::connect(m_HomeBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,  SLOT(onTabBarButtonRelease()),
                         type);
    }
    if (NULL != m_FMBtn) {
        QObject::connect(m_FMBtn,  SIGNAL(bmpButtonRelease()),
                         m_Parent, SLOT(onTabBarButtonRelease()),
                         type);
    }
    if (NULL != m_IRBtn) {
        QObject::connect(m_IRBtn,  SIGNAL(bmpButtonRelease()),
                         m_Parent, SLOT(onTabBarButtonRelease()),
                         type);
    }
    if (NULL != m_VolumeBtn) {
        QObject::connect(m_VolumeBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,    SLOT(onTabBarButtonRelease()),
                         type);
    }
    if (NULL != m_BackBtn) {
        QObject::connect(m_BackBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,  SLOT(onTabBarButtonRelease()),
                         type);
    }
}
