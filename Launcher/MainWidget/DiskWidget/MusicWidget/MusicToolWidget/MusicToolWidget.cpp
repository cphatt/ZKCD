#include "MusicToolWidget.h"
#include "Setting.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "Slider.h"
#include "TextWidget.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QFileInfo>
#include <QVariant>
#include <QTimer>

namespace SourceString {
static const QString Unknown = QString(QObject::tr("Unknown"));
}

class MusicToolWidgetPrivate
{
    Q_DISABLE_COPY(MusicToolWidgetPrivate)
public:
    explicit MusicToolWidgetPrivate(MusicToolWidget *parent);
    ~MusicToolWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    QString convertTime(const int time);
    BmpWidget* m_Background = NULL;
    BmpButton* m_PreviousBtn = NULL;
    BmpButton* m_ToggleBtn = NULL;
    BmpButton* m_NextBtn = NULL;
    BmpButton* m_StopBtn = NULL;
    BmpButton* m_ModeBtn = NULL;
    TextWidget* m_TitleText = NULL;
    TextWidget* m_ElapsedTimeText = NULL;
    TextWidget* m_EndTimeText = NULL;
    Slider* m_Slider = NULL;
    bool m_Seek = false;
    int m_ElapsedTime = 0;
private:
    MusicToolWidget* m_Parent = NULL;
};

MusicToolWidget::MusicToolWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MusicToolWidgetPrivate(this))
{
}

MusicToolWidget::~MusicToolWidget()
{
}

void MusicToolWidget::resizeEvent(QResizeEvent *event)
{
    int width(70);
    int height(70);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    g_Widget->geometryFit(113 + (155 - 113 - width) / 2, 210 + (262 - 210 - height) * 0.5, width, height, m_Private->m_PreviousBtn);
    g_Widget->geometryFit(1116 + (1176 - 1116 - width) / 2, 210 + (262 - 210 - height) * 0.5, width, height, m_Private->m_ToggleBtn);
    g_Widget->geometryFit(113 + (155 - 113 - width) / 2, 316 + (367 - 316 - height) * 0.5, width, height, m_Private->m_NextBtn);
    g_Widget->geometryFit(1116 + (1176 - 1116 - width) / 2, 316 + (367 - 316 - height) * 0.5, width, height, m_Private->m_StopBtn);
    g_Widget->geometryFit(1116 + (1176 - 1116 - width) / 2, 548 + (602 - 548 - height) * 0.5, width, height, m_Private->m_ModeBtn);
    g_Widget->geometryFit(321, 532, 953 - 321, 584 - 532, m_Private->m_Slider);
    g_Widget->geometryFit(336, 141 - (117 - 74), 821 - 336, 117 - 74, m_Private->m_TitleText);
    g_Widget->geometryFit(321, 607 - (626 - 607), (395 - 277) * 2, (626 - 607) * 2, m_Private->m_ElapsedTimeText);
    g_Widget->geometryFit(321 + 953 - 321 - (395 - 277) * 2, 607 - (626 - 607), (395 - 277) * 2, (626 - 607) * 2, m_Private->m_EndTimeText);
}

void MusicToolWidget::paintEvent(QPaintEvent *event)
{
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.drawPixmap(QRect(0, itemHeight * 2, 250, 250), m_Private->m_Conver);
    //    painter.drawRect(QRect(0, itemHeight * 2, 250, 250));
}

void MusicToolWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MusicWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void MusicToolWidget::onMusicPlayerPlayMode(const MusicPlayerPlayMode mode)
{
    switch (mode) {
    case MPPM_RepeatOnce: {
        m_Private->m_ModeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetSingleLoopBtnNormal"));
        m_Private->m_ModeBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetSingleLoopBtnNormal"));
        break;
    }
    case MPPM_Shuffle: {
        m_Private->m_ModeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetRandomLoopBtnNormal"));
        m_Private->m_ModeBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetRandomLoopBtnNormal"));
        break;
    }
    case MPPM_AllRepeat:
    default : {
        m_Private->m_ModeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetAllLoopBtnNormal"));
        m_Private->m_ModeBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetAllLoopBtnNormal"));
        break;
    }
    }
}

void MusicToolWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "MusicToolWidget::onMusicPlayerPlayStatus" << status;
    switch (status) {
    case MPPS_Start: {
//        setVisible(false);
//        m_Private->m_Background->setVisible(false);
//        m_Private->m_PreviousBtn->setVisible(false);
//        m_Private->m_ToggleBtn->setVisible(false);
//        m_Private->m_NextBtn->setVisible(false);
//        m_Private->m_StopBtn->setVisible(false);
//        m_Private->m_ModeBtn->setVisible(false);
//        m_Private->m_Slider->setVisible(false);
//        m_Private->m_TitleText->setVisible(false);
//        m_Private->m_ElapsedTimeText->setVisible(false);
//        m_Private->m_EndTimeText->setVisible(false);
        m_Private->m_TitleText->setText(QString(""));
        m_Private->m_ElapsedTime = 0;
        m_Private->m_ElapsedTimeText->setText(m_Private->convertTime(0));
        m_Private->m_Slider->setTickMarksMillesimal(0);
        m_Private->m_Slider->setTracking(false);
        m_Private->m_Slider->setRange(0, 0);
        m_Private->m_EndTimeText->setText(m_Private->convertTime(0));
        break;
    }
    case MPPS_Play: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPauseBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPauseBtnNormal"));
        setVisible(true);
        break;
    }
    case MPPS_Pause:
    case MPPS_Stop: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
        setVisible(true);
        break;
    }
    default : {
        break;
    }
    }
}

void MusicToolWidget::onMusicPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
    qDebug() << "MusicToolWidget::onMusicPlayerElapsedInformation" << elapsedTime << elapsedMillesimal;
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

void MusicToolWidget::onMusicPlayerID3TagChange(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << fileName << endTime;;
    if (!fileName.isEmpty()) {
        m_Private->m_TitleText->setText(fileName);
    } else {
        m_Private->m_TitleText->setText(QObject::tr(SourceString::Unknown.toLocal8Bit().constData()));
    }
    m_Private->m_Slider->setTracking(false);
    bool ret = (0 == endTime);
    m_Private->m_Slider->setAllowPress(!ret);
    m_Private->m_Slider->setRange(0, endTime);
    m_Private->m_EndTimeText->setText(m_Private->convertTime(endTime));
    /*if (fileName.isEmpty()) {
        m_Private->m_FileName = QString(QObject::tr("Unknown"));
    } else {
        m_Private->m_FileName = fileName;
    }
    if (title.isEmpty()) {
        m_Private->m_Titile = QString(QObject::tr("Unknown"));
    }*/ /*else {
        m_Private->m_Titile = title;
    }
    if (artist.isEmpty()) {
        m_Private->m_Artist = QString(QObject::tr("Unknown"));
    } else {
        m_Private->m_Artist = artist;
    }
    if (album.isEmpty()) {
        m_Private->m_Album = QString(QObject::tr("Unknown"));
    } else {
        m_Private->m_Album = album;
    }*/
    //    QImage image(cover);
    //    if (image.isNull()) {
    //        m_Private->m_Conver = QPixmap(QString(":/Images/Resources/Images/MusicCover.png"));
    //    } else {
    //        QImage mask(":/Images/Resources/Images/MusicCoverMask.png");
    //        QSize size(mask.width(), mask.height());
    //        QImage resultImage(size, QImage::Format_ARGB32_Premultiplied);
    //        QPainter painter(&resultImage);
    //        painter.setCompositionMode(QPainter::CompositionMode_Source);
    //        painter.fillRect(resultImage.rect(), Qt::transparent);
    //        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //        painter.drawImage(0, 0, mask);
    //        painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
    //        painter.drawImage(0, 0, image);
    //        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    //        painter.end();
    //        m_Private->m_Conver = QPixmap::fromImage(resultImage);
    //    }
}

