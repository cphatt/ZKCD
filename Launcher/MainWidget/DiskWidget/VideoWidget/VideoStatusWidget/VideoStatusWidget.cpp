#include "VideoStatusWidget.h"
#include "UserInterfaceUtility.h"
#include "AutoConnect.h"
#include "TextWidget.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include "BmpWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

namespace SourceString {
static const QString Video = QString(QObject::tr("Video>"));
}

class VideoStatusWidgetPrivate
{
    Q_DISABLE_COPY(VideoStatusWidgetPrivate)
public:
    explicit VideoStatusWidgetPrivate(VideoStatusWidget* parent);
    ~VideoStatusWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    TextWidget* m_TitleText = NULL;
    TextWidget* m_FileNameText = NULL;
    BmpWidget* m_VolumeStatusTip = NULL;
private:
    VideoStatusWidget* m_Parent = NULL;
};

VideoStatusWidget::VideoStatusWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VideoStatusWidgetPrivate(this))
{
    setVisible(true);
}

VideoStatusWidget::~VideoStatusWidget()
{
}

void VideoStatusWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), 88, this);
    g_Widget->geometryFit(0, 0, 172, 88, m_Private->m_TitleText);
    g_Widget->geometryFit(172, 0, 800, 88, m_Private->m_FileNameText);
    QWidget::resizeEvent(event);
}
static QWidget* ptr1(NULL);
void VideoStatusWidget::paintEvent(QPaintEvent *event)
{
    if (NULL != ptr1) {
        qDebug() << "ptr1ptr1" << ptr1->geometry();
    }
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(UserInterfaceUtility::multimediaAlphaColor()));
    QWidget::paintEvent(event);
}

void VideoStatusWidget::customEvent(QEvent *event)
{
    qDebug() << "VideoStatusWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::VideoToolBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
            ptr1 = ptr->m_Data->value<QWidget*>();
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void VideoStatusWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    default : {
        break;
    }
    }
}

void VideoStatusWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Start: {
        m_Private->m_FileNameText->setText(QString(""));
        m_Private->m_FileNameText->setVisible(true);
        break;
    }
    default: {
        break;
    }
    }
}

void VideoStatusWidget::onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << "VideoStatusWidget::onVideoPlayerInformation" << fileName;
    m_Private->m_FileNameText->setText(fileName);
    m_Private->m_FileNameText->setVisible(true);
}

VideoStatusWidgetPrivate::VideoStatusWidgetPrivate(VideoStatusWidget *parent)
    : m_Parent(parent)
{
    m_TitleText = NULL;
    m_FileNameText = NULL;
    m_VolumeStatusTip = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

VideoStatusWidgetPrivate::~VideoStatusWidgetPrivate()
{
}

void VideoStatusWidgetPrivate::initialize()
{
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    int fontPointSize(22 * g_Widget->widthScalabilityFactor());
    m_TitleText->setFontPointSize(fontPointSize);
    m_TitleText->setText(SourceString::Video);
    m_TitleText->show();
    m_FileNameText = new TextWidget(m_Parent);
    m_FileNameText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_FileNameText->setFontPointSize(fontPointSize);
    m_FileNameText->setLanguageType(TextWidget::T_NoTranslate);
    m_FileNameText->show();
}

void VideoStatusWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void VideoStatusWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
