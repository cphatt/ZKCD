#include "SettingWidget.h"
#include "Widget.h"
#include "BusinessLogicUtility.h"
#include "BmpButton.h"
#include "UserInterfaceUtility.h"
#include "GeneralWidget/GeneralWidget.h"
#include "LanguageWidget/LanguageWidget.h"
//#include "EffectWidget/EffectWidget.h"
//#include "FieldWidget/FieldWidget.h"
#include "VersionWidget/VersionWidget.h"
#include "TextWidget.h"
#include "EventEngine.h"
#include "BusinessLogicUtility.h"

namespace SourceString {
static const QString General = QString(QObject::tr("General"));
static const QString Language = QString(QObject::tr("Language"));
//static const QString Effect = QString(QObject::tr("Effect"));
//static const QString Field = QString(QObject::tr("Field"));
static const QString Version = QString(QObject::tr("Version"));
}

class SettingWidgetPrivate
{
public:
    explicit SettingWidgetPrivate(SettingWidget *parent);
    ~SettingWidgetPrivate();
    void initializeSettingWidget();
    void initializeGeneralWidget();
    void initializeLanguageWidget();
    //    void initializeEffectWidget();
    //    void initializeFieldWidget();
    void initializeVersionWidget();
    void connectAllSlots();
    BmpButton* m_GeneralBtn = NULL;
    TextWidget* m_GeneralText = NULL;
    BmpButton* m_LanguageBtn = NULL;
    TextWidget* m_LanguageText = NULL;
    //    BmpButton* m_EffectBtn = NULL;
    //    TextWidget* m_EffectText = NULL;
    //    BmpButton* m_FieldBtn = NULL;
    //    TextWidget* m_FieldText = NULL;
    BmpButton* m_VersionBtn = NULL;
    TextWidget* m_VersionText = NULL;
    GeneralWidget* m_GeneralWidget = NULL;
    LanguageWidget* m_LanguageWidget = NULL;
//    EffectWidget* m_EffectWidget = NULL;
//    FieldWidget* m_FieldWidget = NULL;
    VersionWidget* m_VersionWidget = NULL;
private:
    SettingWidget* m_Parent = NULL;
};

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SettingWidgetPrivate(this))
{
    g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::Show);
    lower();
    setVisible(true);
}

SettingWidget::~SettingWidget()
{
}

void SettingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void SettingWidget::showEvent(QShowEvent *event)
{
    if (NULL != m_Private) {
        m_Private->connectAllSlots();
        UserInterfaceUtility::elapsed(QString("SettingWidget::showEvent"));
    }
}

void SettingWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "SettingWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        }
        break;
    }
    case Widget::T_Setting: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            lower();
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingGeneral: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Check);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            //            if (NULL != m_Private->m_EffectBtn) {
            //                m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            //            }
            //            if (NULL != m_Private->m_FieldBtn) {
            //                m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
            //            }
            m_Private->m_VersionBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingLanguage: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Check);
            //            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_VersionBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingEffect: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_EffectBtn->setStatus(BmpButton::B_Check);
            //            m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingField:  {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_FieldBtn->setStatus(BmpButton::B_Check);
        }
        break;
    }
    case Widget::T_SettingVersion:  {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            //            m_Private->m_FieldBtn->setStatus(BmpButton::B_Check);
            m_Private->m_VersionBtn->setStatus(BmpButton::B_Check);
        }
        break;
    }
    default: {
        setVisible(false);
        break;
    }
    }
}

void SettingWidget::onBmpButtonRelease()
{
    BmpButton* ptr = qobject_cast<BmpButton*>(sender());
    if (ptr == m_Private->m_GeneralBtn) {
        g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::RequestShow);
    } else if (ptr == m_Private->m_LanguageBtn) {
        m_Private->initializeLanguageWidget();
        g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::RequestShow);
    }/* else if (sender() == m_Private->m_EffectBtn) {
        m_Private->initializeEffectWidget();
        g_Widget->setWidgetType(Widget::T_SettingEffect, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_FieldBtn) {
        m_Private->initializeFieldWidget();
        g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::RequestShow);
    }*/ else if (ptr == m_Private->m_VersionBtn) {
        m_Private->initializeVersionWidget();
        g_Widget->setWidgetType(Widget::T_SettingVersion, WidgetStatus::RequestShow);
    }
}

