#include "LanguageWidget.h"
#include "AutoConnect.h"
#include "BmpButton.h"
#include "TextWidget.h"
#include "Setting.h"
#include "BmpWidget.h"
#include "ArkApplication.h"
#include "SettingPersistent.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

namespace SourceString {
static const QString English = QString(QObject::tr("English"));
static const QString Chinese = QString(QObject::tr("Chinese"));
static const QString Japaness = QString(QObject::tr("Japaness"));
static const QString Korean = QString(QObject::tr("Korean"));
static const QString Spanish = QString(QObject::tr("Spanish"));
static const QString Portuguese = QString(QObject::tr("Portuguese"));
static const QString Russian = QString(QObject::tr("Russian"));
static const QString German = QString(QObject::tr("German"));
static const QString French = QString(QObject::tr("French"));
}

class LanguageWidgetPrivate
{
    Q_DISABLE_COPY(LanguageWidgetPrivate)
public:
    explicit LanguageWidgetPrivate(LanguageWidget* parent);
    ~LanguageWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
    BmpButton* m_EnglishBtn = NULL;
    TextWidget* m_EnglishText = NULL;
    BmpButton* m_ChineseBtn = NULL;
    TextWidget* m_ChineseText = NULL;
    BmpButton* m_JapanessBtn = NULL;
    TextWidget* m_JapanessText = NULL;
    BmpButton* m_KoreanBtn = NULL;
    TextWidget* m_KoreanText = NULL;
    BmpButton* m_SpanishBtn = NULL;
    TextWidget* m_SpanishText = NULL;
    BmpButton* m_PortugueseBtn = NULL;
    TextWidget* m_PortugueseText = NULL;
    BmpButton* m_RussianBtn = NULL;
    TextWidget* m_RussianText = NULL;
    BmpButton* m_GermanBtn = NULL;
    TextWidget* m_GermanText = NULL;
    BmpButton* m_FrenchBtn = NULL;
    TextWidget* m_FrenchText = NULL;
private:
    LanguageWidget* m_Parent = NULL;
};

LanguageWidget::LanguageWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new LanguageWidgetPrivate(this))
{
}

LanguageWidget::~LanguageWidget()
{
}

void LanguageWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void LanguageWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    g_Widget->geometryFit(0, 0, 1002, 552, m_Private->m_Background);
    int width(161);
    int height(108);
    g_Widget->geometryFit(129, 57, width, height, m_Private->m_EnglishBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_EnglishText);
    g_Widget->geometryFit(419, 57, width, height, m_Private->m_ChineseBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_ChineseText);
    g_Widget->geometryFit(709, 57, width, height, m_Private->m_JapanessBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_JapanessText);
    g_Widget->geometryFit(129, 222, width, height, m_Private->m_KoreanBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_KoreanText);
    g_Widget->geometryFit(419, 222, width, height, m_Private->m_SpanishBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_SpanishText);
    g_Widget->geometryFit(709, 222, width, height, m_Private->m_PortugueseBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_PortugueseText);
    g_Widget->geometryFit(129, 387, width, height, m_Private->m_RussianBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_RussianText);
    g_Widget->geometryFit(419, 387, width, height, m_Private->m_GermanBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_GermanText);
    g_Widget->geometryFit(709, 387, width, height, m_Private->m_FrenchBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FrenchText);
    QWidget::resizeEvent(event);
}

void LanguageWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void LanguageWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "LanguageWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_SettingLanguage: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_Background->setVisible(true);
            m_Private->m_EnglishBtn->setVisible(true);
            m_Private->m_EnglishText->setVisible(true);
            m_Private->m_ChineseBtn->setVisible(true);
            m_Private->m_ChineseText->setVisible(true);
            m_Private->m_JapanessBtn->setVisible(true);
            m_Private->m_JapanessText->setVisible(true);
            m_Private->m_KoreanBtn->setVisible(true);
            m_Private->m_KoreanText->setVisible(true);
            m_Private->m_SpanishBtn->setVisible(true);
            m_Private->m_SpanishText->setVisible(true);
            m_Private->m_PortugueseBtn->setVisible(true);
            m_Private->m_PortugueseText->setVisible(true);
            m_Private->m_RussianBtn->setVisible(true);
            m_Private->m_RussianText->setVisible(true);
            m_Private->m_GermanBtn->setVisible(true);
            m_Private->m_GermanText->setVisible(true);
            m_Private->m_FrenchBtn->setVisible(true);
            m_Private->m_FrenchText->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingGeneral:
    case Widget::T_SettingEffect:
    case Widget::T_SettingField:
    case Widget::T_SettingVersion: {
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

void LanguageWidget::onLanguageTranslateChange(const LanguageType language)
{
    m_Private->m_EnglishBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_ChineseBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_JapanessBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_KoreanBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_SpanishBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_PortugueseBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_RussianBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_GermanBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_FrenchBtn->setStatus(BmpButton::B_Normal);
    switch (language) {
    case LT_English: {
        m_Private->m_EnglishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Chinese: {
        m_Private->m_ChineseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Japaness: {
        m_Private->m_JapanessBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Korean: {
        m_Private->m_KoreanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Spanish: {
        m_Private->m_SpanishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Portuguese: {
        m_Private->m_PortugueseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Russian: {
        m_Private->m_RussianBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_German: {
        m_Private->m_GermanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_French: {
        m_Private->m_FrenchBtn->setStatus(BmpButton::B_Check);
        break;
    }
    default: {
        break;
    }
    }
}

void LanguageWidget::onToolButtonRelease()
{
    if (sender() == m_Private->m_EnglishBtn) {
        g_Setting->setLanguage(LT_English);
    } else if (sender() == m_Private->m_ChineseBtn) {
        g_Setting->setLanguage(LT_Chinese);
    } else if (sender() == m_Private->m_JapanessBtn) {
        g_Setting->setLanguage(LT_Japaness);
    } else if (sender() == m_Private->m_KoreanBtn) {
        g_Setting->setLanguage(LT_Korean);
    } else if (sender() == m_Private->m_SpanishBtn) {
        g_Setting->setLanguage(LT_Spanish);
    } else if (sender() == m_Private->m_PortugueseBtn) {
        g_Setting->setLanguage(LT_Portuguese);
    } else if (sender() == m_Private->m_RussianBtn) {
        g_Setting->setLanguage(LT_Russian);
    } else if (sender() == m_Private->m_GermanBtn) {
        g_Setting->setLanguage(LT_German);
    } else if (sender() == m_Private->m_FrenchBtn) {
        g_Setting->setLanguage(LT_French);
    }
}

LanguageWidgetPrivate::LanguageWidgetPrivate(LanguageWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

LanguageWidgetPrivate::~LanguageWidgetPrivate()
{
}

void LanguageWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageWidgetBackground"));
    m_EnglishBtn = new BmpButton(m_Parent);
    m_EnglishBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_EnglishBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_EnglishBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_EnglishText = new TextWidget(m_EnglishBtn);
    m_EnglishText->setText(SourceString::English);
    m_ChineseBtn = new BmpButton(m_Parent);
    m_ChineseBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ChineseBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ChineseBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ChineseText = new TextWidget(m_ChineseBtn);
    m_ChineseText->setText(SourceString::Chinese);
    m_JapanessBtn = new BmpButton(m_Parent);
    m_JapanessBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_JapanessBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_JapanessBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_JapanessText = new TextWidget(m_JapanessBtn);
    m_JapanessText->setText(SourceString::Japaness);
    m_KoreanBtn = new BmpButton(m_Parent);
    m_KoreanBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_KoreanBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_KoreanBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_KoreanText = new TextWidget(m_KoreanBtn);
    m_KoreanText->setText(SourceString::Korean);
    m_SpanishBtn = new BmpButton(m_Parent);
    m_SpanishBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_SpanishBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_SpanishBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_SpanishText = new TextWidget(m_SpanishBtn);
    m_SpanishText->setText(SourceString::Spanish);
    m_PortugueseBtn = new BmpButton(m_Parent);
    m_PortugueseBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_PortugueseBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_PortugueseBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_PortugueseText = new TextWidget(m_PortugueseBtn);
    m_PortugueseText->setText(SourceString::Portuguese);
    m_RussianBtn = new BmpButton(m_Parent);
    m_RussianBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_RussianBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_RussianBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_RussianText = new TextWidget(m_RussianBtn);
    m_RussianText->setText(SourceString::Russian);
    m_GermanBtn = new BmpButton(m_Parent);
    m_GermanBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_GermanBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_GermanBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_GermanText = new TextWidget(m_GermanBtn);
    m_GermanText->setText(SourceString::German);
    m_FrenchBtn = new BmpButton(m_Parent);
    m_FrenchBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FrenchBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FrenchBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FrenchText = new TextWidget(m_FrenchBtn);
    m_FrenchText->setText(SourceString::French);
    int language = SettingPersistent::getLanguage();
    switch (language) {
    case LT_English: {
        m_EnglishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Chinese: {
        m_ChineseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Japaness: {
        m_JapanessBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Korean: {
        m_KoreanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Spanish: {
        m_SpanishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Portuguese: {
        m_PortugueseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Russian: {
        m_RussianBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_German: {
        m_GermanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_French: {
        m_FrenchBtn->setStatus(BmpButton::B_Check);
        break;
    }
    default: {
        break;
    }
    }
}

void LanguageWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_EnglishBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ChineseBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_JapanessBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_KoreanBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_SpanishBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_PortugueseBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,        SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_RussianBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_GermanBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FrenchBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
}
