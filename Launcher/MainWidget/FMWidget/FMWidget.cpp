#include "FMWidget.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "Widget.h"
#include "FMToolWidget/FMToolWidget.h"
#include "Audio.h"
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>

class FMWidgetPrivate
{
    Q_DISABLE_COPY(FMWidgetPrivate)
public:
    explicit FMWidgetPrivate(FMWidget* parent);
    ~FMWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    FMToolWidget* m_FMToolWidget = NULL;
    QTimer* m_Timer = NULL;
private:
    FMWidget* m_Parent = NULL;
};


FMWidget::FMWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new FMWidgetPrivate(this))
{
    setVisible(true);
}

FMWidget::~FMWidget()
{
}

void FMWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
}

void FMWidget::customEvent(QEvent *event)
{
    qDebug() << "FMWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::FMWidgetStatus: {
        EventEngine::CustomEvent<QString> event1(CustomEventType::VolumeWidgetStatus, NULL);
        g_EventEngine->sendCustomEvent(event1);
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
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
}

void FMWidget::showEvent(QShowEvent *event)
{
    if (NULL != m_Private) {
        m_Private->receiveAllCustomEvent();
    }
}

void FMWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void FMWidget::mousePressEvent(QMouseEvent *event)
{
    if (isVisible()
            && g_Widget->geometryFit(139, g_Widget->baseStatusBarHeight() + 12, 1002, 552).contains(event->pos())) {
        m_Private->m_Timer->stop();
    }
}

void FMWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()
            && (!g_Widget->geometryFit(139, g_Widget->baseStatusBarHeight() + 12, 1002, 552).contains(event->pos()))
            && m_Private->m_Timer->isActive()) {
        m_Private->m_Timer->stop();
        setVisible(false);
    } else {
        m_Private->m_Timer->start();
    }
}

void FMWidget::onTimeout()
{
    m_Private->m_Timer->stop();
    setVisible(false);
}

FMWidgetPrivate::FMWidgetPrivate(FMWidget *parent)
    : m_Parent(parent)
{
    m_FMToolWidget = NULL;
    initialize();
}

FMWidgetPrivate::~FMWidgetPrivate()
{
}

void FMWidgetPrivate::initialize()
{
    if (NULL == m_FMToolWidget) {
        m_FMToolWidget = new FMToolWidget(m_Parent);
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

void FMWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
