#include "CarplayLinkWidget.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "CarplayShortCutWidget/CarplayShortCutWidget.h"
#include "Setting.h"
#include "UserInterfaceUtility.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDomElement>
#include <QApplication>
namespace SourceString {
static const QString No_Carplay_Device = QString(QObject::tr("No Carplay Device..."));
static const QString Fail_Carplay_Device = QString(QObject::tr("Conneting Carplay Fail..."));
static const QString Conneting_Carplay_Device = QString(QObject::tr("Conneting Carplay Device..."));
static const QString Remove_Carplay_Device = QString(QObject::tr("Remove Carplay Device..."));
}

class CarplayLinkWidgetPrivate
{
    Q_DISABLE_COPY(CarplayLinkWidgetPrivate)
public:
    explicit CarplayLinkWidgetPrivate(CarplayLinkWidget* parent);
    ~CarplayLinkWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    void onCarplayLinkStatus(const Link_STATUS status);
    void touchBeginEventHandler(QEvent* event);
    void touchUpdateEventHandler(QEvent* event);
    void touchEndEventHandler(QEvent* event);
    QString translateTouchEvent(const QList<TouchEvent> &list);
    CarplayShortCutWidget* m_CarplayShortCutWidget = NULL;
    MessageBox* m_DeviceMessageBox = NULL;
    QPoint m_Src = QPoint(0, 0);
    QPoint m_Dest = QPoint(0, 0);
    bool onPhone = FALSE;
private:
    CarplayLinkWidget* m_Parent = NULL;
};

CarplayLinkWidget::CarplayLinkWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new CarplayLinkWidgetPrivate(this))
{
}

CarplayLinkWidget::~CarplayLinkWidget()
{
}

void CarplayLinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void CarplayLinkWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
}

void CarplayLinkWidget::mousePressEvent(QMouseEvent *event)
{
    qWarning() << __FUNCTION__ << event->pos() << qgetenv("QWS_ARK_MT_DEVICE").isEmpty();
    if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointPressed;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //        qWarning() << __FUNCTION__ << event->pos() << qgetenv("QWS_ARK_MT_DEVICE").isEmpty();
    if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointReleased;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::mouseMoveEvent(QMouseEvent *event)
{
    //    qWarning() << __FUNCTION__ << event->pos() << qgetenv("QWS_ARK_MT_DEVICE").isEmpty();
    if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointMoved;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::LinkMessageWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            if (m_Private->m_DeviceMessageBox != ptr->m_Data->value<QWidget*>()) {
                m_Private->m_DeviceMessageBox->setVisible(false);
            }
        }
        break;
    }
    default: {
        break;
    }
    }
}

void CarplayLinkWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    g_Setting->setDisplayScreen(DST_On);
}

bool CarplayLinkWidget::event(QEvent *event)
{
    bool ret(true);
    switch (event->type()) {
    case QEvent::TouchBegin:
        m_Private->touchBeginEventHandler(event);
        ret = true;
        break;
    case QEvent::TouchUpdate: {
        m_Private->touchUpdateEventHandler(event);
        return true;
        break;
    }
    case QEvent::TouchEnd: {
        m_Private->touchEndEventHandler(event);
        ret = true;
        break;
    }
    default : {
        ret = QWidget::event(event);
        break;
    }
    }
    return ret;
}

void CarplayLinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Carplay: {
        if (WidgetStatus::RequestShow == status) {
            g_Link->requestLinkStatus(CARPLAY, LINK_STARTING);
        } else if (WidgetStatus::Show == status) {
            raise();
            if (!qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
                setAttribute(Qt::WA_AcceptTouchEvents, true);
            }
            setVisible(true);
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            m_Private->m_DeviceMessageBox->setVisible(false);
            setVisible(false);
        }
        break;
    }
    }
}

void CarplayLinkWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qWarning() << "CarplayLinkWidget::onLinkStatusChange" << type << status;
    switch (type) {
    case CARPLAY: {
        m_Private->onCarplayLinkStatus(status);
        break;
    }
    default: {
        break;
    }
    }
}
//传入一个点，发送到ｃａｒｐｌａｙ界面
void CarplayLinkWidget::sendPoint(QPoint &pos){
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &event0);

    QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &event1);
}

void CarplayLinkWidget::onMCUDataRecv(int type, int data)
{
    qWarning() << "CarplayLinkWidget::onMCUDataRecv" << data;
    if(type == 1 && m_Private->onPhone){
        if( data == 1){ //接听
            QPoint pos(100,100);
            sendPoint(pos);
             qWarning() << "--------------------jieting";
        }else if(data == 2){    //挂断
            QPoint pos(200,200);
            sendPoint(pos);
             qWarning() << "--------------------guaduan";
        }else if(data == 3){

        }
    }
}

CarplayLinkWidgetPrivate::CarplayLinkWidgetPrivate(CarplayLinkWidget* parent)
    : m_Parent(parent)

