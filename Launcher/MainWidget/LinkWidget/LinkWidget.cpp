#include "LinkWidget.h"
#include "MirrorLinkWidget/MirrorLinkWidget.h"
#include "CarplayLinkWidget/CarplayLinkWidget.h"
#include "AutoConnect.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "MainWidget/MainWidget.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "TextWidget.h"
#include "EventEngine.h"
#include <QVariant>

namespace SourceString {
static const QString Select_Connect_Mode = QString(QObject::tr("Select connect mode!"));
static const QString AndroidMirror = QString(QObject::tr("Android Mirror"));
static const QString AndroidMirrorTip = QString(QObject::tr("1:Enable developer USB debugging options!\n"
                                                            "2:Connect to bluetooth devices!\n"
                                                            "3:Connect usb cable!\n"
                                                            "4:Press Mirror icon!"));
static const QString AppleCarPlay = QString(QObject::tr("Apple CarPlay"));
static const QString AppleCarPlayTip = QString(QObject::tr(" \n"
                                                           "1:Connect usb cable!\n"
                                                           "2:Press Carplay icon!\n"
                                                           " "));
}

class LinkWidgetPrivate
{
    Q_DISABLE_COPY(LinkWidgetPrivate)
public:
    explicit LinkWidgetPrivate(LinkWidget *parent);
    ~LinkWidgetPrivate();
    void initializeLinkWidget();
    void initializeMirrowWidget();
    void initializeCarplayWidget();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
    TextWidget* m_TitleText = NULL;
    BmpButton* m_MirrorBtn = NULL;
    TextWidget* m_MirrorBtnText = NULL;
    TextWidget* m_MirrorTipText = NULL;
    BmpButton* m_CarplayBtn = NULL;
    TextWidget* m_CarplayBtnText = NULL;
    TextWidget* m_CarplayTipText = NULL;
    MirrorLinkWidget* m_MirrorLinkWidget = NULL;
    CarplayLinkWidget* m_CarplayLinkWidget = NULL;
private:
    LinkWidget* m_Parent = NULL;
};

LinkWidget::LinkWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new LinkWidgetPrivate(this))
{
}

LinkWidget::~LinkWidget()
{
}

void LinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void LinkWidget::showEvent(QShowEvent *event)
{
    qDebug() << "LinkWidget::showEvent";
    if (NULL != m_Private) {
        m_Private->connectAllSlots();
        m_Private->receiveAllCustomEvent();
    }
}

void LinkWidget::customEvent(QEvent *event)
{
    qDebug() << "LinkWidget::customEvent";
    switch (event->type()) {
    case CustomEventType::LinkMessageWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void LinkWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    m_Private->initializeMirrowWidget();
    m_Private->initializeCarplayWidget();
}

void LinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qWarning() << "LinkWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
//            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            char data = 1;
            g_Port->responseMCU(Port::C_HideCarplay, &data, 1);
            g_Port->setMemStatus(Port::IO);
        }
        break;
    }
    case Widget::T_Link: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->initializeLinkWidget();
//            if ((NULL == m_Private->m_MirrorLinkWidget)
//                    || (NULL == m_Private->m_CarplayLinkWidget)) {
//                startTimer(150);
//            }
            lower();
            setVisible(true);
        }
        break;
    }
    case Widget::T_Mirror:
    case Widget::T_Carplay: {
        if (WidgetStatus::Show == status) {
            lower();
            setVisible(true);
        }
        break;
    }
    default : {
        setVisible(false);
        break;
    }
    }
}

void LinkWidget::onToolButtonRelease()
{
    qDebug() << "onToolButtonRelease";
    if (sender() == m_Private->m_MirrorBtn) {
        m_Private->initializeMirrowWidget();
        g_Widget->setWidgetType(Widget::T_Mirror, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_CarplayBtn) {

        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::RequestShow);
    }
}

LinkWidgetPrivate::LinkWidgetPrivate(LinkWidget *parent)
    : m_Parent(parent)
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    initializeCarplayWidget();
}

LinkWidgetPrivate::~LinkWidgetPrivate()
{
}

