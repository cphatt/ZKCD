#include "VideoWidget.h"
#include "VideoStatusWidget/VideoStatusWidget.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"
#include "VideoShortCutWidget/VideoShortCutWidget.h"
#include "VideoLoadingWidget/VideoLoadingWidget.h"
#include "MessageBox.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QBrush>
#include <QLabel>
#include <QFileInfo>
#include <QTimer>
#include <QMouseEvent>

namespace SourceString {
static const QString Unsupport = QString(QObject::tr("Unsupport..."));
}

class VideoWidgetPrivate
{
    Q_DISABLE_COPY(VideoWidgetPrivate)
public:
    explicit VideoWidgetPrivate(VideoWidget * parent);
    ~VideoWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void videoWidgetSwitchHandler(const QString &status);
    QString convertTime(const int time);
    VideoShortCutWidget* m_VideoShortCutWidget = NULL;
    VideoStatusWidget* m_StatusWidget = NULL;
    VideoToolBarWidget* m_ToolBarWidget = NULL;
    VideoLoadingWidget* m_VideoLoadingWidget = NULL;
    QTimer *m_Timer = NULL;
    QRect m_TouchRect = QRect(0, 0, 0, 0);
    MessageBox* m_MessageBox = NULL;
private:
    VideoWidget* m_Parent = NULL;
};

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VideoWidgetPrivate(this))
{
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_MessageBox);
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (isVisible()) {
        if (m_Private->m_TouchRect.contains(event->pos())) {
            if (m_Private->m_TouchRect == g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight())) {
                g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
            } else {
                g_Widget->setWidgetType(Widget::T_VideoFullScreen, WidgetStatus::Show);
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void VideoWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        m_Private->videoWidgetSwitchHandler(status);
        break;
    }
    case Widget::T_VideoFullScreen: {
        m_Private->m_TouchRect = g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
        m_Private->m_Timer->stop();
        break;
    }
    default : {
        if (status == WidgetStatus::Show) {
            setVisible(false);
            m_Private->m_Timer->stop();
        }
        break;
    }
    }
}

void VideoWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus playStatus)
{
    switch (playStatus) {
    case VPPS_Start: {
        m_Private->m_MessageBox->setVisible(false);
        break;
    }
    case VPPS_Play: {
        if (isVisible()
                && !m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        //        m_Private->m_ToggleBtn->setText(SourceString::Pause);
        break;
    }
    case VPPS_Pause: {
        m_Private->m_Timer->stop();
        //        m_Private->m_ToggleBtn->setText(SourceString::Play);
        break;
    }
    case VPPS_Exit: {
        m_Private->m_Timer->stop();
        break;
    }
    case VPPS_Unsupport: {
        m_Private->m_MessageBox->setText(SourceString::Unsupport);
        m_Private->m_MessageBox->setAutoHide(false);
        m_Private->m_MessageBox->setVisible(true);
        break;
    }
    default : {
        break;
    }
    }
}

void VideoWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    m_Private->m_Timer->start();
    //    qDebug() << "onVideoInformation" << fileName << endTime;
    //    if (VideoWidgetPrivate::S_Normal == m_Private->m_ShowStatus) {
    //        if (!m_Private->m_Timer->isActive()) {
    //            //            if (SourceString::Pause == m_Private->m_ToggleBtn->getText()) {
    //            //                m_Private->m_Timer->start();
    //            //            }
    //        }
    //    }
}

void VideoWidget::onTimeout()
{
    g_Widget->setWidgetType(Widget::T_VideoFullScreen, WidgetStatus::Show);
}

VideoWidgetPrivate::VideoWidgetPrivate(VideoWidget * parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

VideoWidgetPrivate::~VideoWidgetPrivate()
{
}

void VideoWidgetPrivate::initialize()
{
    m_MessageBox = new MessageBox(m_Parent);
    m_MessageBox->setVisible(false);
    m_MessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_VideoShortCutWidget = new VideoShortCutWidget(m_Parent);
    m_StatusWidget = new VideoStatusWidget(m_Parent);
    m_ToolBarWidget = new VideoToolBarWidget(m_Parent);
    m_VideoLoadingWidget = new VideoLoadingWidget(m_Parent);
    m_Timer = new QTimer(m_Parent);
    m_Timer->setInterval(5000);
    m_Timer->setSingleShot(true);
}

void VideoWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

void VideoWidgetPrivate::videoWidgetSwitchHandler(const QString &status)
{
    if (WidgetStatus::RequestShow == status) {
        g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
    } else if (WidgetStatus::Show == status) {
        m_TouchRect = g_Widget->geometryFit(0, 88, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - 88 - 124);
        m_Timer->start();
        m_Parent->setVisible(true);
    }
}

QString VideoWidgetPrivate::convertTime(const int time)
{
    QString hour("%1");
    QString minute("%1");
    QString second("%1");
    return hour.arg((time / 60) / 60, 2, 10, QChar('0'))
            + QString(":") + minute.arg((time / 60) % 60, 2, 10, QChar('0'))
            + QString(":") + second.arg(time % 60, 2, 10, QChar('0'));
}
