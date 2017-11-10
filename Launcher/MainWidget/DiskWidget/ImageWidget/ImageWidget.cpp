#include "ImageWidget.h"
#include "BusinessLogicUtility.h"
#include "UserInterfaceUtility.h"
#include "ImageStatusWidget/ImageStatusWidget.h"
#include "PixmapWidget/PixmapWidget.h"
#include "ImageShortCutWidget/ImageShortCutWidget.h"
#include "ImageLoadingWidget/ImageLoadingWidget.h"
#include "ImageToolBarWidget/ImageToolBarWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QImageReader>
#include <QMouseEvent>
#include <QTimer>

class ImageWidgetPrivate
{
public:
    explicit ImageWidgetPrivate(ImageWidget *parent);
    ~ImageWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void imageWidgetSwitchHandler(const QString &status);
    ImageStatusWidget* m_StatusWidget = NULL;
    ImageToolBarWidget* m_ToolBarWidget = NULL;
    PixmapWidget* m_PixmapWidget = NULL;
    ImageLoadingWidget* m_ImageLoadingWidget = NULL;
    ImageShortCutWidget* m_ImageShortCutWidget = NULL;
    QTimer* m_Timer = NULL;
    QTimer* m_AnimationTimer = NULL;
    QRect m_TouchRect = QRect(0, 0, 0, 0);
    QImage m_Image;
    float m_Scale = 1.0f;
    QImageReader m_ImageReader;
    QMatrix m_Matrix;
private:
    ImageWidget *m_Parent = NULL;
};

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ImageWidgetPrivate(this))
{
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), UserInterfaceUtility::customBlackColor());
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
    qWarning() << event->pos();
    if (m_Private->m_TouchRect.contains(event->pos())) {
        if (QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight()) == m_Private->m_TouchRect) {
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::Show);
        } else {
            g_Widget->setWidgetType(Widget::T_ImageFullScreen, WidgetStatus::Show);
        }
    }
}

void ImageWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Image: {
        m_Private->imageWidgetSwitchHandler(status);
        break;
    }
    case Widget::T_ImageFullScreen: {
        if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
            m_Private->m_Timer->stop();
            setVisible(true);
        }
        break;
    }
    default : {
        if (WidgetStatus::Show == status) {
            m_Private->m_Timer->stop();
            setVisible(false);
        }
        break;
    }
    }
}

void ImageWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "ImageWidget::onImagePlayerPlayStatus" << status;
    switch (status) {
    case IPPS_Start: {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        m_Private->m_PixmapWidget->setVisible(false);
        break;
    }
    case IPPS_Pause:
    case IPPS_Play: {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        m_Private->m_PixmapWidget->setVisible(true);
        break;
    }
    case IPPS_Exit: {
        m_Private->m_Timer->stop();
        m_Private->m_AnimationTimer->stop();
        break;
    }
    default: {
        break;
    }
    }
}

void ImageWidget::onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate)
{
    qDebug() << "ImageWidget::onImagePlayerChange" << type << filePath << index << percent << rotate;
    m_Private->m_ImageReader.setFileName(filePath);
    QString tmpPath(filePath);
    if (!m_Private->m_ImageReader.canRead()) {
        tmpPath = QString(":/Images/Resources/Images/ImageLoadFailedBackground.png");
    }
    m_Private->m_Scale = (static_cast<const float>(percent) / 100);
    m_Private->m_Image.load(tmpPath);
    m_Private->m_Matrix.reset();
    m_Private->m_Matrix.rotate(rotate);
    qDebug() << "m_Private->m_Matrix" << rotate;
    if ((tmpPath == filePath)
            && (m_Private->m_ImageReader.supportsAnimation())) {
        m_Private->m_AnimationTimer->setSingleShot(false);
        m_Private->m_AnimationTimer->start(0);
    } else {
        m_Private->m_Image = m_Private->m_Image.scaled(m_Private->m_Image.width() * g_Widget->widthScalabilityFactor(), m_Private->m_Image.height() * g_Widget->heightScalabilityFactor(), Qt::KeepAspectRatio);
        m_Private->m_AnimationTimer->setSingleShot(true);
        m_Private->m_AnimationTimer->start(0);
    }
}

void ImageWidget::onStartTimer()
{
    qDebug() << "onStartTimer";
    if (QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight()) != m_Private->m_TouchRect) {
        m_Private->m_Timer->start();
    }
}

void ImageWidget::onStopTimer()
{
    qDebug() << "onStopTimer";
    m_Private->m_Timer->stop();
}

ImageWidgetPrivate::ImageWidgetPrivate(ImageWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

ImageWidgetPrivate::~ImageWidgetPrivate()
{
}

void ImageWidgetPrivate::initialize()
{
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(7000);
    m_AnimationTimer = new QTimer(m_Parent);
    m_AnimationTimer->setSingleShot(false);
    m_PixmapWidget = new PixmapWidget(m_Parent);
    m_StatusWidget = new ImageStatusWidget(m_Parent);
    m_ToolBarWidget = new ImageToolBarWidget(m_Parent);
    m_ImageLoadingWidget = new ImageLoadingWidget(m_Parent);
    m_ImageShortCutWidget = new ImageShortCutWidget(m_Parent);
}

void ImageWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
    QObject::connect(m_AnimationTimer,  SIGNAL(timeout()),
                     m_Parent,          SLOT(onTimeout()),
                     type);
    //    QObject::connect(m_PixmapWidget,  SIGNAL(startTimer()),
    //                     m_Parent,        SLOT(onStartTimer()),
    //                     type);
    //    QObject::connect(m_PixmapWidget,  SIGNAL(stopTimer()),
    //                     m_Parent,        SLOT(onStopTimer()),
    //                     type);
}

void ImageWidget::onTimeout()
{
    const QTimer* ptr = qobject_cast<QTimer*>(sender());
    if (ptr == m_Private->m_Timer) {
        g_Widget->setWidgetType(Widget::T_ImageFullScreen, WidgetStatus::Show);
    } else if (ptr == m_Private->m_AnimationTimer) {
        qDebug() << "ImageWidget::onTimeout" << isVisible();
        if (isVisible()) {
            if (m_Private->m_ImageReader.supportsAnimation()) {
                m_Private->m_AnimationTimer->setInterval(m_Private->m_ImageReader.nextImageDelay());
                if (m_Private->m_ImageReader.currentImageNumber() >= (m_Private->m_ImageReader.imageCount() - 1)) {
                    m_Private->m_ImageReader.setFileName(m_Private->m_ImageReader.fileName());
                }
                m_Private->m_ImageReader.read(&m_Private->m_Image);
            }
            m_Private->m_Image = m_Private->m_Image.scaled(m_Private->m_Image.width() * m_Private->m_Scale, m_Private->m_Image.height() * m_Private->m_Scale, Qt::KeepAspectRatio).transformed(m_Private->m_Matrix, Qt::SmoothTransformation);
            m_Private->m_PixmapWidget->onPixmapChange(QPixmap::fromImage(m_Private->m_Image), false);
        }
    }
}

void ImageWidgetPrivate::imageWidgetSwitchHandler(const QString &status)
{
    qDebug() << "ImageWidgetPrivate::imageWidgetSwitchHandler" << status;
    if (WidgetStatus::RequestShow == status) {
        g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::Show);
    } else if (WidgetStatus::Show == status) {
        m_TouchRect = g_Widget->geometryFit(0, 74, g_Widget->baseWindowWidth() - 0, g_Widget->baseWindowHeight() - 74 - 103);
        m_Parent->setVisible(true);
        m_Timer->start();
    }
}