void LinkWidgetPrivate::initializeLinkWidget()
{
    if (NULL == m_Background) {
        m_Background = new BmpWidget(m_Parent);
        m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkWidgetBackground"));
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Background);
        m_Background->setVisible(true);
    }
    if (NULL == m_TitleText) {
        m_TitleText = new TextWidget(m_Parent);
        m_TitleText->setFontPointSize(26 * g_Widget->widthScalabilityFactor());
        m_TitleText->setText(SourceString::Select_Connect_Mode);
        g_Widget->geometryFit(0, 78, g_Widget->baseWindowWidth(), 64, m_TitleText);
        m_TitleText->setVisible(true);
    }
    int width(179);
    int height(197);
    if (NULL == m_MirrorBtn) {
        m_MirrorBtn = new BmpButton(m_Parent);
        m_MirrorBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorBtnNormal"));
        m_MirrorBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorBtnNormal"));
        g_Widget->geometryFit((g_Widget->baseWindowWidth() * 0.5 - width) * 0.5, (g_Widget->baseWindowHeight() - height) * 0.4, width, height, m_MirrorBtn);
        m_MirrorBtn->setVisible(true);
    }
    if (NULL == m_MirrorBtnText) {
        m_MirrorBtnText = new TextWidget(m_Parent);
        m_MirrorBtnText->setText(SourceString::AndroidMirror);
        m_MirrorBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit((g_Widget->baseWindowWidth() * 0.5 - width) * 0.5, (g_Widget->baseWindowHeight() - height) * 0.4 + height, width, 29, m_MirrorBtnText);
        m_MirrorBtnText->setVisible(true);
    }
    if (NULL == m_MirrorTipText) {
        m_MirrorTipText = new TextWidget(m_Parent);
        m_MirrorTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        m_MirrorTipText->setText(SourceString::AndroidMirrorTip);
        m_MirrorTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit(30, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_MirrorTipText);
        m_MirrorTipText->setVisible(true);
    }
    if (NULL == m_CarplayBtn) {
        m_CarplayBtn = new BmpButton(m_Parent);
        m_CarplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
        m_CarplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
        g_Widget->geometryFit(g_Widget->baseWindowWidth() * 0.5 + (g_Widget->baseWindowWidth() * 0.5 - width) * 0.5, (g_Widget->baseWindowHeight() - height) * 0.4, width, height, m_CarplayBtn);
        m_CarplayBtn->setVisible(true);
    }
    if (NULL == m_CarplayBtnText) {
        m_CarplayBtnText = new TextWidget(m_Parent);
        m_CarplayBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
        m_CarplayBtnText->setText(SourceString::AppleCarPlay);
        g_Widget->geometryFit(g_Widget->baseWindowWidth() * 0.5 + (g_Widget->baseWindowWidth() * 0.5 - width) * 0.5, (g_Widget->baseWindowHeight() - height) * 0.4 + height, width, 29, m_CarplayBtnText);
        m_CarplayBtnText->setVisible(true);
    }
    if (NULL == m_CarplayTipText) {
        m_CarplayTipText = new TextWidget(m_Parent);
        m_CarplayTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        m_CarplayTipText->setText(SourceString::AppleCarPlayTip);
        m_CarplayTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit(678, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_CarplayTipText);
        m_CarplayTipText->setVisible(true);
    }
}

void LinkWidgetPrivate::initializeMirrowWidget()
{
    if (NULL == m_MirrorLinkWidget) {
        m_MirrorLinkWidget = new MirrorLinkWidget(m_Parent);
    }
}

void LinkWidgetPrivate::initializeCarplayWidget()
{
    if (NULL == m_CarplayLinkWidget) {
        m_CarplayLinkWidget = new CarplayLinkWidget(m_Parent);
    }
}

void LinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void LinkWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    qDebug() << "LinkWidgetPrivate::connectAllSlots" << m_MirrorBtn << m_CarplayBtn;
    if (NULL != m_MirrorBtn) {
        QObject::connect(m_MirrorBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,    SLOT(onToolButtonRelease()),
                         type);
    }
    if (NULL != m_CarplayBtn) {
        QObject::connect(m_CarplayBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,     SLOT(onToolButtonRelease()),
                         type);
    }
}
