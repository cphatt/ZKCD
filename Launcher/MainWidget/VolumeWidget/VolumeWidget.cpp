#include "VolumeWidget.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "Audio.h"
#include "Widget.h"
#include "AutoConnect.h"
#include "VolumeToolWidget/VolumeToolWidget.h"
#include "BmpWidget.h"
#include "EventEngine.h"
#include <QVariant>
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>

class VolumeWidgetPrivate
{
    Q_DISABLE_COPY(VolumeWidgetPrivate)
public:
    explicit VolumeWidgetPrivate(VolumeWidget* parent);
    ~VolumeWidgetPrivate();
    void initializeTipWidget();
    void initializeToolWidget();
    void initializeTimer();
    void receiveAllCustomEvent();
    void connectAllSlots();
    VolumeToolWidget* m_VolumeToolWidget = NULL;
    BmpWidget* m_VolumeStatusTip = NULL;
    QTimer* m_Timer = NULL;
private:
    VolumeWidget* m_Parent = NULL;
};

VolumeWidget::VolumeWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VolumeWidgetPrivate(this))
{
}

VolumeWidget::~VolumeWidget()
{
}

void VolumeWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void VolumeWidget::customEvent(QEvent *event)
{
    qDebug() << "VolumeWidget::customEvent" << event->type() << CustomEventType::VolumeWidgetStatus;
    switch (event->type()) {
    case CustomEventType::VolumeWidgetStatus: {
        m_Private->connectAllSlots();
        m_Private->initializeToolWidget();
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                setVisible(true);
                m_Private->initializeTimer();
                m_Private->m_Timer->start();
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

void VolumeWidget::mousePressEvent(QMouseEvent *event)
{
    if (isVisible()
            && g_Widget->geometryFit(213, 180, 853, 360).contains(event->pos())) {
        m_Private->m_Timer->stop();
    }
}

void VolumeWidget::mouseReleaseEvent(QMouseEvent *event)
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

void VolumeWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
}

void VolumeWidget::onVolumeChange(OutPutSource type, const int volume)
{
    qDebug() << "VolumeWidget::onVolumeChange" << type << volume;
    m_Private->initializeTipWidget();
    if (!m_Private->m_VolumeStatusTip->isVisible()) {
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_Private->m_VolumeStatusTip));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(g_Widget->baseWindowWidth() - 60 - 15, 0, 60, 60, m_Private->m_VolumeStatusTip);
    }
    if (0 == volume) {
        m_Private->m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeMuteWidgetTipNormal"));
    } else {
        switch (type) {
        case OPS_FM: {
            m_Private->m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeFMWidgetTipNormal"));
            break;
        }
        case OPS_IR: {
            m_Private->m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeIRWidgetTipNormal"));
            break;
        }
        case OPS_Speak: {
            m_Private->m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeSpeakWidgetTipNormal"));
            break;
        }
        default: {
            m_Private->m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeFMWidgetTipNormal"));
            break;
        }
        }
    }
    m_Private->m_VolumeStatusTip->setVisible(true);
}

void VolumeWidget::onTimeout()
{
    m_Private->m_Timer->stop();
    setVisible(false);
}

VolumeWidgetPrivate::VolumeWidgetPrivate(VolumeWidget *parent)
    : m_Parent(parent)
{
    receiveAllCustomEvent();
}

VolumeWidgetPrivate::~VolumeWidgetPrivate()
{
}

void VolumeWidgetPrivate::initializeTipWidget()
{
    if (NULL == m_VolumeStatusTip) {
        m_VolumeStatusTip = new BmpWidget(m_Parent);
        m_VolumeStatusTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/VolumeSpeakWidgetTipNormal"));
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_VolumeStatusTip));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(g_Widget->baseWindowWidth() - 60 - 15, 0, 60, 60, m_VolumeStatusTip);
    }
}

void VolumeWidgetPrivate::initializeToolWidget()
{
    if (NULL == m_VolumeToolWidget) {
        m_VolumeToolWidget = new VolumeToolWidget(m_Parent);
    }
}

void VolumeWidgetPrivate::initializeTimer()
{
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

void VolumeWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void VolumeWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
}
