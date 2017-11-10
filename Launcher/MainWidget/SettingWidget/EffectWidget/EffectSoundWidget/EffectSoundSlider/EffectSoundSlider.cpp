#include "EffectSoundSlider.h"
#include "BmpButton.h"
#include "Slider.h"
#include "TextWidget.h"
#include "UserInterfaceUtility.h"
#include "Widget.h"
#include <QPainter>

class EffectSoundSliderPrivate
{
    Q_DISABLE_COPY(EffectSoundSliderPrivate)
public:
    explicit EffectSoundSliderPrivate(EffectSoundSlider* parent);
    ~EffectSoundSliderPrivate();
    TextWidget* m_MinimumText = NULL;
    TextWidget* m_MaxmumText = NULL;
    BmpButton* m_MinusBtn = NULL;
    BmpButton* m_PlusBtn = NULL;
    Slider* m_Slider = NULL;
    void initialize();
    void connectAllSlots();
private:
    EffectSoundSlider* m_Parent = NULL;
};

EffectSoundSlider::EffectSoundSlider(QWidget *parent)
    : QWidget(parent)
    , m_Private(new EffectSoundSliderPrivate(this))
{
    setVisible(true);
}

EffectSoundSlider::~EffectSoundSlider()
{
}

void EffectSoundSlider::setMinimumValue(const int value)
{
    m_Private->m_MinimumText->setText(QString::number(value));
}

void EffectSoundSlider::setMaximumValue(const int value)
{
    m_Private->m_MaxmumText->setText(QString::number(value));
}

void EffectSoundSlider::resizeEvent(QResizeEvent *event)
{
    int width(100);
    int height(132 - 102);
    g_Widget->geometryFit((716 - 619) * 0.5 + 20, 0, width, height, m_Private->m_MinimumText);
    g_Widget->geometryFit(716 - width - ((716 - 619) * 0.5 + 20), 0, width, height, m_Private->m_MaxmumText);
    g_Widget->geometryFit(0, (68 - 50) + (50 - 37) * 0.5, 31, 37, m_Private->m_MinusBtn);
    g_Widget->geometryFit((716 - 619) * 0.5, (68 - 50) + (50 - 40) * 0.5, 619, 40, m_Private->m_Slider);
    g_Widget->geometryFit(716 - 31, (68 - 50) + (50 - 37) * 0.5, 31, 37, m_Private->m_PlusBtn);
    QWidget::resizeEvent(event);
}

void EffectSoundSlider::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

EffectSoundSliderPrivate::EffectSoundSliderPrivate(EffectSoundSlider *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

EffectSoundSliderPrivate::~EffectSoundSliderPrivate()
{
}

void EffectSoundSliderPrivate::initialize()
{
    m_MinimumText = new TextWidget(m_Parent);
    m_MinimumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MinimumText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_MinimumText->show();
    m_MaxmumText = new TextWidget(m_Parent);
    m_MaxmumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MaxmumText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    m_MaxmumText->show();
    m_MinusBtn = new BmpButton(m_Parent);
    m_MinusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderMinusNormal"));
    m_MinusBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderMinusNormal"));
    m_MinusBtn->show();
    m_PlusBtn = new BmpButton(m_Parent);
    m_PlusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderPlusNormal"));
    m_PlusBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderPlusNormal"));
    m_PlusBtn->show();
    m_Slider = new Slider(m_Parent);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
    m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setAllowMove(false);
    m_Slider->show();
}

void EffectSoundSliderPrivate::connectAllSlots()
{
}
