#include "MessageBoxWidget.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include <QEvent>
#include <QPainter>
#include <QVariant>

class MessageBoxWidgetPrivate
{
    Q_DISABLE_COPY(MessageBoxWidgetPrivate)
public:
    explicit MessageBoxWidgetPrivate(MessageBoxWidget *parent);
    ~MessageBoxWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
private:
    MessageBoxWidget* m_Parent = NULL;
};

MessageBoxWidget::MessageBoxWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MessageBoxWidgetPrivate(this))
{
}

MessageBoxWidget::~MessageBoxWidget()
{
}

void MessageBoxWidget::customEvent(QEvent *event)
{
    qDebug() << "MessageBoxWidget::customEvent" << event->type();
    if (CustomEventType::MessageBoxWidgetAddChild == event->type()) {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
    } else if (CustomEventType::MessageBoxWidgetStatus == event->type()) {
        EventEngine::CustomEvent<QString>* ptr = dynamic_cast<EventEngine::CustomEvent<QString>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)) {
            if (WidgetStatus::RequestShow == (*ptr->m_Data)) {
                setVisible(true);
                qDebug() << "WidgetStatus::RequestShow" << isVisible();
            } else if (WidgetStatus::RequestHide == (*ptr->m_Data)) {
                setVisible(false);
            }
        }
    }
}

void MessageBoxWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void MessageBoxWidget::paintEvent(QPaintEvent *event)
{
}

MessageBoxWidgetPrivate::MessageBoxWidgetPrivate(MessageBoxWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
}

MessageBoxWidgetPrivate::~MessageBoxWidgetPrivate()
{
}

void MessageBoxWidgetPrivate::initialize()
{
}

void MessageBoxWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
