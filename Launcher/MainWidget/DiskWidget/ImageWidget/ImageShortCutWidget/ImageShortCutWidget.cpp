#include "ImageShortCutWidget.h"
#include "AutoConnect.h"
#include "BusinessLogicUtility.h"
#include "Widget.h"
#include "EventEngine.h"
#include <QVariant>
#include <QPainter>

class ImageShortCutWidgetPrivate
{
    Q_DISABLE_COPY(ImageShortCutWidgetPrivate)
public:
    explicit ImageShortCutWidgetPrivate(ImageShortCutWidget* parent);
    ~ImageShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background = NULL;
private:
    ImageShortCutWidget* m_Parent = NULL;
};

ImageShortCutWidget::ImageShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ImageShortCutWidgetPrivate(this))
{
}

ImageShortCutWidget::~ImageShortCutWidget()
{
}

void ImageShortCutWidget::resizeEvent(QResizeEvent *event)
{
    int width(84);
    int height(84);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5, width, height, m_Private->m_Background);
}

void ImageShortCutWidget::customEvent(QEvent *event)
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

void ImageShortCutWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "ImageShortCutWidget::onImagePlayerPlayStatus" << status;
    switch (status) {
    case IPPS_Start: {
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(this));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        break;
    }
    case IPPS_Exit: {
        setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}

void ImageShortCutWidget::onBmpButtonRelease()
{
    g_Multimedia->imagePlayerSetPlayStatus(IPPS_SuspendToggle);
    g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::RequestShow);
}

ImageShortCutWidgetPrivate::ImageShortCutWidgetPrivate(ImageShortCutWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

ImageShortCutWidgetPrivate::~ImageShortCutWidgetPrivate()
{
}

void ImageShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/ImageShortCutWidgetBackground"));
    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/ImageShortCutWidgetBackground"));
}

void ImageShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void ImageShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onBmpButtonRelease()),
                     type);
}
