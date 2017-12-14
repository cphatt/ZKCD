#include "Widget.h"
#include "BusinessLogicUtility.h"
#include "ArkApplication.h"
#include <QDesktopWidget>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>

class WidgetPrivate
{
    Q_DISABLE_COPY(WidgetPrivate)
public:
    explicit WidgetPrivate(Widget* parent);
    ~WidgetPrivate();
    void initialize();
    Widget::Type M_Type = Widget::T_Home;
    int m_BaseWindowWidth = 1280;
    float m_WidthScalabilityFactor = 1.0f;
    int m_BaseWindowHeight = 720;
    float m_HeightScalabilityFactor = 1.0f;
    int m_BaseStatusBarHeight = 60;
    int m_BaseTabBarHeight = 96;
private:
    Widget* m_Parent = NULL;
};

QRect Widget::geometryFit(const int x, const int y, const int w, const int h, QWidget *widget)
{
    initializePrivate();
    int ax = x * m_Private->m_WidthScalabilityFactor;
    int ay = y * m_Private->m_HeightScalabilityFactor;
    int aw = w * m_Private->m_WidthScalabilityFactor;
    int ah = h * m_Private->m_HeightScalabilityFactor;
    if (NULL != widget) {
        widget->move(ax, ay);
        widget->setFixedSize(QSize(aw, ah));
    }
    QRect rect(ax, ay, aw, ah);
    return rect;
}

int Widget::baseWindowWidth()
{
    initializePrivate();
    return m_Private->m_BaseWindowWidth;
}

int Widget::baseWindowHeight()
{
    initializePrivate();
    return m_Private->m_BaseWindowHeight;
}

int Widget::baseStatusBarHeight()
{
    initializePrivate();
    return m_Private->m_BaseStatusBarHeight;
}

int Widget::baseTabBarHeight()
{
    initializePrivate();
    return m_Private->m_BaseTabBarHeight;
}

float Widget::widthScalabilityFactor()
{
    initializePrivate();
    return m_Private->m_WidthScalabilityFactor;
}

float Widget::heightScalabilityFactor()
{
    initializePrivate();
    return m_Private->m_HeightScalabilityFactor;
}

void Widget::setWidgetType(const Widget::Type type, const QString &status)
{
    initializePrivate();
    if (type != m_Private->M_Type) {
        m_Private->M_Type = type;
    }
    emit ontWidgetTypeChange(m_Private->M_Type, status);
}

Widget::Widget(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
}

Widget::~Widget()
{
    qDebug();
}

void Widget::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new WidgetPrivate(this));
    }
}

WidgetPrivate::WidgetPrivate(Widget* parent)
    : m_Parent(parent)
{
    initialize();
}

WidgetPrivate::~WidgetPrivate()
{
}

void WidgetPrivate::initialize()
{
    int windowWidth(1280);
    int windowHeight(720);
    QDesktopWidget* dekstopWidget = ArkApplication::desktop();
    if (NULL != dekstopWidget) {
        windowWidth = dekstopWidget->width();
        windowHeight = dekstopWidget->height();
        //        windowWidth = 800;
        //        windowHeight = 480;
        qDebug() << "dekstopWidget" << windowWidth << windowHeight;
    } else {
        int fd = open("/dev/fb0", O_RDONLY);
        if (fd) {
            struct fb_var_screeninfo fb_var;
            if (-1 != ioctl(fd, FBIOGET_VSCREENINFO, &fb_var)) {
                windowWidth = fb_var.xres;
                windowHeight = fb_var.yres;
                close(fd);
            }
        }
    }
    m_WidthScalabilityFactor = windowWidth / static_cast<float>(m_BaseWindowWidth);
    m_HeightScalabilityFactor = windowHeight / static_cast<float>(m_BaseWindowHeight);
    qDebug() << "m_WidthScalabilityFactor" << m_WidthScalabilityFactor;
    qDebug() << "m_HeightScalabilityFactor" << m_HeightScalabilityFactor;
}
