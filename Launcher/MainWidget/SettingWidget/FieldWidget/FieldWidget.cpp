#include "FieldWidget.h"
#include "AutoConnect.h"
#include "BmpWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

class FieldWidgetPrivate
{
    Q_DISABLE_COPY(FieldWidgetPrivate)
public:
    explicit FieldWidgetPrivate(FieldWidget* parent);
    ~FieldWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
private:
    FieldWidget* m_Parent = NULL;
};

FieldWidget::FieldWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new FieldWidgetPrivate(this))
{
}

FieldWidget::~FieldWidget()
{
}

void FieldWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void FieldWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    g_Widget->geometryFit(0, 0, 1002, 552, m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void FieldWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void FieldWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_SettingField: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::Show);
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

FieldWidgetPrivate::FieldWidgetPrivate(FieldWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

FieldWidgetPrivate::~FieldWidgetPrivate()
{
}

void FieldWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageWidgetBackground"));
}

void FieldWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
