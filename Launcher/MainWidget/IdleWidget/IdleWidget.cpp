#include "IdleWidget.h"
#include "Widget.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include "Setting.h"
#include "AutoConnect.h"
#include <QPainter>
#include <QEvent>

class IdleWidgetPrivate
{
    Q_DISABLE_COPY(IdleWidgetPrivate)
public:
    explicit IdleWidgetPrivate(IdleWidget* parent);
    ~IdleWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
private:
    IdleWidget* m_Parent = NULL;
};

IdleWidget::IdleWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new IdleWidgetPrivate(this))
{
    setVisible(true);
}

IdleWidget::~IdleWidget()
{
}

void IdleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::transparent);
}

void IdleWidget::showEvent(QShowEvent *event)
{
    if (NULL != m_Private) {
        m_Private->receiveAllCustomEvent();
        m_Private->connectAllSlots();
    }
}

void IdleWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void IdleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    g_Setting->setDisplayScreen(DST_On);
}

void IdleWidget::customEvent(QEvent *event)
{
    qDebug() << "IdleWidget::customEvent" << event->type();
    if (CustomEventType::IdleWidgetStatus == event->type()) {
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                g_Setting->setDisplayScreen(DST_Off);
            } else if (WidgetStatus::RequestHide == *temp) {
                g_Setting->setDisplayScreen(DST_On);
            }
        }
    }
    QWidget::customEvent(event);
}

void IdleWidget::onDisplayScreenChange(const DisplayScreenType type)
{
    qDebug() << "IdleWidget::onDisplayScreenChange" << type;
    switch (type) {
    case DST_Off: {
        setVisible(true);
        break;
    }
    case DST_On: {
        setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}

IdleWidgetPrivate::IdleWidgetPrivate(IdleWidget *parent)
    : m_Parent(parent)
{
    initialize();
}

IdleWidgetPrivate::~IdleWidgetPrivate()
{
}

void IdleWidgetPrivate::initialize()
{
}

void IdleWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void IdleWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
}
