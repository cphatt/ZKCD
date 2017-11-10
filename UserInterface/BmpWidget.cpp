#include "BmpWidget.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#ifdef SVG
#include <QSvgRenderer>
#endif
#include <QFile>
#include <QScopedPointer>

class BmpWidgetPrivate
{
    Q_DISABLE_COPY(BmpWidgetPrivate)
public:
    explicit BmpWidgetPrivate(BmpWidget* parent);
    ~BmpWidgetPrivate();
    QScopedPointer<QPixmap> m_BackgroundPixmap;
#ifdef SVG
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
#endif
private:
    BmpWidget* m_Parent = NULL;
};

BmpWidget::BmpWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new BmpWidgetPrivate(this))
{
}

BmpWidget::~BmpWidget()
{
}
static int m_Count(0);
#include <QTime>
void BmpWidget::setBackgroundBmpPath(const QString &path)
{
    QTime time;
    time.start();
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_BackgroundPixmap.reset(new QPixmap(path + QString(".png")));
        qDebug() << path + QString(".png");
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
    m_Count += time.elapsed();
    qDebug() << time.elapsed() << m_Count << "setBackgroundBmpPath" << path;
}

void BmpWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
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
    QWidget::paintEvent(event);
}

BmpWidgetPrivate::BmpWidgetPrivate(BmpWidget *parent)
    : m_Parent(parent)
{
}

BmpWidgetPrivate::~BmpWidgetPrivate()
{
}
