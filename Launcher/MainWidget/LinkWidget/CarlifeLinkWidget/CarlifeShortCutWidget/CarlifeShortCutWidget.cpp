#include "CarlifeShortCutWidget.h"
#include "AutoConnect.h"
#include "BusinessLogicUtility.h"
#include "Widget.h"
#include "EventEngine.h"
#include <QVariant>
#include <QPainter>

class CarlifeShortCutWidgetPrivate
{
    Q_DISABLE_COPY(CarlifeShortCutWidgetPrivate)
public:
    explicit CarlifeShortCutWidgetPrivate(CarlifeShortCutWidget* parent);
    ~CarlifeShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background = NULL;
private:
    CarlifeShortCutWidget* m_Parent = NULL;
};

CarlifeShortCutWidget::CarlifeShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new CarlifeShortCutWidgetPrivate(this))
{
}

CarlifeShortCutWidget::~CarlifeShortCutWidget()
{
}

void CarlifeShortCutWidget::resizeEvent(QResizeEvent *event)
{
    int width(84);
    int height(84);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5, width, height, m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void CarlifeShortCutWidget::customEvent(QEvent *event)
{
    qDebug() << "CarlifeShortCutWidget::customEvent" << event->type();
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

void CarlifeShortCutWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "CarlifeShortCutWidget::onLinkStatusChange" << type << status;
    switch (type) {
    case CARPLAY: {
        if (LINK_EXITING == status) {
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(this));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        } else {
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void CarlifeShortCutWidget::onBmpButtonRelease()
{
    g_Link->requestLinkStatus(CARPLAY, LINK_STARTING);
}

CarlifeShortCutWidgetPrivate::CarlifeShortCutWidgetPrivate(CarlifeShortCutWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

CarlifeShortCutWidgetPrivate::~CarlifeShortCutWidgetPrivate()
{
}

void CarlifeShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/CarlifeShortCutWidgetBackground"));
    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/CarlifeShortCutWidgetBackground"));
}

void CarlifeShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void CarlifeShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onBmpButtonRelease()),
                     type);
}
