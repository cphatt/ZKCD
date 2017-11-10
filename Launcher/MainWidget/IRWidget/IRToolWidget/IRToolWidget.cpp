#include "IRToolWidget.h"
#include "BmpWidget.h"
#include "Widget.h"
#include "BmpButton.h"
#include "TextWidget.h"
#include "AutoConnect.h"
#include "AudioConfig.h"
#include "UserInterfaceUtility.h"

namespace SourceString {
static const QString IR = QString(QObject::tr("IR"));
static const QString IRA = QString(QObject::tr("IRA"));
static const QString IRB = QString(QObject::tr("IRB"));
static const QString On = QString(QObject::tr("On"));
static const QString Off = QString(QObject::tr("Off"));
}

class IRToolWidgetPrivate
{
    Q_DISABLE_COPY(IRToolWidgetPrivate)
public:
    explicit IRToolWidgetPrivate(IRToolWidget* parent);
    ~IRToolWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
    TextWidget* m_TitleText = NULL;
    BmpButton* m_IRABtn = NULL;
    TextWidget* m_IRAText = NULL;
    BmpButton* m_IRBBtn = NULL;
    TextWidget* m_IRBText = NULL;
    BmpButton* m_IRToggleBtn = NULL;
    TextWidget* m_IRToggleText = NULL;
private:
    IRToolWidget* m_Parent = NULL;
};

IRToolWidget::IRToolWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new IRToolWidgetPrivate(this))
{
    setVisible(true);
}

IRToolWidget::~IRToolWidget()
{
}

void IRToolWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(213, 180, 853, 360, this);
    g_Widget->geometryFit(0, 0, 853, 360, m_Private->m_Background);
    g_Widget->geometryFit(0, 0, 853, 180, m_Private->m_TitleText);
    int width(161);
    int height(108);
    g_Widget->geometryFit(66 + (132 + width) * 0, 180 + (180 - height) * 0.5, width, height, m_Private->m_IRABtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_IRAText);
    g_Widget->geometryFit(66 + (132 + width) * 1, 180 + (180 - height) * 0.5, width, height, m_Private->m_IRBBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_IRBText);
    g_Widget->geometryFit(66 + (132 + width) * 2, 180 + (180 - height) * 0.5, width, height, m_Private->m_IRToggleBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_IRToggleText);
}

void IRToolWidget::onIRIsOpen(int open)
{
    qDebug() << "IRToolWidget::onIRIsOpen" << open;
    if (1 == open) {
        m_Private->m_IRToggleText->setText(SourceString::On);
    } else {
        m_Private->m_IRToggleText->setText(SourceString::Off);
        m_Private->m_IRABtn->setStatus(BmpButton::B_Normal);
        m_Private->m_IRBBtn->setStatus(BmpButton::B_Normal);
    }
}

void IRToolWidget::onIRChange(IR_Mode mode)
{
    qDebug() << "IRToolWidget::onIRChange" << mode;
    switch (mode) {
    case IR_A: {
        m_Private->m_IRABtn->setStatus(BmpButton::B_Check);
        m_Private->m_IRBBtn->setStatus(BmpButton::B_Normal);
        break;
    }
    case IR_B: {
        m_Private->m_IRABtn->setStatus(BmpButton::B_Normal);
        m_Private->m_IRBBtn->setStatus(BmpButton::B_Check);
        break;
    }
    default: {
        break;
    }
    }
}

void IRToolWidget::onVolumeChange(OutPutSource type, const int volume)
{
    if (OPS_IR != type) {
        onIRIsOpen(0);
    }
}

void IRToolWidget::onToolButtonRelease()
{
    qDebug() << "IRToolWidget::onToolButtonRelease";
    BmpButton* ptr = qobject_cast<BmpButton*>(sender());
    if (ptr == m_Private->m_IRABtn) {
        qDebug() << "m_Private->m_IRABtn";
        g_Audio->requestIRMode(IR_A);
    } else if (ptr == m_Private->m_IRBBtn) {
        qDebug() << "m_Private->m_IRBBtn";
        g_Audio->requestIRMode(IR_B);
    } if (ptr == m_Private->m_IRToggleBtn) {
        g_Audio->requestIRToggle();
        qDebug() << "m_Private->m_IRToggleBtn";
    }
}

IRToolWidgetPrivate::IRToolWidgetPrivate(IRToolWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

IRToolWidgetPrivate::~IRToolWidgetPrivate()
{
}

void IRToolWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/MessageBackground"));
    m_Background->setVisible(true);
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setAlignmentFlag(Qt::AlignCenter);
    int fontPointSize(40 * g_Widget->widthScalabilityFactor());
    m_TitleText->setFontPointSize(fontPointSize);
    m_TitleText->setText(SourceString::IR);
    m_TitleText->setVisible(true);
    m_IRABtn = new BmpButton(m_Parent);
    m_IRABtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRABtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRABtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_IRAText = new TextWidget(m_IRABtn);
    m_IRAText->setText(SourceString::IRA);
    m_IRAText->setVisible(true);
    m_IRABtn->setVisible(true);
    m_IRBBtn = new BmpButton(m_Parent);
    m_IRBBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRBBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRBBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_IRBText = new TextWidget(m_IRBBtn);
    m_IRBText->setText(SourceString::IRB);
    m_IRBText->setVisible(true);
    m_IRBBtn->setVisible(true);
    m_IRToggleBtn = new BmpButton(m_Parent);
    m_IRToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_IRToggleText = new TextWidget(m_IRToggleBtn);
    m_IRToggleText->setText(SourceString::Off);
    m_IRToggleText->setVisible(true);
    m_IRToggleBtn->setVisible(true);
}

void IRToolWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_IRABtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_IRBBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_IRToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onToolButtonRelease()),
                     type);
}
