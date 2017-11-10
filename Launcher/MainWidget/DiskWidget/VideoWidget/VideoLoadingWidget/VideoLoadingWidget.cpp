#include "VideoLoadingWidget.h"
#include "Widget.h"
#include "AutoConnect.h"
#include "BmpWidget.h"
#include "MainWidget/DiskWidget/MultimediaLoadingWidget.h"
#include <QPainter>

class VideoLoadingWidgetPrivate
{
public:
    explicit VideoLoadingWidgetPrivate(VideoLoadingWidget* parent);
    ~VideoLoadingWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MultimediaLoadingWidget* m_Background = NULL;
private:
    VideoLoadingWidget* m_Parent = NULL;
};

VideoLoadingWidget::VideoLoadingWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new VideoLoadingWidgetPrivate(this))
{
}

VideoLoadingWidget::~VideoLoadingWidget()
{
}

void VideoLoadingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
}

void VideoLoadingWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
}

bool VideoLoadingWidget::event(QEvent *event)
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

void VideoLoadingWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
//    qWarning() << "VideoLoadingWidget::onVideoPlayerPlayStatus" << status;
    switch (status) {
    case VPPS_Start: {
        setVisible(true);
        break;
    }
    default: {
        setVisible(false);
        break;
    }
    }
}

VideoLoadingWidgetPrivate::VideoLoadingWidgetPrivate(VideoLoadingWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

VideoLoadingWidgetPrivate::~VideoLoadingWidgetPrivate()
{
}

void VideoLoadingWidgetPrivate::initialize()
{
    m_Background = new MultimediaLoadingWidget(m_Parent);
    m_Background->show();
}

void VideoLoadingWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
