#include "Slider.h"
#include "BmpWidget.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QMouseEvent>
#ifdef SVG
#include <QSvgRenderer>
#endif
#include <QPixmap>
#include <QScopedPointer>
#include <QFile>

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
public:
    explicit SliderPrivate(Slider* parent);
    ~SliderPrivate();
    QRect m_TickMarks = QRect(0, 0, 0, 0);
    int m_TickMarksMillesimal = 500;
    bool m_IsTracking = false;
    QScopedPointer<QPixmap> m_BackgroundPixmap;
#ifdef SVG
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
#endif
    QScopedPointer<QPixmap> m_TickMarksPixmap;
#ifdef SVG
    QScopedPointer<QSvgRenderer> m_TickMarksSvg;
#endif
    int m_Minimum = 0;
    int m_Maximum = 40;
    bool m_AllowPress = true;
    bool m_AllowMove = true;
    bool m_StepRange = false;
private:
    Slider* m_Parent = NULL;
};

Slider::Slider(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SliderPrivate(this))
{
}

Slider::~Slider()
{
}

void Slider::setAllowPress(const bool flag)
{
    m_Private->m_AllowPress = flag;
    //    if (!m_Private->m_AllowPress) {
    //        m_Private->m_AllowMove = m_Private->m_AllowPress;
    //    }
}

void Slider::setAllowMove(const bool flag)
{
    if (!m_Private->m_AllowPress) {
        m_Private->m_AllowMove = m_Private->m_AllowPress;
    } else {
        m_Private->m_AllowMove = flag;
    }
}

void Slider::setTracking(const bool flag)
{
    m_Private->m_IsTracking = flag;
}

void Slider::setBackgroundBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_BackgroundPixmap.reset(new QPixmap(path + QString(".png")));
    }
#ifdef SVG
    else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_BackgroundSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
#endif
    else {
        if (!m_Private->m_BackgroundPixmap.isNull()) {
            m_Private->m_BackgroundPixmap.reset(NULL);
        }
#ifdef SVG
        if (!m_Private->m_BackgroundSvg.isNull()) {
            m_Private->m_BackgroundSvg.reset(NULL);
        }
#endif
    }
    if (isVisible()) {
        update();
    }
}

void Slider::setTickMarkTickMarkslBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_TickMarksPixmap.reset(new QPixmap(path + QString(".png")));
    }
#ifdef SVG
    else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_TickMarksSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
#endif
    else {
        if (!m_Private->m_TickMarksPixmap.isNull()) {
            m_Private->m_TickMarksPixmap.reset(NULL);
        }
#ifdef SVG
        if (!m_Private->m_TickMarksSvg.isNull()) {
            m_Private->m_TickMarksSvg.reset(NULL);
        }
#endif
    }
    if (isVisible()) {
        update();
    }
}

void Slider::setTickMarksSize(const QSize &size)
{
    m_Private->m_TickMarks.setSize(size);
    if (isVisible()) {
        update();
    }
}

void Slider::setTickMarksMillesimal(const int millesimal)
{
    int value(millesimal);
    if (millesimal < 0) {
        value = 0;
    } else if (millesimal > 1000) {
        value = 1000;
    }
    if (!m_Private->m_IsTracking) {
        qDebug() << __FUNCTION__ << m_Private->m_TickMarksMillesimal << value << m_Private->m_Maximum << m_Private->m_Minimum;
        if (m_Private->m_StepRange) {
            m_Private->m_StepRange = false;
            if ((m_Private->m_Minimum == m_Private->m_Maximum)
                    || (qAbs(m_Private->m_TickMarksMillesimal - value) < (1000 / (m_Private->m_Maximum - m_Private->m_Minimum)))) {
                return ;
            }
        }
        m_Private->m_TickMarksMillesimal = value;
        if (isVisible()) {
            update();
        }
    }
}

void Slider::setRange(const int minimum, const int maxmum)
{
    m_Private->m_Minimum = minimum;
    m_Private->m_Maximum = maxmum;
}

void Slider::resizeEvent(QResizeEvent *event)
{
    m_Private->m_TickMarks.setHeight(height());
    QWidget::resizeEvent(event);
}

