#include "MultimediaLoadingWidget.h"
#include "Widget.h"
#include "AutoConnect.h"
#include "BmpWidget.h"
#include <QPainter>

class MultimediaLoadingWidgetPrivate
{
public:
    explicit MultimediaLoadingWidgetPrivate(MultimediaLoadingWidget* parent);
    ~MultimediaLoadingWidgetPrivate();
    void initialize();
    BmpWidget* m_Background = NULL;
private:
    MultimediaLoadingWidget* m_Parent = NULL;
};

MultimediaLoadingWidget::MultimediaLoadingWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new MultimediaLoadingWidgetPrivate(this))
{
}

MultimediaLoadingWidget::~MultimediaLoadingWidget()
{
}

void MultimediaLoadingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(565, 285, 150, 150, m_Private->m_Background);
//    QWidget::resizeEvent(event);
}

void MultimediaLoadingWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.fillRect(rect(), QColor(0, 0, 1, 127));
//    QWidget::paintEvent(event);
}

MultimediaLoadingWidgetPrivate::MultimediaLoadingWidgetPrivate(MultimediaLoadingWidget *parent)
    : m_Parent(parent)
{
    initialize();
}

MultimediaLoadingWidgetPrivate::~MultimediaLoadingWidgetPrivate()
{
}

void MultimediaLoadingWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->show();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/MultimediaLoadingBackground"));
}
