#include "SDDiskListViewWidget.h"
#include "SDDiskMusicListViewWidget/SDDiskMusicListViewWidget.h"
#include "SDDiskImageListViewWidget/SDDiskImageListViewWidget.h"
#include "SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.h"
#include "BusinessLogicUtility.h"
#include "AutoConnect.h"

class SDDiskListViewWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskListViewWidgetPrivate)
public:
    explicit SDDiskListViewWidgetPrivate(SDDiskListViewWidget* parent);
    ~SDDiskListViewWidgetPrivate();
    void initialize();
    void connectAllSlots();
    SDDiskMusicListViewWidget* m_SDDiskMusicListViewWidget = NULL;
    SDDiskImageListViewWidget* m_SDDiskImageListViewWidget = NULL;
    SDDiskVideoListViewWidget* m_SDDiskVideoListViewWidget = NULL;
private:
    SDDiskListViewWidget* m_Parent = NULL;
};

SDDiskListViewWidget::SDDiskListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SDDiskListViewWidgetPrivate(this))
{
        setVisible(true);
}

SDDiskListViewWidget::~SDDiskListViewWidget()
{
}

void SDDiskListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
}

void SDDiskListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_SDDisk:
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo: {
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

SDDiskListViewWidgetPrivate::SDDiskListViewWidgetPrivate(SDDiskListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

SDDiskListViewWidgetPrivate::~SDDiskListViewWidgetPrivate()
{
}

void SDDiskListViewWidgetPrivate::initialize()
{
    m_SDDiskMusicListViewWidget = new SDDiskMusicListViewWidget(m_Parent);
    m_SDDiskImageListViewWidget = new SDDiskImageListViewWidget(m_Parent);
    m_SDDiskVideoListViewWidget = new SDDiskVideoListViewWidget(m_Parent);
}

void SDDiskListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
