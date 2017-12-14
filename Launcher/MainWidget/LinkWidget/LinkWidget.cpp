#include "LinkWidget.h"
//#include "MirrorLinkWidget/MirrorLinkWidget.h"
#include "CarplayLinkWidget/CarplayLinkWidget.h"
#include "CarlifeLinkWidget/CarlifeLinkWidget.h"
#include "AutoConnect.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "MainWidget/MainWidget.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "TextWidget.h"
#include "EventEngine.h"
#include <QVariant>
#include "FaderWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
static int a = 0;
static int x1,x2,y_1,y_2;
namespace SourceString {
static const QString Select_Connect_Mode = QString(QObject::tr("Select connect mode!"));
static const QString AndroidMirror = QString(QObject::tr("Carlife"));
static const QString AndroidMirrorTip = QString(QObject::tr("1:Enable developer USB debugging options!\n"
                                                            "2:Connect to bluetooth devices!\n"
                                                            "3:Connect andriod usb cable!\n"
                                                            "4:Press Carlife icon!"));
static const QString AppleCarPlay = QString(QObject::tr("Carplay"));
static const QString AppleCarPlayTip = QString(QObject::tr("1:Connect iphone usb cable!\n"
                                                           "2:Press Carplay icon!\n"));

static const QString version = QString(QObject::tr("MAN:2017-12-14\n"
                                                    "BSP:2017-12-14\n"
                                                    "APP:2017-12-14\n"));
}

class LinkWidgetPrivate
{
    Q_DISABLE_COPY(LinkWidgetPrivate)
public:
    explicit LinkWidgetPrivate(LinkWidget *parent);
    ~LinkWidgetPrivate();
    void initializeLinkWidget();
//    void initializeMirrowWidget();
    void initializeCarplayWidget();
    void initializeCarlifeWidget();
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
    BmpButton* m_BackBtn = NULL;
     MessageBox* m_DeviceMessageBox = NULL;
//    MirrorLinkWidget* m_MirrorLinkWidget = NULL;
    CarplayLinkWidget* m_CarplayLinkWidget = NULL;
    CarlifeLinkWidget * m_CarlifeLinkWidget = NULL;
    QTimer *m_Timer = NULL;
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
//void LinkWidget::mouseDoubleClickEvent(QMouseEvent *event){
//    qWarning() << a;
//    if(a++ % 2)
//        m_Private->m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkWidgetBackground2"));
//    else
//        m_Private->m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/test"));
//    update();
//}

void LinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void LinkWidget::showEvent(QShowEvent *event)
{
    qWarning() << "LinkWidget::showEvent";
    if (NULL != m_Private) {
        m_Private->connectAllSlots();
        m_Private->receiveAllCustomEvent();
    }
}

//void LinkWidget::mousePressEvent(QMouseEvent *event){
//    x1 = event->x();
//    y_1 = event->y();
//    qWarning() << x1;
//    m_Private->m_Timer->start();
//        QWidget::mousePressEvent(event);
//}

//void LinkWidget::mouseReleaseEvent(QMouseEvent *event){
//    x2 = event->x();
//    y_2 = event->y();
//    qWarning() << x2;
//    if((x2 - x1 > 400 )|| (x1 - x2 > 400)){
//        a = 1-a;
//        qWarning() << a;
//        if(a)
//            m_Private->m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkWidgetBackground2"));
//        else
//            m_Private->m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/test"));
//    }
//    if((y_2 - y_1 > 100) || (y_1 - y_2 > 100)){

//        QVariant* variant = new QVariant();
//        variant->setValue(static_cast<QWidget*>(m_Private->m_DeviceMessageBox));
//        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
//        g_EventEngine->sendCustomEvent(event);
//        m_Private->m_DeviceMessageBox->setAutoHide(true);
//        m_Private->m_DeviceMessageBox->setText(tr("2017-12-14"));
//        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_DeviceMessageBox);
//        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
//        g_EventEngine->sendCustomEvent(event2);
//    }
//    m_Private->m_Timer->stop();
//    QWidget::mouseReleaseEvent(event);
//}

void LinkWidget::onTimeout(){
    m_Private->m_BackBtn->setVisible(false);
    QVariant* variant = new QVariant();
    variant->setValue(static_cast<QWidget*>(m_Private->m_DeviceMessageBox));
    EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
    g_EventEngine->sendCustomEvent(event);

    m_Private->m_DeviceMessageBox->setAutoHide(true);
    m_Private->m_DeviceMessageBox->setText(tr("2017-12-14"));
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_DeviceMessageBox);
    EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
    g_EventEngine->sendCustomEvent(event2);
}

