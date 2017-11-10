#include "IRWidget.h"
#include "BusinessLogicUtility.h"
#include "IRToolWidget/IRToolWidget.h"
#include "EventEngine.h"
#include "Widget.h"
#include "Audio.h"
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>

class IRWidgetPrivate
{
    Q_DISABLE_COPY(IRWidgetPrivate)
public:
    explicit IRWidgetPrivate(IRWidget* parent);
    ~IRWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    IRToolWidget* m_IRToolWidget = NULL;
    QTimer* m_Timer = NULL;
private:
    IRWidget* m_Parent = NULL;
};


IRWidget::IRWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new IRWidgetPrivate(this))
{
    setVisible(true);
}

IRWidget::~IRWidget()
{
}

void IRWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
}

void IRWidget::customEvent(QEvent *event)
{
    qDebug() << "IRWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::IRWidgetStatus: {
        EventEngine::CustomEvent<QString> event1(CustomEventType::VolumeWidgetStatus, NULL);
        g_EventEngine->sendCustomEvent(event1);
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                m_Private->initialize();
                m_Private->m_Timer->start();
                setVisible(true);
            } else if (WidgetStatus::RequestHide == *temp) {
                m_Private->m_Timer->stop();
                setVisible(false);
            }
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void IRWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void IRWidget::mousePressEvent(QMouseEvent *event)
{
    if (isVisible()
            && g_Widget->geometryFit(213, 180, 853, 360).contains(event->pos())) {
        m_Private->m_Timer->stop();
    }
}

void IRWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()
            && (!g_Widget->geometryFit(213, 180, 853, 360).contains(event->pos()))
            && m_Private->m_Timer->isActive()) {
        m_Private->m_Timer->stop();
        setVisible(false);
    } else {
        m_Private->m_Timer->start();
    }
}

void IRWidget::onTimeout()
{
    m_Private->m_Timer->stop();
    setVisible(false);
}

IRWidgetPrivate::IRWidgetPrivate(IRWidget *parent)
    : m_Parent(parent)
{
    receiveAllCustomEvent();
}

IRWidgetPrivate::~IRWidgetPrivate()
{
}

void IRWidgetPrivate::initialize()
{
    if (NULL == m_IRToolWidget) {
        m_IRToolWidget = new IRToolWidget(m_Parent);
    }
    if (NULL == m_Timer) {
        m_Timer = new QTimer(m_Parent);
        m_Timer->setSingleShot(true);
        m_Timer->setInterval(5000);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_Timer,  SIGNAL(timeout()),
                         m_Parent, SLOT(onTimeout()),
                         type);
    }
}

void IRWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
