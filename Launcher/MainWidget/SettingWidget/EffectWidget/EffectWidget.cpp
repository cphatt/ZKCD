#include "EffectWidget.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include "EffectSoundWidget/EffectSoundWidget.h"
#include "EffectToolBarWidget/EffectToolBarWidget.h"
#include <QPainter>

class EffectWidgetPrivate
{
    Q_DISABLE_COPY(EffectWidgetPrivate)
public:
    explicit EffectWidgetPrivate(EffectWidget* parent);
    ~EffectWidgetPrivate();
    void initialize();
    void connectAllSlots();
    EffectSoundWidget* m_EffectSoundWidget = NULL;
    EffectToolBarWidget* m_EffectToolBarWidget = NULL;
private:
    EffectWidget* m_Parent = NULL;
};

EffectWidget::EffectWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new EffectWidgetPrivate(this))
{

}

EffectWidget::~EffectWidget()
{
}

void EffectWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingEffect, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void EffectWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    QWidget::resizeEvent(event);
}

void EffectWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(UserInterfaceUtility::customBlackColor());
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void EffectWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_SettingEffect: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingEffect, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingLanguage:
    case Widget::T_SettingGeneral:
    case Widget::T_SettingField: {
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

EffectWidgetPrivate::EffectWidgetPrivate(EffectWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

EffectWidgetPrivate::~EffectWidgetPrivate()
{
}

void EffectWidgetPrivate::initialize()
{
    m_EffectSoundWidget = new EffectSoundWidget(m_Parent);
    m_EffectToolBarWidget = new EffectToolBarWidget(m_Parent);
}

void EffectWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