void LinkWidget::onMessageChange(){
        m_Private->m_BackBtn->setVisible(true);
    raise();

}
void LinkWidget::customEvent(QEvent *event)
{
    qWarning() << "LinkWidget::customEvent";
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
//    m_Private->initializeMirrowWidget();
    m_Private->initializeCarplayWidget();
    m_Private->initializeCarlifeWidget();
}
//void LinkWidget::paintEvent(QPaintEvent *event){
//    QPainter painter(this);
//    int currentAlpha = 10;
//    QColor color = Qt::white;
//    color.setAlpha(currentAlpha);

//    painter.fillRect(rect(), color);
//}
//void LinkWidget::mouseReleaseEvent(QMouseEvent *e){
//    qWarning() << e->x() << e->y();
//    if(e->x() >= 400)
//        emit clickCarplay();
//    else
//        emit clickCarlife();
//}
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
            lower();
            setVisible(true);
        }
        break;
    }
    case Widget::T_Carplay:
    case Widget::T_Carlife: {
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
    qWarning() << "onToolButtonRelease";
    if (sender() == m_Private->m_MirrorBtn) {
//        m_Private->initializeMirrowWidget();
        g_Widget->setWidgetType(Widget::T_Carlife, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_CarplayBtn) {
        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::RequestShow);
    }else if (sender() == m_Private->m_BackBtn) {
        g_Widget->setWidgetType(Widget::T_Back, WidgetStatus::RequestShow);
    }
}

LinkWidgetPrivate::LinkWidgetPrivate(LinkWidget *parent)
    : m_Parent(parent)
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    initializeCarplayWidget();
    initializeCarlifeWidget();
}

LinkWidgetPrivate::~LinkWidgetPrivate()
{
}

void LinkWidgetPrivate::initializeLinkWidget()
{
    if (NULL == m_Background) {
        m_Background = new BmpWidget(m_Parent);
        m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkWidgetBackground2"));
//        m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/test"));
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Background);
        m_Background->setVisible(true);
    }
    if (NULL == m_TitleText) {
        m_TitleText = new TextWidget(m_Parent);
        m_TitleText->setFontPointSize(28 * g_Widget->widthScalabilityFactor());
        m_TitleText->setText(SourceString::Select_Connect_Mode);
        g_Widget->geometryFit(0, 78, g_Widget->baseWindowWidth(), 64, m_TitleText);
        m_TitleText->setVisible(true);
    }
    int width(179);
    int height(197);
    if (NULL == m_MirrorBtn) {
        m_MirrorBtn = new BmpButton(m_Parent);
        m_MirrorBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarlifeBtnNormal"));
        m_MirrorBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarlifeBtnNormal"));
        g_Widget->geometryFit((g_Widget->baseWindowWidth() * 0.5 - width) * 0.5 + 50, (g_Widget->baseWindowHeight() - height) * 0.4, width, height, m_MirrorBtn);
        m_MirrorBtn->setVisible(true);
    }
    if (NULL == m_MirrorBtnText) {
        m_MirrorBtnText = new TextWidget(m_Parent);
        m_MirrorBtnText->setText(SourceString::AndroidMirror);
        m_MirrorBtnText->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit((g_Widget->baseWindowWidth() * 0.5 - width) * 0.5 + 50, (g_Widget->baseWindowHeight() - height) * 0.4 + height, width, 29, m_MirrorBtnText);
        m_MirrorBtnText->setVisible(true);
    }
    if (NULL == m_MirrorTipText) {
        m_MirrorTipText = new TextWidget(m_Parent);
        m_MirrorTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        m_MirrorTipText->setText(SourceString::AndroidMirrorTip);
        m_MirrorTipText->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit(260, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_MirrorTipText);
        m_MirrorTipText->setVisible(true);
    }
    if (NULL == m_CarplayBtn) {
        m_CarplayBtn = new BmpButton(m_Parent);
        m_CarplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
        m_CarplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
        g_Widget->geometryFit(g_Widget->baseWindowWidth() * 0.5 + (g_Widget->baseWindowWidth() * 0.5 - width) * 0.5 - 50, (g_Widget->baseWindowHeight() - height) * 0.4, width, height, m_CarplayBtn);
        m_CarplayBtn->setVisible(true);
    }
    if (NULL == m_CarplayBtnText) {
        m_CarplayBtnText = new TextWidget(m_Parent);
        m_CarplayBtnText->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
        m_CarplayBtnText->setText(SourceString::AppleCarPlay);
        g_Widget->geometryFit(g_Widget->baseWindowWidth() * 0.5 + (g_Widget->baseWindowWidth() * 0.5 - width) * 0.5 - 50, (g_Widget->baseWindowHeight() - height) * 0.4 + height, width, 29, m_CarplayBtnText);
        m_CarplayBtnText->setVisible(true);
    }
    if (NULL == m_CarplayTipText) {
        m_CarplayTipText = new TextWidget(m_Parent);
        m_CarplayTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
        m_CarplayTipText->setText(SourceString::AppleCarPlayTip);
        m_CarplayTipText->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
        g_Widget->geometryFit(678 + 120, (g_Widget->baseWindowHeight() - height) * 0.5 + height - 20, 572, 120, m_CarplayTipText);
        m_CarplayTipText->setVisible(true);
    }
    if(NULL == m_DeviceMessageBox){
        m_DeviceMessageBox = new MessageBox(m_Parent);
        m_DeviceMessageBox->hide();
        m_DeviceMessageBox->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
    }
