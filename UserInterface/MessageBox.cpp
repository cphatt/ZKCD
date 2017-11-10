

#include "MessageBox.h"
#include "Utility.h"
#include "BmpWidget.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QTimer>
#include <QFont>
#ifdef SVG
#include <QSvgRenderer>
#endif

class MessageBoxPrivate
{
    Q_DISABLE_COPY(MessageBoxPrivate)
public:
    explicit MessageBoxPrivate(MessageBox *parent);
    ~MessageBoxPrivate();
    void initialize();
    void connectAllSlots();
    QString m_Text;
    QTimer* m_Timer = NULL;
    QScopedPointer<QPixmap> m_BackgroundPixmap;
#ifdef SVG
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
#endif
    QFont m_Font;
    bool m_AutoHide = true;
private:
    MessageBox *m_Parent;
};

MessageBox::MessageBox(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MessageBoxPrivate(this))
{
}

MessageBox::~MessageBox()
{
}

void MessageBox::setText(const QString &text)
{
    if (text != m_Private->m_Text) {
        m_Private->m_Text = text;
        if (isVisible()) {
            update();
        }
    }
}

void MessageBox::setAutoHide(const bool flag)
{
    if (flag != m_Private->m_AutoHide) {
        m_Private->m_AutoHide = flag;
    }
}

void MessageBox::setFontPointSize(const int pointSize)
{
    m_Private->m_Font.setPointSize(pointSize);
    if (isVisible()) {
        update();
    }
}

void MessageBox::showEvent(QShowEvent *event)
{
    m_Private->m_Timer->start();
    emit messageWidgetChange(MessageBox::T_Show);
    QWidget::showEvent(event);
}

void MessageBox::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void MessageBox::hideEvent(QHideEvent *event)
{
    if (isVisible()) {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->stop();
        }
        emit messageWidgetChange(MessageBox::T_Hide);
    }
    QWidget::hideEvent(event);
}

void MessageBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1));
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
    if (!m_Private->m_Text.isEmpty()) {
        painter.setFont(m_Private->m_Font);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
    }
    QWidget::paintEvent(event);
}

void MessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_Private->m_AutoHide && isVisible()) {
        setVisible(false);
    }
    QWidget::mouseReleaseEvent(event);
}

MessageBoxPrivate::MessageBoxPrivate(MessageBox *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MessageBoxPrivate::~MessageBoxPrivate()
{
}
#include <QFile>
void MessageBoxPrivate::initialize()
{
    m_BackgroundPixmap.reset(NULL);
#ifdef SVG
    m_BackgroundSvg.reset(NULL);
#endif
    QString path(":/Images/Resources/Images/MessageBackground");
    if (QFile(path + QString(".png")).exists()) {
        m_BackgroundPixmap.reset(new QPixmap(path + QString(".png")));
    }
#ifdef SVG
    else if (QFile(path + QString(".svg")).exists()) {
        m_BackgroundSvg.reset(new QSvgRenderer(path + QString(".svg"), m_Parent));
    }
#endif
    m_Text.clear();
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(3000);
}

void MessageBoxPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeOut()),
                     type);
}

void MessageBox::onTimeOut()
{
    if (m_Private->m_AutoHide && isVisible()) {
        setVisible(false);
    }
    emit messageShowTimeout();
}