SettingWidgetPrivate::SettingWidgetPrivate(SettingWidget *parent)
    : m_Parent(parent)
{
    initializeSettingWidget();
    initializeGeneralWidget();
}

SettingWidgetPrivate::~SettingWidgetPrivate()
{
}

void SettingWidgetPrivate::initializeSettingWidget()
{
    //    qDebug() << __FUNCTION__;
    int width(264);
    int height(248 - 72);
    if (NULL == m_GeneralBtn) {
        m_GeneralBtn = new BmpButton(m_Parent);
        m_GeneralBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnNormal"));
        m_GeneralBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnNormal"));
        m_GeneralBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnPress"));
        m_GeneralBtn->setStatus(BmpButton::B_Check);
        g_Widget->geometryFit(0, 72, width, height, m_GeneralBtn);
        m_GeneralBtn->setVisible(true);
    }
    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    if (NULL == m_GeneralText) {
        m_GeneralText = new TextWidget(m_GeneralBtn);
        m_GeneralText->setText(SourceString::General);
        m_GeneralText->setFontPointSize(fontPointSize);
        m_GeneralText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        g_Widget->geometryFit(123, 0, width - 123, height, m_GeneralText);
        m_GeneralText->setVisible(true);
    }
    if (NULL == m_LanguageBtn) {
        m_LanguageBtn = new BmpButton(m_Parent);
        m_LanguageBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnNormal"));
        m_LanguageBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnNormal"));
        m_LanguageBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnPress"));
        g_Widget->geometryFit(0, 262, width, height, m_LanguageBtn);
        m_LanguageBtn->setVisible(true);
    }
    if (NULL == m_LanguageText) {
        m_LanguageText = new TextWidget(m_LanguageBtn);
        m_LanguageText->setText(SourceString::Language);
        m_LanguageText->setFontPointSize(fontPointSize);
        m_LanguageText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        g_Widget->geometryFit(123, 0, width - 123, height, m_LanguageText);
        m_LanguageText->setVisible(true);
    }
    //    if (NULL == m_EffectBtn) {
    //        m_EffectBtn = new BmpButton(m_Parent);
    //        m_EffectBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnNormal"));
    //        m_EffectBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnNormal"));
    //        m_EffectBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnPress"));
    //        g_Widget->geometryFit(0, 352, width, height, m_EffectBtn);
    //        m_EffectBtn->setVisible(true);
    //    }
    //    if (NULL == m_EffectText) {
    //        m_EffectText = new TextWidget(m_EffectBtn);
    //        m_EffectText->setText(SourceString::Effect);
    //        m_EffectText->setFontPointSize(fontPointSize);
    //        m_EffectText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    //        g_Widget->geometryFit(123, 0, width - 123, height, m_EffectText);
    //        m_EffectText->setVisible(true);
    //    }
    //    if (NULL == m_FieldBtn) {
    //        m_FieldBtn = new BmpButton(m_Parent);
    //        m_FieldBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
    //        m_FieldBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
    //        m_FieldBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnPress"));
    //        g_Widget->geometryFit(0, 493, width, height, m_FieldBtn);
    //        m_FieldBtn->setVisible(true);
    //    }
    //    if (NULL == m_FieldText) {
    //        m_FieldText = new TextWidget(m_FieldBtn);
    //        m_FieldText->setText(SourceString::Field);
    //        m_FieldText->setFontPointSize(fontPointSize);
    //        m_FieldText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    //        g_Widget->geometryFit(123, 0, width - 123, height, m_FieldText);
    //        m_FieldText->setVisible(true);
    //    }
    //    g_Widget->geometryFit(0, 0, 264, g_Widget->baseWindowHeight(), this);
    //    g_Widget->geometryFit(0, 73, 264, 248 - 73, m_Private->m_MusicBtn);
    //    int width(150);
    //    int height(248 - 73);
    //    g_Widget->geometryFit(128 + (196 - 128 - width) * 0.5, 0, width, height, m_Private->m_MusicText);
    //    g_Widget->geometryFit(0, 262, 264, 437 - 262, m_Private->m_ImageBtn);
    //    g_Widget->geometryFit(128 + (196 - 128 - width) * 0.5, 0, width, height, m_Private->m_ImageText);
    //    g_Widget->geometryFit(0, 451, 264, 626 - 451, m_Private->m_VideoBtn);
    //    g_Widget->geometryFit(128 + (196 - 128 - width) * 0.5, 0, width, height, m_Private->m_VideoText);
    if (NULL == m_VersionBtn) {
        m_VersionBtn = new BmpButton(m_Parent);
        m_VersionBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
        m_VersionBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
        m_VersionBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnPress"));
        g_Widget->geometryFit(0, 451, width, height, m_VersionBtn);
        m_VersionBtn->setVisible(true);
    }
    if (NULL == m_VersionText) {
        m_VersionText = new TextWidget(m_VersionBtn);
        m_VersionText->setText(SourceString::Version);
        m_VersionText->setFontPointSize(fontPointSize);
        m_VersionText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        g_Widget->geometryFit(123, 0, width - 123, height, m_VersionText);
        m_VersionText->setVisible(true);
    }
}

