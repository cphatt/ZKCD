#include "GeneralSlider.h"
#include "BmpButton.h"
#include "Slider.h"
#include "TextWidget.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

class GeneralSliderPrivate
{
    Q_DISABLE_COPY(GeneralSliderPrivate)
public:
    explicit GeneralSliderPrivate(GeneralSlider* parent);
    ~GeneralSliderPrivate();
    void initialize();
    void connectAllSlots();
    TextWidget* m_MinimumText = NULL;
    TextWidget* m_MaxmumText = NULL;
    BmpButton* m_MinusBtn = NULL;
    BmpButton* m_PlusBtn = NULL;
    Slider* m_Slider = NULL;
private:
    GeneralSlider* m_Parent = NULL;
};

GeneralSlider::GeneralSlider(QWidget *parent)
    : QWidget(parent)
    , m_Private(new GeneralSliderPrivate(this))
{  
    setVisible(true);
}

GeneralSlider::~GeneralSlider()
{
}

void GeneralSlider::setMinimumValue(const int value)
{
    m_Private->m_MinimumText->setText(QString::number(value));
}

void GeneralSlider::setMaximumValue(const int value)
{
    m_Private->m_MaxmumText->setText(QString::number(value));
}

void GeneralSlider::setTickMarksMillesimal(const int millesimal)
{
    m_Private->m_Slider->setTickMarksMillesimal(millesimal);
}

void GeneralSlider::resizeEvent(QResizeEvent *event)
{
    int width(100);
    int height(40);
    g_Widget->geometryFit(577 - 536 + 51, 0, width, height, m_Private->m_MinimumText);
    g_Widget->geometryFit(636 - 92 - width, 0, width, height, m_Private->m_MaxmumText);
    width = 92;
    height = 92;
    g_Widget->geometryFit(536 - 536, 0, width, height, m_Private->m_MinusBtn);
    g_Widget->geometryFit(636 - width, 0, width, height, m_Private->m_PlusBtn);
    g_Widget->geometryFit(577 - 536 + 51, 0, 1027 - 577, height, m_Private->m_Slider);
    QWidget::resizeEvent(event);
}

void GeneralSlider::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

GeneralSliderPrivate::GeneralSliderPrivate(GeneralSlider *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

GeneralSliderPrivate::~GeneralSliderPrivate()
{
}

void GeneralSliderPrivate::initialize()
{
    m_MinimumText = new TextWidget(m_Parent);
    m_MinimumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MinimumText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_MinimumText->setVisible(true);
    m_MaxmumText = new TextWidget(m_Parent);
    m_MaxmumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MaxmumText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    m_MaxmumText->setVisible(true);
    m_MinusBtn = new BmpButton(m_Parent);
    m_MinusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/GeneralSliderMinusNormal"));
    m_MinusBtn->setPressBmpPath(QString(":/Images/Resources/Images/GeneralSliderMinusNormal"));
    m_MinusBtn->setVisible(true);
    m_PlusBtn = new BmpButton(m_Parent);
    m_PlusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/GeneralSliderPlusNormal"));
    m_PlusBtn->setPressBmpPath(QString(":/Images/Resources/Images/GeneralSliderPlusNormal"));
    m_PlusBtn->setVisible(true);
    m_Slider = new Slider(m_Parent);
    m_Slider->setRange(0, 15);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
    m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/GeneralSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setVisible(true);
}

void GeneralSliderPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_MinusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SIGNAL(minusBtnRelease()),
                     type);
    QObject::connect(m_PlusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SIGNAL(plusBtnRelease()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,  SIGNAL(tickMarksMillesimalEnd(const int)),
                     type);
}