//    if(NULL == m_Timer){
//        m_Timer = new QTimer(m_Parent);
//        m_Timer->setSingleShot(true);
//        m_Timer->setInterval(1000);
//    }
    if (NULL == m_BackBtn) {
        m_BackBtn = new BmpButton(m_Parent);
        m_BackBtn->setNormalBmpPath(QString(":/Images/Resources/Images/go_back"));
        m_BackBtn->setPressBmpPath(QString(":/Images/Resources/Images/go_back"));
        g_Widget->geometryFit(1280 - 136, 720- 136, 96, 96, m_BackBtn);
        m_BackBtn->setVisible(true);
    }
}

//void LinkWidgetPrivate::initializeMirrowWidget()
//{
//    if (NULL == m_MirrorLinkWidget) {
//        m_MirrorLinkWidget = new MirrorLinkWidget(m_Parent);
//    }
//}

void LinkWidgetPrivate::initializeCarplayWidget()
{
    if (NULL == m_CarplayLinkWidget) {
        m_CarplayLinkWidget = new CarplayLinkWidget(m_Parent);
    }
}

void LinkWidgetPrivate::initializeCarlifeWidget()
{
    if (NULL == m_CarlifeLinkWidget) {
        m_CarlifeLinkWidget = new CarlifeLinkWidget(m_Parent);
    }
}
void LinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void LinkWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    qWarning() << "LinkWidgetPrivate::connectAllSlots" << m_MirrorBtn << m_CarplayBtn;
    QObject::connect(m_Parent, SIGNAL(clickCarplay()),
                     m_CarplayBtn,SIGNAL(bmpButtonRelease()),
                     type);
    QObject::connect(m_Parent, SIGNAL(clickCarlife()),
                     m_MirrorBtn,SIGNAL(bmpButtonRelease()),
                     type);
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
//    if(NULL != m_Timer){
//        QObject::connect(m_Timer,  SIGNAL(timeout()),
//                         m_Parent, SLOT(onTimeout()),
//                         type);
//    }
    if(NULL != m_BackBtn){
        QObject::connect(m_BackBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent,     SLOT(onToolButtonRelease()),
                         type);
    }
//    QObject::connect(m_DeviceMessageBox, SIGNAL(messageShowTimeout()),
//                     m_Parent,  SLOT(onMessageChange()),
//                     type);
}
