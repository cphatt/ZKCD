#include "EffectSoundWidget.h"
#include "Widget.h"
#include "TextWidget.h"
#include "EffectSoundSlider/EffectSoundSlider.h"
#include "BmpWidget.h"
#include "UserInterfaceUtility.h"
#include <QEvent>
#include <QPainter>

namespace SourceString {
static const QString High_Pitch = QString(QObject::tr("HighPitch"));
static const QString Middle_Pitch = QString(QObject::tr("MiddlePitch"));
static const QString Low_Pitch = QString(QObject::tr("LowPitch"));
}

class EffectSoundWidgetPrivate
{
    Q_DISABLE_COPY(EffectSoundWidgetPrivate)
public:
    explicit EffectSoundWidgetPrivate(EffectSoundWidget* parent);
    ~EffectSoundWidgetPrivate();
    void initialize();
    void connectAllSlots();
    TextWidget* m_HighPitchText = NULL;
    short int m_HightPitchValue = 0;
    EffectSoundSlider* m_HighPitchSlider = NULL;
    TextWidget* m_MiddlePitchText = NULL;
    short int m_MiddlePitchValue = 0;
    EffectSoundSlider* m_MiddlePitchSlider = NULL;
    TextWidget* m_LowPitchText = NULL;
    short int m_LowPitchValue = 0;
    EffectSoundSlider* m_LowPitchSlider = NULL;
    BmpWidget* m_Background = NULL;
private:
    EffectSoundWidget* m_Parent = NULL;
};

EffectSoundWidget::EffectSoundWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new EffectSoundWidgetPrivate(this))
{
    setVisible(true);
}

EffectSoundWidget::~EffectSoundWidget()
{
}

void EffectSoundWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 505 - 73, this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 505 - 73, m_Private->m_Background);
    int width(200);
    int height(50);
    g_Widget->geometryFit(333 + (433 - 333 - width) * 0.5 - 278, 154 + (187 - 154 - height) * 0.5 - 73, width, height, m_Private->m_HighPitchText);
    g_Widget->geometryFit(333 + (433 - 333 - width) * 0.5 - 278, 272 + (304 - 272 - height) * 0.5 - 73, width, height, m_Private->m_MiddlePitchText);
    g_Widget->geometryFit(333 + (433 - 333 - width) * 0.5 - 278, 393 + (424 - 393 - height) * 0.5 - 73, width, height, m_Private->m_LowPitchText);
    width = 1226 - 510;
    height = 68;

    g_Widget->geometryFit(510 - 278,  72 - (height - 50), width, height, m_Private->m_HighPitchSlider);
    g_Widget->geometryFit(510 - 278,  190 - (height - 50), width, height, m_Private->m_MiddlePitchSlider);
    g_Widget->geometryFit(510 - 278,  310 - (height - 50), width, height, m_Private->m_LowPitchSlider);
    QWidget::resizeEvent(event);
}

void EffectSoundWidget::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange: {
        m_Private->m_HighPitchText->setText(QString(QObject::tr(SourceString::High_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_HightPitchValue));
        m_Private->m_MiddlePitchText->setText(QString(QObject::tr(SourceString::Middle_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_MiddlePitchValue));
        m_Private->m_LowPitchText->setText(QString(QObject::tr(SourceString::Low_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_LowPitchValue));
        break;
    }
    default: {
        break;
    }
    }
    QWidget::changeEvent(event);
}

void EffectSoundWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

EffectSoundWidgetPrivate::EffectSoundWidgetPrivate(EffectSoundWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

EffectSoundWidgetPrivate::~EffectSoundWidgetPrivate()
{
}

void EffectSoundWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->show();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/EffectSoundWidgetBackground"));
    m_HighPitchText = new TextWidget(m_Parent);
    m_HighPitchText->setLanguageType(TextWidget::T_NoTranslate);
    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_HighPitchText->setFontPointSize(fontPointSize);
    m_HighPitchText->show();
    m_HighPitchSlider = new EffectSoundSlider(m_Parent);
    m_HighPitchSlider->setMinimumValue(-16);
    m_HighPitchSlider->setMaximumValue(16);
    m_HighPitchSlider->show();
    m_MiddlePitchText = new TextWidget(m_Parent);
    m_MiddlePitchText->setLanguageType(TextWidget::T_NoTranslate);
    m_MiddlePitchText->setFontPointSize(fontPointSize);
    m_MiddlePitchText->show();
    m_MiddlePitchSlider = new EffectSoundSlider(m_Parent);
    m_MiddlePitchSlider->setMinimumValue(-16);
    m_MiddlePitchSlider->setMaximumValue(16);
    m_MiddlePitchSlider->show();
    m_LowPitchText = new TextWidget(m_Parent);
    m_LowPitchText->setLanguageType(TextWidget::T_NoTranslate);
    m_LowPitchText->setFontPointSize(fontPointSize);
    m_LowPitchText->show();
    m_LowPitchSlider = new EffectSoundSlider(m_Parent);
    m_LowPitchSlider->setMinimumValue(-16);
    m_LowPitchSlider->setMaximumValue(16);
    m_LowPitchSlider->show();
    m_HighPitchText->setText(QString(QObject::tr(SourceString::High_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_HightPitchValue));
    m_MiddlePitchText->setText(QString(QObject::tr(SourceString::Middle_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_MiddlePitchValue));
    m_LowPitchText->setText(QString(QObject::tr(SourceString::Low_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_LowPitchValue));
}

void EffectSoundWidgetPrivate::connectAllSlots()
{
}
