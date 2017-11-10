#include "AVWidget.h"
#include "AV1Widget/AV1Widget.h"
#include "AV2Widget/AV2Widget.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include <QTimer>
#include <QRect>
#include <QPainter>

class AVWidgetPrivate
{
    Q_DISABLE_COPY(AVWidgetPrivate)
public:
    explicit AVWidgetPrivate(AVWidget* parent);
    ~AVWidgetPrivate();
    void initializeAV1Widget();
    void initializeAV2Widget();
    void connectAllSlots();
    AV1Widget* m_AV1Widget = NULL;
    AV2Widget* m_AV2Widget = NULL;
    QTimer* m_Timer = NULL;
    QRect m_TouchRect = QRect(0, 0, 0, 0);
private:
    AVWidget* m_Parent = NULL;
};

AVWidget::AVWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new AVWidgetPrivate(this))
{
}

AVWidget::~AVWidget()
{
}

void AVWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void AVWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), UserInterfaceUtility::mainWidgetBackgroundColor());
}

void AVWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_AV1:
    case Widget::T_AV1FullScreen: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->initializeAV1Widget();
        } else if (WidgetStatus::Show == status) {
            lower();
            setVisible(true);
        }
        break;
    }
    case Widget::T_AV2:
    case Widget::T_AV2FullScreen: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->initializeAV2Widget();
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

AVWidgetPrivate::AVWidgetPrivate(AVWidget *parent)
    : m_Parent(parent)
{
    m_AV1Widget = NULL;
    m_AV2Widget = NULL;
    initializeAV1Widget();
    initializeAV2Widget();
    connectAllSlots();
}

AVWidgetPrivate::~AVWidgetPrivate()
{
}

void AVWidgetPrivate::initializeAV1Widget()
{
    if (NULL == m_AV1Widget) {
        m_AV1Widget = new AV1Widget(m_Parent);
    }
}

void AVWidgetPrivate::initializeAV2Widget()
{
    if (NULL == m_AV2Widget) {
        m_AV2Widget = new AV2Widget(m_Parent);
    }
}

void AVWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