{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

CarplayLinkWidgetPrivate::~CarplayLinkWidgetPrivate()
{
}

void CarplayLinkWidgetPrivate::initialize()
{
    m_CarplayShortCutWidget = new CarplayShortCutWidget(m_Parent);
    m_DeviceMessageBox = new MessageBox(m_Parent);
    m_DeviceMessageBox->hide();
    m_DeviceMessageBox->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
}

void CarplayLinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void CarplayLinkWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
    connectSignalAndSlotByNamesake(g_Port, m_Parent);
}

void CarplayLinkWidgetPrivate::onCarplayLinkStatus(const int status)   //查看触发事件，确认给MCU发信息的时间
{
    qWarning()<< "onCarplayLinkStatus" << status;
    switch (status) {
    case LINK_STARTING: {      //连接中
//         g_Port->setMemStatus(Port::RGB);
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MessageBoxWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setText(SourceString::Conneting_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event2);
        break;
    }
    case LINK_DISCONNECTED: {   //退出链接
//         g_Port->setMemStatus(Port::RGB);
//        g_Port->setStatus(Port::CarPlayDisConnected);
//        char data = 0x1;
//        g_Port->responseMCU(Port::C_Close, &data, 1);

        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(true);
        m_DeviceMessageBox->setText(SourceString::No_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        break;
    }
        //新增ｆａｉｌ状态
    case LINK_FAIL:{
        g_Port->setStatus(Port::CarPlayDisConnected);

        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(true);
        m_DeviceMessageBox->setText(SourceString::Fail_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        break;
        break;
    }
    case LINK_EXITING: {       //Home键  ,这里可能要切换低阻
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        break;
    }
    case LINK_REMOVED:{
//    case LINK_EXITED: {         //退出carplay

         g_Port->setStatus(Port::CarPlayDisConnected);
        char data = Port::CarPlayDisConnected;
        g_Port->responseMCU(Port::C_SoundStatus, &data, 1);

        if ((m_Parent->isVisible())
                || (m_DeviceMessageBox->isVisible())) {
            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
            EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
            g_EventEngine->sendCustomEvent(event2);
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            m_DeviceMessageBox->setAutoHide(true);
            m_DeviceMessageBox->setText(SourceString::Remove_Carplay_Device);
//            m_DeviceMessageBox->setFontPointSize(22 * g_Widget->widthScalabilityFactor());
            g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
            //            EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
            //            g_EventEngine->sendCustomEvent(event2);
            //            QVariant* variant = new QVariant();
            //            variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
            //            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
            //            g_EventEngine->sendCustomEvent(event);
            //            m_DeviceMessageBox->setAutoHide(true);
            //            m_DeviceMessageBox->setText(SourceString::Remove_Carplay_Device);
            //            g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
            //            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::Show);
        }
        break;
    }
    case LINK_SUCCESS: {    //链接成功
        g_Port->setStatus(Port::CarPlayConnected);

         char data = Port::CarPlayConnected;
        g_Port->responseMCU(Port::C_SoundStatus, &data, 1);

        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::Show);
        m_Parent->startTimer(250);
        break;
    }
    case LINK_CALL_PHONE: {    //来电
         char data = 0x01;
        g_Port->responseMCU(Port::C_BTCall, &data, 1);
        onPhone = TRUE;
        break;
    }
    case LINK_CALL_PHONE_EXITED: {    //去电
        char data = 0x02;
        if(onPhone)
            g_Port->responseMCU(Port::C_BTCall, &data, 1);
        onPhone = FALSE;
        break;
    }
    default: {
        break;
    }
    }
}

void CarplayLinkWidgetPrivate::touchBeginEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos().toPoint();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
        }
    }
}

void CarplayLinkWidgetPrivate::touchUpdateEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(CARPLAY, TouchUpdate, touchPointXml);
        }
    }
}

void CarplayLinkWidgetPrivate::touchEndEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(CARPLAY, TouchEnd, touchPointXml);
        }
    }
}

QString CarplayLinkWidgetPrivate::translateTouchEvent(const QList<TouchEvent> &list)
{
    QString touchPointXml;
    touchPointXml.clear();
    QDomDocument domDocument;
    domDocument.appendChild(domDocument.createElement(QString("TouchEvent")));
    QDomElement root = domDocument.firstChildElement(QString("TouchEvent"));
    QDomElement touchPoint = domDocument.createElement(QString("TouchPoint"));
    root.appendChild(touchPoint);
    QDomElement positionState;
    QDomElement positionX;
    QDomElement positionY;
    QDomElement touchPointIndex;
    touchPointXml.clear();
    for (int i = 0; i < list.size(); ++i) {
        positionState = domDocument.createElement(QString("State"));
        positionState.appendChild(domDocument.createTextNode(QString::number(list.at(i).state)));
        touchPointIndex = domDocument.createElement(QString("Index:") + QString::number(i));
        touchPointIndex.appendChild(positionState);
        positionX = domDocument.createElement(QString("X"));
        positionX.appendChild(domDocument.createTextNode(QString::number(list.at(i).x)));
        touchPointIndex.appendChild(positionX);
        positionY = domDocument.createElement(QString("Y"));
        positionY.appendChild(domDocument.createTextNode(QString::number(list.at(i).y)));
        touchPointIndex.appendChild(positionY);
        touchPoint.appendChild(touchPointIndex);
    }
    touchPointXml = domDocument.toString();
    return touchPointXml;
}
