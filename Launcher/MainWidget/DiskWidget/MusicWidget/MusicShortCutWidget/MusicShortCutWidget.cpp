#include "MusicShortCutWidget.h"
#include "UserInterfaceUtility.h"
#include "AutoConnect.h"
#include "Widget.h"
#include "BusinessLogicUtility.h"
#include "BmpButton.h"
#include "EventEngine.h"
#include <QVariant>
#include <QPainter>

class MusicShortCutWidgetPrivate
{
    Q_DISABLE_COPY(MusicShortCutWidgetPrivate)
public:
    explicit MusicShortCutWidgetPrivate(MusicShortCutWidget *parent);
    ~MusicShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background = NULL;
    bool m_Filter = false;
private:
    MusicShortCutWidget* m_Parent = NULL;
};

MusicShortCutWidget::MusicShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MusicShortCutWidgetPrivate(this))
{
}

MusicShortCutWidget::~MusicShortCutWidget()
{
}

void MusicShortCutWidget::resizeEvent(QResizeEvent *event)
{
    int width(84);
    int height(84);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5, width, height, m_Private->m_Background);
}

void MusicShortCutWidget::customEvent(QEvent *event)
{
    qDebug() << "ImageShortCutWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::TabBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            if (this != ptr->m_Data->value<QWidget*>()) {
                this->setVisible(false);
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

void MusicShortCutWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    m_Private->m_Filter = false;
}

void MusicShortCutWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_AV1:
    case Widget::T_AV2: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->m_Filter = true;
            startTimer(500);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void MusicShortCutWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "MusicShortCutWidget::onMusicPlayerPlayStatus" << status;
    switch (status) {
    case MPPS_Start: {
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(this));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        break;
    }
    case MPPS_Exit: {
        setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicShortCutWidget::onBmpButtonRelease()
{
    if (!m_Private->m_Filter) {
        g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::RequestShow);
    }
}

MusicShortCutWidgetPrivate::MusicShortCutWidgetPrivate(MusicShortCutWidget* parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

MusicShortCutWidgetPrivate::~MusicShortCutWidgetPrivate()
{
}

void MusicShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/MusicShortCutWidgetBackground"));
    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/MusicShortCutWidgetBackground"));
}

void MusicShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MusicShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onBmpButtonRelease()),
                     type);
}
