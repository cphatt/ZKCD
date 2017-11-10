#include "VersionWidget.h"
#include "AutoConnect.h"
#include "BmpWidget.h"
#include "UserInterfaceUtility.h"
#include "VersionListView/VersionListView.h"
#include <QPainter>

class VersionWidgetPrivate
{
    Q_DISABLE_COPY(VersionWidgetPrivate)
public:
    explicit VersionWidgetPrivate(VersionWidget* parent);
    ~VersionWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
    VersionListView* m_VersionListView = NULL;
private:
    VersionWidget* m_Parent = NULL;
};

VersionWidget::VersionWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VersionWidgetPrivate(this))
{
}

VersionWidget::~VersionWidget()
{
}

void VersionWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingVersion, WidgetStatus::Show);
}

void VersionWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    g_Widget->geometryFit(0, 0, 1002, 552, m_Private->m_Background);
}

void VersionWidget::paintEvent(QPaintEvent *event)
{
}

void VersionWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_SettingVersion: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingVersion, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingLanguage:
    case Widget::T_SettingGeneral:
    case Widget::T_SettingEffect: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

VersionWidgetPrivate::VersionWidgetPrivate(VersionWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

VersionWidgetPrivate::~VersionWidgetPrivate()
{
}

void VersionWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageWidgetBackground"));
    m_VersionListView = new VersionListView(m_Parent);
}

void VersionWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
