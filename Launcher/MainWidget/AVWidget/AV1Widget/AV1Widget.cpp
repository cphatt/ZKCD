#include "AV1Widget.h"
#include "AutoConnect.h"
#include "MessageBox.h"
#include "UserInterfaceUtility.h"
#include "BmpWidget.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

namespace SourceString {
static const QString No_AV1_Signal = QString(QObject::tr("No AV1 Signal..."));
static const QString Conneting_AV1_Signal = QString(QObject::tr("Conneting AV1 Signal..."));
}

class AV1WidgetPrivate
{
    Q_DISABLE_COPY(AV1WidgetPrivate)
public:
    explicit AV1WidgetPrivate(AV1Widget* parent);
    ~AV1WidgetPrivate();
    void initializeTimer();
    void initializeShortCutWidget();
    void initializeMessageBox();
    QColor m_BackgroundColor = UserInterfaceUtility::customBlackColor();
    BmpWidget* m_ShortCutWidget = NULL;
    QTimer* m_Timer = NULL;
    MessageBox* m_DeviceMessageBox = NULL;
    QRect m_TouchRect = QRect(0, 0, 0, 0);
    bool m_ShowFlag = false;
private:
    AV1Widget* m_Parent = NULL;
};

AV1Widget::AV1Widget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new AV1WidgetPrivate(this))
{
}

AV1Widget::~AV1Widget()
{
}

void AV1Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
}

void AV1Widget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_DeviceMessageBox);
}

void AV1Widget::mousePressEvent(QMouseEvent *event)
{
    if (isVisible()) {
        if (m_Private->m_TouchRect.contains(event->pos())) {
            if (m_Private->m_TouchRect == QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight())) {
                g_Widget->setWidgetType(Widget::T_AV1, WidgetStatus::Show);
            } else {
                g_Widget->setWidgetType(Widget::T_AV1FullScreen, WidgetStatus::Show);
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void AV1Widget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "AV1Widget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (WidgetStatus::RequestShow == status) {
            if (isVisible()) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_AV1: {
        if (WidgetStatus::RequestShow == status) {
            connectSignalAndSlotByNamesake(g_AV, this);
            g_AV->startAV(AVT_1, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor());
        } else if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = QRect(0, 50, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - 50 - 70);
            m_Private->initializeTimer();
            m_Private->m_Timer->start();
            m_Private->m_ShowFlag = true;
            setVisible(true);
        }
        break;
    }
    case Widget::T_AV1FullScreen: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_AV1FullScreen, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
            m_Private->initializeTimer();
            m_Private->m_Timer->stop();
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            m_Private->initializeMessageBox();
            m_Private->m_DeviceMessageBox->setVisible(false);
            setVisible(false);
            if (m_Private->m_ShowFlag) {
                g_AV->stopAV(AVT_1);
                m_Private->initializeShortCutWidget();
                m_Private->m_ShortCutWidget->setVisible(false);
            }
            m_Private->m_ShowFlag = false;
            m_Private->initializeTimer();
            m_Private->m_Timer->stop();
        }
        break;
    }
    }
}

void AV1Widget::onAVStatus(const int type, const int status)
{
    if (AVT_1 == type) {
        if (AVS_Detacting == status) {
            m_Private->m_BackgroundColor = UserInterfaceUtility::customBlackColor();
            m_Private->initializeMessageBox();
            m_Private->m_DeviceMessageBox->setText(SourceString::Conneting_AV1_Signal);
            m_Private->m_DeviceMessageBox->setVisible(true);
            g_Widget->setWidgetType(Widget::T_AV1, WidgetStatus::Show);
            update();
        } else if (AVS_Detacted == status) {
            m_Private->initializeShortCutWidget();
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ShortCutWidget));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), m_Private->m_ShortCutWidget);
        } else if (AVS_Play == status) {
            m_Private->initializeShortCutWidget();
            if (m_Private->m_ShortCutWidget->isHidden()) {
                QVariant* variant = new QVariant();
                variant->setValue(static_cast<QWidget*>(m_Private->m_ShortCutWidget));
                EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
                g_EventEngine->sendCustomEvent(event);
                g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), m_Private->m_ShortCutWidget);
            }
            m_Private->m_BackgroundColor = UserInterfaceUtility::videoColor();
            m_Private->initializeMessageBox();
            m_Private->m_DeviceMessageBox->setVisible(false);
            update();
        } else if (AVS_NoDetact == status) {
            m_Private->m_BackgroundColor = UserInterfaceUtility::customBlackColor();
            m_Private->initializeMessageBox();
            m_Private->m_DeviceMessageBox->setText(SourceString::No_AV1_Signal);
            m_Private->m_DeviceMessageBox->setVisible(true);
            if (isVisible()) {
                g_Widget->setWidgetType(Widget::T_AV1, WidgetStatus::Show);
            }
        }
    }
}

void AV1Widget::onTimeout()
{
    qDebug() << "AV1Widget::onTimeout";
    g_Widget->setWidgetType(Widget::T_AV1FullScreen, WidgetStatus::RequestShow);
}

AV1WidgetPrivate::AV1WidgetPrivate(AV1Widget *parent)
    : m_Parent(parent)
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}

AV1WidgetPrivate::~AV1WidgetPrivate()
{
}

void AV1WidgetPrivate::initializeTimer()
{
    if (NULL == m_Timer) {
        m_Timer = new QTimer(m_Parent);
        m_Timer->setSingleShot(true);
        m_Timer->setInterval(7000);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
        QObject::connect(m_Timer,  SIGNAL(timeout()),
                         m_Parent, SLOT(onTimeout()),
                         type);
    }
}

void AV1WidgetPrivate::initializeShortCutWidget()
{
    if (NULL == m_ShortCutWidget) {
        m_ShortCutWidget = new BmpWidget(m_Parent);
        m_ShortCutWidget->hide();
    }
}

void AV1WidgetPrivate::initializeMessageBox()
{
    if (NULL == m_DeviceMessageBox) {
        m_DeviceMessageBox = new MessageBox(m_Parent);
        m_DeviceMessageBox->hide();
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    }
}
