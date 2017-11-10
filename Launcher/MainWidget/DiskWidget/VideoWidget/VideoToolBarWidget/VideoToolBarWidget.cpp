#include "VideoToolBarWidget.h"
#include "BmpButton.h"
#include "Slider.h"
#include "Multimedia.h"
#include "UserInterfaceUtility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"
#include "TextWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QVariant>
#include <QTimer>

class VideoToolBarWidgetPrivate
{
    Q_DISABLE_COPY(VideoToolBarWidgetPrivate)
public:
    enum FunctionType {
        FT_Volume = 0,
        FT_Video = 1,
    };
    explicit VideoToolBarWidgetPrivate(VideoToolBarWidget* parent);
    ~VideoToolBarWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void switchFunction();
    QString convertTime(const int time);
    Slider* m_Slider = NULL;
    TextWidget* m_ElapsedTimeText = NULL;
    TextWidget* m_EndTimeText = NULL;
    BmpButton* m_VolumeBtn = NULL;
    BmpButton* m_PreviousBtn = NULL;
    BmpButton* m_ToggleBtn = NULL;
    BmpButton* m_NextBtn = NULL;
    BmpButton* m_FMBtn = NULL;
    BmpButton* m_IRBtn = NULL;
    BmpButton* m_SwitchFunctionBtn = NULL;
    FunctionType m_FunctionType = FT_Video;
    bool m_Seek = false;
    int m_ElapsedTime = 0;
private:
    VideoToolBarWidget* m_Parent = NULL;
};

VideoToolBarWidget::VideoToolBarWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VideoToolBarWidgetPrivate(this))
{
}

VideoToolBarWidget::~VideoToolBarWidget()
{
}

void VideoToolBarWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 597, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - 597, this);
    g_Widget->geometryFit(36, 603 - 596, 72 * 2, 50, m_Private->m_ElapsedTimeText);
    g_Widget->geometryFit(165, 603 - 596, 1113 - 165, 50, m_Private->m_Slider);
    g_Widget->geometryFit(1175 - 72, 603 - 596, 72 * 2, 50, m_Private->m_EndTimeText);
    int width(50);
    int height(50);
    g_Widget->geometryFit(441 + (481 - 441 - width) * 0.5, 654 + height * 0.5 - 596 - height * 0.5, width, height, m_Private->m_PreviousBtn);
    g_Widget->geometryFit(618 + (663 - 618 - width) * 0.5, 654 + height * 0.5 - 596 - height * 0.5, width, height, m_Private->m_ToggleBtn);
    g_Widget->geometryFit(797 + (837 - 797  - width) * 0.5, 654 + height * 0.5 - 596 - height * 0.5, width, height, m_Private->m_NextBtn);
    g_Widget->geometryFit(441 + (481 - 441 - width) * 0.5, 654 + height * 0.5 - 596 - height * 0.5, width, height, m_Private->m_FMBtn);
    g_Widget->geometryFit(797 + (837 - 797  - width) * 0.5, 654 + height * 0.5 - 596 - height * 0.5, width, height, m_Private->m_IRBtn);
    width = 70;
    height = 70;
    g_Widget->geometryFit(71 + (147 - 71 - width) * 0.5, 655 + (699 - 655 - height) * 0.5 - 596, width, height, m_Private->m_VolumeBtn);
    g_Widget->geometryFit(1103 + (1238 - 1103 - 70) * 0.5, 655 + (699 - 655 - height) * 0.5 - 596, width, height, m_Private->m_SwitchFunctionBtn);
}

void VideoToolBarWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(UserInterfaceUtility::multimediaAlphaColor()));
}

void VideoToolBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        if (WidgetStatus::Show == status) {
            if (VideoToolBarWidgetPrivate::FT_Video == m_Private->m_FunctionType) {
                m_Private->m_PreviousBtn->setVisible(true);
                m_Private->m_ToggleBtn->setVisible(true);
                m_Private->m_NextBtn->setVisible(true);
                m_Private->m_FMBtn->setVisible(false);
                m_Private->m_IRBtn->setVisible(false);
            } else {
                m_Private->m_PreviousBtn->setVisible(false);
                m_Private->m_ToggleBtn->setVisible(false);
                m_Private->m_NextBtn->setVisible(false);
                m_Private->m_FMBtn->setVisible(true);
                m_Private->m_IRBtn->setVisible(true);
            }
            m_Private->m_VolumeBtn->setVisible(true);
            m_Private->m_Slider->setVisible(true);
            m_Private->m_ElapsedTimeText->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
            m_Private->m_PreviousBtn->setVisible(false);
            m_Private->m_ToggleBtn->setVisible(false);
            m_Private->m_NextBtn->setVisible(false);
            m_Private->m_VolumeBtn->setVisible(false);
            m_Private->m_Slider->setVisible(false);
            m_Private->m_ElapsedTimeText->setVisible(false);
        }
        break;
    }
    default : {
        break;
    }
    }
}

void VideoToolBarWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Start: {
        m_Private->m_Slider->setRange(0, 0);
        m_Private->m_Slider->setTracking(false);
        m_Private->m_EndTimeText->setText(m_Private->convertTime(0));
        m_Private->m_EndTimeText->setVisible(true);
        m_Private->m_ElapsedTime = 0;
        m_Private->m_ElapsedTimeText->setText(m_Private->convertTime(0));
        m_Private->m_ElapsedTimeText->setVisible(true);
        m_Private->m_Slider->setTickMarksMillesimal(0);
        break;
    }
    case VPPS_Stop:
    case VPPS_Pause: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
        break;
    }
    case VPPS_Play: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPauseBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPauseBtnNormal"));
        break;
    }
    default : {
        break;
    }
    }
}

void VideoToolBarWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
//    qDebug() << "VideoToolBarWidget::onVideoPlayerInformation" << endTime;
    m_Private->m_Slider->setRange(0, endTime);
    m_Private->m_Slider->setTracking(false);
    m_Private->m_EndTimeText->setText(m_Private->convertTime(endTime));
    bool ret = (0 == endTime);
    m_Private->m_Slider->setAllowPress(!ret);
    m_Private->m_EndTimeText->setVisible(true);
}

void VideoToolBarWidget::onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
//    qWarning() << "VideoToolBarWidget::onVideoPlayerElapsedInformation" << elapsedTime << elapsedMillesimal;
    if (m_Private->m_Seek) {
        m_Private->m_Seek = false;
        if (1 == (elapsedTime - m_Private->m_ElapsedTime)) {
            return ;
        }
    }
    m_Private->m_ElapsedTime = elapsedTime;
    m_Private->m_ElapsedTimeText->setText(m_Private->convertTime(elapsedTime));
    m_Private->m_Slider->setTickMarksMillesimal(elapsedMillesimal);
}

void VideoToolBarWidget::onToolButtonRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if (ptr == m_Private->m_PreviousBtn) {
        g_Multimedia->videoPlayerPlayPreviousListViewIndex();
    } else if (ptr == m_Private->m_ToggleBtn) {
        g_Multimedia->videoPlayerSetPlayStatusToggle();
    } else if (ptr == m_Private->m_NextBtn) {
        g_Multimedia->videoPlayerPlayNextListViewIndex();
    } else if (ptr == m_Private->m_VolumeBtn) {
        //        g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_SwitchFunctionBtn) {
        m_Private->switchFunction();
    } else if (ptr == m_Private->m_FMBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_IRBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::IRWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    }
}

void VideoToolBarWidget::onTickMarksMillesimalStart()
{
//    g_Multimedia->videoPlayerSetPlayStatus(VPPS_Pause);
}

void VideoToolBarWidget::onTickMarksMillesimalEnd(const int millesimal)
{
    m_Private->m_Seek = true;
    g_Multimedia->videoPlayerSeekToMillesimal(millesimal);
}

VideoToolBarWidgetPrivate::VideoToolBarWidgetPrivate(VideoToolBarWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

VideoToolBarWidgetPrivate::~VideoToolBarWidgetPrivate()
{
}

void VideoToolBarWidgetPrivate::initialize()
{
    m_ElapsedTimeText = new TextWidget(m_Parent);
    m_ElapsedTimeText->hide();
    m_ElapsedTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_EndTimeText = new TextWidget(m_Parent);
    m_EndTimeText->hide();
    m_EndTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_Slider = new Slider(m_Parent);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
    m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setTickMarksMillesimal(0);
    m_Slider->hide();
    m_VolumeBtn = new BmpButton(m_Parent);
    m_VolumeBtn->show();
    m_VolumeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
    m_VolumeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
    m_PreviousBtn = new BmpButton(m_Parent);
    m_PreviousBtn->hide();
    m_PreviousBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPreviousBtnNormal"));
    m_PreviousBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPreviousBtnNormal"));
    m_ToggleBtn = new BmpButton(m_Parent);
    m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
    m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
    m_ToggleBtn->hide();
    m_NextBtn = new BmpButton(m_Parent);
    m_NextBtn->hide();
    m_NextBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetNextBtnNormal"));
    m_NextBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetNextBtnNormal"));
    m_FMBtn = new BmpButton(m_Parent);
    m_FMBtn->setVisible(false);
    m_FMBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetFMBtnNormal"));
    m_FMBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetFMBtnNormal"));
    m_IRBtn = new BmpButton(m_Parent);
    m_IRBtn->setVisible(false);
    m_IRBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetIRBtnNormal"));
    m_IRBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetIRBtnNormal"));
    m_SwitchFunctionBtn = new BmpButton(m_Parent);
    m_SwitchFunctionBtn->show();
    m_SwitchFunctionBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSwitchFunctionNormal"));
    m_SwitchFunctionBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSwitchFunctionNormal"));
}

void VideoToolBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_PreviousBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_NextBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FMBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_IRBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_VolumeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_SwitchFunctionBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,            SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalStart(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalStart()),
                     type);
}

void VideoToolBarWidgetPrivate::switchFunction()
{
    if (FT_Video == m_FunctionType) {
        m_FunctionType = FT_Volume;
    } else {
        m_FunctionType = FT_Video;
    }
    g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
}

QString VideoToolBarWidgetPrivate::convertTime(const int time)
{
    QString hour("%1");
    QString minute("%1");
    QString second("%1");
    return hour.arg((time / 60) / 60, 2, 10, QChar('0'))
            + QString(":") + minute.arg((time / 60) % 60, 2, 10, QChar('0'))
            + QString(":") + second.arg(time % 60, 2, 10, QChar('0'));
}