void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //    qDebug() << "m_Private->m_TickMarksMillesimal" << m_Private->m_TickMarksMillesimal << m_Private->m_TickMarksMillesimal % (1000 / (m_Private->m_Maximum - m_Private->m_Minimum));
    //    qDebug() << "" << (m_Private->m_TickMarksMillesimal * (width() - m_Private->m_TickMarks.width())) / 1000;
    //    if (0 == m_Private->m_TickMarksMillesimal << m_Private->m_TickMarksMillesimal % (1000 / (m_Private->m_Maximum - m_Private->m_Minimum))) {
    m_Private->m_TickMarks.moveLeft((m_Private->m_TickMarksMillesimal * (width() - m_Private->m_TickMarks.width())) / 1000);
    //    }
    if (!m_Private->m_BackgroundPixmap.isNull()) {
        painter.drawPixmap(QRect((width() - m_Private->m_BackgroundPixmap->width() * g_Widget->widthScalabilityFactor()) / 2, (height() - m_Private->m_BackgroundPixmap->height() * g_Widget->heightScalabilityFactor()) / 2, m_Private->m_BackgroundPixmap->width() * g_Widget->widthScalabilityFactor(), m_Private->m_BackgroundPixmap->height() * g_Widget->heightScalabilityFactor()), *m_Private->m_BackgroundPixmap);
    }
#ifdef SVG
    else if (!m_Private->m_BackgroundSvg.isNull()) {
        m_Private->m_BackgroundSvg->render(&painter, QRect((width() - m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                           (height() - m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                           m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                           m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
#endif
    if (!m_Private->m_TickMarksPixmap.isNull()) {
        painter.drawPixmap(QRect((m_Private->m_TickMarks.width() - m_Private->m_TickMarksPixmap->width() * g_Widget->widthScalabilityFactor()) / 2 + m_Private->m_TickMarks.x(),
                                 (m_Private->m_TickMarks.height() - m_Private->m_TickMarksPixmap->height() * g_Widget->heightScalabilityFactor()) / 2 + m_Private->m_TickMarks.y(),
                                 m_Private->m_TickMarksPixmap->width() * g_Widget->widthScalabilityFactor(), m_Private->m_TickMarksPixmap->height() * g_Widget->heightScalabilityFactor()),
                           *m_Private->m_TickMarksPixmap);
    }
#ifdef SVG
    else if (!m_Private->m_TickMarksSvg.isNull()) {
        m_Private->m_TickMarksSvg->render(&painter, QRect((m_Private->m_TickMarks.width() - m_Private->m_TickMarksSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2 + m_Private->m_TickMarks.x(),
                                                          (height() - m_Private->m_TickMarksSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                          m_Private->m_TickMarksSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                          m_Private->m_TickMarksSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
#endif
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if (m_Private->m_AllowPress) {
        m_Private->m_IsTracking = true;
        int x = event->pos().x();
        if (x < m_Private->m_TickMarks.width() / 2) {
            x = m_Private->m_TickMarks.width() / 2;
        } else if (x > (width() - m_Private->m_TickMarks.width() / 2)) {
            x = width() - m_Private->m_TickMarks.width() / 2;
        }
        if (m_Private->m_TickMarks.left() != (x - m_Private->m_TickMarks.width() / 2)) {
            m_Private->m_TickMarks.moveLeft(x - m_Private->m_TickMarks.width() / 2);
            update();
        }
        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        m_Private->m_StepRange = true;
        emit tickMarksMillesimalStart(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    //    qWarning() << "Slider::mouseMoveEvent" << m_Private->m_AllowPress << m_Private->m_AllowMove << event->pos();
    if (m_Private->m_AllowPress
            && m_Private->m_AllowMove) {
        //        if (m_Private->m_TickMarks.contains(event->pos())) {
        int x = event->pos().x();
        if (x < m_Private->m_TickMarks.width() / 2) {
            x = m_Private->m_TickMarks.width() / 2;
        } else if (x > (width() - m_Private->m_TickMarks.width() / 2)) {
            x = width() - m_Private->m_TickMarks.width() / 2;
        }
        if (m_Private->m_TickMarks.left() != (x - m_Private->m_TickMarks.width() / 2)) {
            m_Private->m_TickMarks.moveLeft(x - m_Private->m_TickMarks.width() / 2);
            update();
        }
        //        }
        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        m_Private->m_StepRange = true;
        emit tickMarksMillesimalChange(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mouseMoveEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_Private->m_AllowPress
            && m_Private->m_IsTracking) {
        m_Private->m_IsTracking = false;
        //        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        emit tickMarksMillesimalEnd(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mouseReleaseEvent(event);
}

SliderPrivate::SliderPrivate(Slider* parent)
    : m_Parent(parent)
{
}

SliderPrivate::~SliderPrivate()
{
}
