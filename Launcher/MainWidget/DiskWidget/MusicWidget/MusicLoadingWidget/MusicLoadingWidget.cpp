#include "MusicLoadingWidget.h"
#include "Widget.h"
#include "AutoConnect.h"
#include "BmpWidget.h"
#include "MainWidget/DiskWidget/MultimediaLoadingWidget.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include <QVariant>
#include <QPainter>

class MusicLoadingWidgetPrivate
{
public:
    explicit MusicLoadingWidgetPrivate(MusicLoadingWidget* parent);
    ~MusicLoadingWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MultimediaLoadingWidget* m_Background = NULL;
private:
    MusicLoadingWidget* m_Parent = NULL;
};

MusicLoadingWidget::MusicLoadingWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new MusicLoadingWidgetPrivate(this))
{
}

MusicLoadingWidget::~MusicLoadingWidget()
{
}

void MusicLoadingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
}

void MusicLoadingWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
}

bool MusicLoadingWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove: {
        event->accept();
        return true;
        break;
    }
    default: {
        break;
    }
    }
    return QWidget::event(event);
}

void MusicLoadingWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "MusicLoadingWidget::ontWidgetTypeChange" << type << status;
    if ((WidgetStatus::RequestShow == status)
            || (WidgetStatus::Show == status)) {
        switch (type) {
        case Widget::T_Music: {
            m_Private->m_Background->setVisible(true);
            break;
        }
        default: {
            if (!m_Private->m_Background->isHidden()) {
                EventEngine::CustomEvent<QString> event(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
                g_EventEngine->sendCustomEvent(event);
            }
            m_Private->m_Background->setVisible(false);
            break;
        }
        }
    }
}

void MusicLoadingWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
//    qWarning() << "MusicLoadingWidget::onMusicPlayerPlayStatus" << status << isVisible() << isHidden() << m_Private->m_Background->isVisible() << m_Private->m_Background->isHidden();
    switch (status) {
    case MPPS_Start: {
        if (!m_Private->m_Background->isHidden()) {
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(this));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MessageBoxWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
            g_EventEngine->sendCustomEvent(event2);
        }
        break;
    }
    default: {
        if (!m_Private->m_Background->isHidden()) {
            EventEngine::CustomEvent<QString> event(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
            g_EventEngine->sendCustomEvent(event);
        }
        setVisible(false);
        break;
    }
    }
}

MusicLoadingWidgetPrivate::MusicLoadingWidgetPrivate(MusicLoadingWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MusicLoadingWidgetPrivate::~MusicLoadingWidgetPrivate()
{
}

void MusicLoadingWidgetPrivate::initialize()
{
    m_Background = new MultimediaLoadingWidget(m_Parent);
//    m_Background->show();
}

void MusicLoadingWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
