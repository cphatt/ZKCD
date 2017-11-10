#include "USBDiskListViewWidget.h"
#include "USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.h"
#include "USBDiskImageListViewWidget/USBDiskImageListViewWidget.h"
#include "USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.h"
#include "BusinessLogicUtility.h"
#include "AutoConnect.h"
#include <QPainter>

class USBDiskListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskListViewWidgetPrivate)
public:
    explicit USBDiskListViewWidgetPrivate(USBDiskListViewWidget* parent);
    ~USBDiskListViewWidgetPrivate();
    void initialize();
    void connectAllSlots();
    USBDiskMusicListViewWidget* m_USBDiskMusicListViewWidget = NULL;
    USBDiskImageListViewWidget* m_USBDiskImageListViewWidget = NULL;
    USBDiskVideoListViewWidget* m_USBDiskVideoListViewWidget = NULL;
private:
    USBDiskListViewWidget* m_Parent = NULL;
};

USBDiskListViewWidget::USBDiskListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new USBDiskListViewWidgetPrivate(this))
{
    setVisible(false);
}

USBDiskListViewWidget::~USBDiskListViewWidget()
{
}

void USBDiskListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
}

void USBDiskListViewWidget::paintEvent(QPaintEvent *event)
{
}

void USBDiskListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo: {
            setVisible(true);
            break;
        }
        case Widget::T_Music:
        case Widget::T_Image:
        case Widget::T_Video: {
            setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
    }
}

USBDiskListViewWidgetPrivate::USBDiskListViewWidgetPrivate(USBDiskListViewWidget *parent)
    : m_Parent(parent)
{
    m_USBDiskMusicListViewWidget = NULL;
    m_USBDiskImageListViewWidget = NULL;
    m_USBDiskVideoListViewWidget = NULL;
    initialize();
    connectAllSlots();
}

USBDiskListViewWidgetPrivate::~USBDiskListViewWidgetPrivate()
{
}

void USBDiskListViewWidgetPrivate::initialize()
{
    m_USBDiskMusicListViewWidget = new USBDiskMusicListViewWidget(m_Parent);
    m_USBDiskImageListViewWidget = new USBDiskImageListViewWidget(m_Parent);
    m_USBDiskVideoListViewWidget = new USBDiskVideoListViewWidget(m_Parent);
}

void USBDiskListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