void MusicToolWidget::onTickMarksMillesimalStart()
{
//    g_Multimedia->musicPlayerSetPlayStatus(MPPS_Pause);
}

MusicToolWidgetPrivate::MusicToolWidgetPrivate(MusicToolWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

MusicToolWidgetPrivate::~MusicToolWidgetPrivate()
{
}

void MusicToolWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetBackground"));
    m_PreviousBtn = new BmpButton(m_Parent);
    m_PreviousBtn->setVisible(true);
    m_PreviousBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPreviousBtnNormal"));
    m_PreviousBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPreviousBtnNormal"));
    m_ToggleBtn = new BmpButton(m_Parent);
    m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
    m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
    m_ToggleBtn->setVisible(true);
    m_NextBtn = new BmpButton(m_Parent);
    m_NextBtn->setVisible(true);
    m_NextBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetNextBtnNormal"));
    m_NextBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetNextBtnNormal"));
    m_StopBtn = new BmpButton(m_Parent);
    m_StopBtn->setVisible(true);
    m_StopBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetStopBtnNormal"));
    m_StopBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetStopBtnNormal"));
    m_ModeBtn = new BmpButton(m_Parent);
    m_ModeBtn->setVisible(true);
    m_Slider = new Slider(m_Parent);
    m_Slider->setVisible(true);
    m_Slider->setTickMarksSize(QSize(52 * g_Widget->widthScalabilityFactor(), 52 * g_Widget->heightScalabilityFactor()));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetSliderTickMarksBackground"));
    m_Slider->setTickMarksMillesimal(0);
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setVisible(true);
    m_TitleText->setLanguageType(TextWidget::T_NoTranslate);
    m_TitleText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_TitleText->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
    m_ElapsedTimeText = new TextWidget(m_Parent);
    m_ElapsedTimeText->setVisible(true);
    m_ElapsedTimeText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_ElapsedTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_EndTimeText = new TextWidget(m_Parent);
    m_EndTimeText->setVisible(true);
    m_EndTimeText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    m_EndTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
}

void MusicToolWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MusicToolWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalStart(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalStart()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_PreviousBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_NextBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_StopBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ModeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
}

void MusicToolWidget::onTickMarksMillesimalEnd(const int millesimal)
{
    qDebug() << "onTickMarksMillesimalEnd" << millesimal;
    m_Private->m_Seek = true;
    g_Multimedia->musicPlayerSeekToMillesimal(millesimal);
}

void MusicToolWidget::onToolButtonRelease()
{
    qDebug () << "MusicToolWidget::onToolButtonRelease";
    if (sender() == m_Private->m_PreviousBtn) {
        g_Multimedia->musicPlayerPlayPreviousListViewIndex();
    } else if (sender() == m_Private->m_ToggleBtn) {
        g_Multimedia->musicPlayerSetPlayStatusToggle();
    } else if (sender() == m_Private->m_NextBtn) {
        g_Multimedia->musicPlayerPlayNextListViewIndex();
    } else if (sender() == m_Private->m_ModeBtn) {
        g_Multimedia->musicPlayerSetPlayModeToggle();
    } else if (sender() == m_Private->m_StopBtn) {
        g_Multimedia->musicPlayerSetPlayStatus(MPPS_Stop);
    }
}

QString MusicToolWidgetPrivate::convertTime(const int time)
{
    QString hour("%1");
    QString minute("%1");
    QString second("%1");
    return hour.arg((time / 60) / 60, 2, 10, QChar('0'))
            + QString(":") + minute.arg((time / 60) % 60, 2, 10, QChar('0'))
            + QString(":") + second.arg(time % 60, 2, 10, QChar('0'));
}