void SettingWidgetPrivate::initializeGeneralWidget()
{
    qDebug() << __FUNCTION__;
    if (NULL == m_GeneralWidget) {
        m_GeneralWidget = new GeneralWidget(m_Parent);
    }
}

void SettingWidgetPrivate::initializeLanguageWidget()
{
    qDebug() << __FUNCTION__;
    if (NULL == m_LanguageWidget) {
        m_LanguageWidget = new LanguageWidget(m_Parent);
    }
}

void SettingWidgetPrivate::initializeVersionWidget()
{
    if (NULL == m_VersionWidget) {
        m_VersionWidget = new VersionWidget(m_Parent);
    }
}

//void SettingWidgetPrivate::initializeEffectWidget()
//{
//    qDebug() << __FUNCTION__;
//    if (NULL == m_EffectWidget) {
//        m_EffectWidget = new EffectWidget(m_Parent);
//    }
//}

//void SettingWidgetPrivate::initializeFieldWidget()
//{
//    qDebug() << __FUNCTION__;
//    if (NULL == m_FieldWidget) {
//        m_FieldWidget = new FieldWidget(m_Parent);
//    }
//}

void SettingWidgetPrivate::connectAllSlots()
{
    qDebug() << "SettingWidgetPrivate::connectAllSlots";
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    if (NULL != m_GeneralBtn) {
        QObject::connect(m_GeneralBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,     SLOT(onBmpButtonRelease()),
                         type);
    }
    if (NULL != m_LanguageBtn) {
        QObject::connect(m_LanguageBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,      SLOT(onBmpButtonRelease()),
                         type);
    }
    //    if (NULL != m_EffectBtn) {
    //        QObject::connect(m_EffectBtn, SIGNAL(bmpButtonRelease()),
    //                         m_Parent,    SLOT(onBmpButtonRelease()),
    //                         type);
    //    }
    //    if (NULL != m_FieldBtn) {
    //        QObject::connect(m_FieldBtn, SIGNAL(bmpButtonRelease()),
    //                         m_Parent,   SLOT(onBmpButtonRelease()),
    //                         type);
    //    }
    if (NULL != m_VersionBtn) {
        QObject::connect(m_VersionBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,     SLOT(onBmpButtonRelease()),
                         type);
    }
}

