#include "MirrorLinkWidget.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "BT.h"
#include "Setting.h"
#include "MirrorShortCutWidget/MirrorShortCutWidget.h"
#include "MirrorToolWidget/MirrorToolWidget.h"
#include "MirrorMessageDialog/MirrorMessageDialog.h"
#include "UserInterfaceUtility.h"
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QTouchEvent>
#include <QDomElement>

//namespace SourceString {
//static const QString No_Mirror_Device = QString(QObject::tr("No Mirror Device..."));
//static const QString Conneting_Mirror_Device = QString(QObject::tr("Conneting Mirror Device..."));
//static const QString Remove_Mirror_Device = QString(QObject::tr("Remove Mirror Device..."));
//}

class MirrorLinkWidgetPrivate
{
    Q_DISABLE_COPY(MirrorLinkWidgetPrivate)
public:
    explicit MirrorLinkWidgetPrivate(MirrorLinkWidget* parent);
    ~MirrorLinkWidgetPrivate();
    void initialize();
    void initializeBluetoothTipWidget();
    void receiveAllCustomEvent();
    void connectAllSlots();
    void onMirrorLinkStatus(const Link_STATUS status);
    void touchBeginEventHandler(QEvent* event);
    void touchUpdateEventHandler(QEvent* event);
    void touchEndEventHandler(QEvent* event);
    QString translateTouchEvent(const QList<TouchEvent> &list);
    MirrorShortCutWidget* m_MirrorShortCutWidget = NULL;
    MessageBox* m_DeviceMessageBox = NULL;
    MirrorMessageDialog* m_MirrorMessageDialog = NULL;
    MirrorToolWidget* m_MirrorToolWidget = NULL;
    BmpButton* m_PopBtn = NULL;
    BmpWidget* m_BluetoothTip = NULL;
    QPoint m_Src = QPoint(0, 0);
    QPoint m_Dest = QPoint(0, 0);
    bool m_Filter = false;
    QTimer* m_Timer = NULL;
private:
    MirrorLinkWidget* m_Parent = NULL;
};

MirrorLinkWidget::MirrorLinkWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MirrorLinkWidgetPrivate(this))
{

}

MirrorLinkWidget::~MirrorLinkWidget()
{
}

void MirrorLinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, g_Widget->baseWindowHeight() - 40, 40, 40, m_Private->m_PopBtn);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_MirrorMessageDialog);
}

void MirrorLinkWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
    QWidget::paintEvent(event);
}

void MirrorLinkWidget::mousePressEvent(QMouseEvent *event)
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
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //    qWarning() << __FUNCTION__ << event->pos() << qgetenv("QWS_ARK_MT_DEVICE").isEmpty();
    if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointReleased;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::mouseMoveEvent(QMouseEvent *event)
{
    //    qWarning() << __FUNCTION__ << event->pos() << QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty();
    if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointMoved;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::customEvent(QEvent *event)
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

void MirrorLinkWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    g_Setting->setDisplayScreen(DST_On);
}

bool MirrorLinkWidget::event(QEvent *event)
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

void MirrorLinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{

   qWarning() << "MirrorLinkWidget::ontWidgetTypeChange" << status;
    switch (type) {
    case Widget::T_Mirror: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->initialize();
            m_Private->receiveAllCustomEvent();
            m_Private->connectAllSlots();
            g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_STARTING);
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
            if (NULL != m_Private->m_DeviceMessageBox) {
                m_Private->m_DeviceMessageBox->setVisible(false);
            }
            setVisible(false);
        }
        break;
    }
    }
}

void MirrorLinkWidget::onMessageWidgetChange(const MessageBox::Type type)
{
    if (MessageBox::T_Hide == type) {
        m_Private->m_DeviceMessageBox->setVisible(false);
    }
}

void MirrorLinkWidget::onPopBtnRelease()
{
    qWarning() << "MirrorLinkWidget::onPopBtnRelease" << m_Private->m_MirrorToolWidget->isVisible();
    if (m_Private->m_MirrorToolWidget->isVisible()) {
        m_Private->m_Timer->stop();
        m_Private->m_MirrorMessageDialog->setVisible(false);
        m_Private->m_MirrorToolWidget->setVisible(false);
    } else {
        m_Private->m_Timer->start();
        m_Private->m_MirrorToolWidget->setVisible(true);
    }
}

void MirrorLinkWidget::onToolBtnRelease(const int type)
{
    qWarning() << "MirrorLinkWidget::onToolBtnRelease" << type;
    switch(type) {
    case MirrorToolWidget::T_BlueTooth: {
        if (m_Private->m_MirrorMessageDialog->isVisible()) {
            m_Private->m_Timer->start();
            m_Private->m_MirrorMessageDialog->setVisible(false);
        } else {
            m_Private->m_MirrorMessageDialog->setVisible(true);
            m_Private->m_Timer->stop();
        }
        break;
    }
    case MirrorToolWidget::T_Car: {
        m_Private->m_Timer->stop();
        m_Private->m_MirrorToolWidget->setVisible(false);
        g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_EXITING);
        break;
    }
    case MirrorToolWidget::T_Back: {
        m_Private->m_Timer->start();
        g_Link->requestKeyValue(BACK_KEY);
        break;
    }
    case MirrorToolWidget::T_Home: {
        m_Private->m_Timer->start();
        g_Link->requestKeyValue(HOME_KEY);
        break;;
    }
    case MirrorToolWidget::T_Menu: {
        m_Private->m_Timer->start();
        g_Link->requestKeyValue(MENU_KEY);
        break;
    }
    default: {
        break;
    }
    }
}

void MirrorLinkWidget::onTimeout()
{
    m_Private->m_MirrorMessageDialog->setVisible(false);
    m_Private->m_MirrorToolWidget->setVisible(false);
}

void MirrorLinkWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "MirrorLinkWidget::onLinkStatusChange" << type << status;
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->onMirrorLinkStatus(status);
        break;
    }
    default: {
        break;
    }
    }
}

void MirrorLinkWidget::onBTStatus(int status)
{
    m_Private->initializeBluetoothTipWidget();
    if (BT_CONNECTED == status) {
        m_Private->m_BluetoothTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/BluetoothConnectTipNormal"));
    } else {
        m_Private->m_BluetoothTip->setBackgroundBmpPath(QString(""));
    }
    m_Private->m_BluetoothTip->setVisible(true);
    if (NULL != m_Private->m_MirrorMessageDialog) {
        m_Private->m_MirrorMessageDialog->setDeviceStatus(status);
    }
}

void MirrorLinkWidget::onBTPairCode(QString code)
{
    qDebug() << "MirrorLinkWidget::onBTPairCode" << code;
    if (NULL != m_Private->m_MirrorMessageDialog) {
        m_Private->m_MirrorMessageDialog->setDeviceCode(code);
    }
}

void MirrorLinkWidget::onBTName(QString name)
{
    qDebug() << "MirrorLinkWidget::onBTName" << name;
    if (NULL != m_Private->m_MirrorMessageDialog) {
        m_Private->m_MirrorMessageDialog->setDeviceName(name);
    }
}

MirrorLinkWidgetPrivate::MirrorLinkWidgetPrivate(MirrorLinkWidget* parent)
    : m_Parent(parent)
{

    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

MirrorLinkWidgetPrivate::~MirrorLinkWidgetPrivate()
{
}

void MirrorLinkWidgetPrivate::initialize()
{
    if (NULL == m_Timer) {
        m_Timer = new QTimer(m_Parent);
        m_Timer->setSingleShot(true);
        m_Timer->setInterval(5000);
    }
    if (NULL == m_MirrorMessageDialog) {
        m_MirrorMessageDialog = new MirrorMessageDialog(m_Parent);
        m_MirrorMessageDialog->setVisible(true);
    }
    if (NULL == m_MirrorToolWidget) {
        m_MirrorToolWidget = new MirrorToolWidget(m_Parent);
        m_MirrorToolWidget->setVisible(false);
    }
    if (NULL == m_MirrorShortCutWidget) {
        m_MirrorShortCutWidget = new MirrorShortCutWidget(m_Parent);
    }
    if (NULL == m_PopBtn) {
        m_PopBtn = new BmpButton(m_Parent);
        m_PopBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorPotBtnNormal"));
        m_PopBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorPotBtnNormal"));
        m_PopBtn->setVisible(true);
    }
    if (NULL == m_DeviceMessageBox) {
        m_DeviceMessageBox = new MessageBox(m_Parent);
        m_DeviceMessageBox->hide();
        m_DeviceMessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    }
}

void MirrorLinkWidgetPrivate::initializeBluetoothTipWidget()
{
    if (NULL == m_BluetoothTip) {
        m_BluetoothTip = new BmpWidget(m_Parent);
        m_BluetoothTip->setVisible(true);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_BluetoothTip));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(1280 - 95 - 60, 0, 60, 60, m_BluetoothTip);
    }
}

void MirrorLinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MirrorLinkWidgetPrivate::connectAllSlots()
{    
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
    connectSignalAndSlotByNamesake(g_Port, m_Parent);
    connectSignalAndSlotByNamesake(g_BT, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    if (NULL != m_DeviceMessageBox) {
        QObject::connect(m_DeviceMessageBox, SIGNAL(messageWidgetChange(const MessageBox::Type)),
                         m_Parent,           SLOT(onMessageWidgetChange(const MessageBox::Type)),
                         type);
    }
    if (NULL != m_PopBtn) {
        QObject::connect(m_PopBtn, SIGNAL(bmpButtonRelease()),
                         m_Parent, SLOT(onPopBtnRelease()),
                         type);
    }
    if (NULL != m_Timer) {
        QObject::connect(m_Timer,  SIGNAL(timeout()),
                         m_Parent, SLOT(onTimeout()),
                         type);
    }
    if (NULL != m_MirrorToolWidget) {
        QObject::connect(m_MirrorToolWidget,  SIGNAL(toolBtnRelease(const int)),
                         m_Parent,            SLOT(onToolBtnRelease(const int)),
                         type);
    }
}

void MirrorLinkWidgetPrivate::onMirrorLinkStatus(const Link_STATUS status)
{
    qDebug() << "onMirrorLinkStatus" << status;
    switch (status) {
    case LINK_STARTING: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MessageBoxWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
//        m_DeviceMessageBox->setText(SourceString::Conneting_Mirror_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event2);
        break;
    }
    case LINK_DISCONNECTED: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(true);
//        m_DeviceMessageBox->setText(SourceString::No_Mirror_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        break;
    }
    case LINK_EXITING: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        break;
    }
    case LINK_EXITED: {
        g_Port->setStatus(Port::MirrorDisConnected);
       char data = Port::MirrorDisConnected;
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
//            m_DeviceMessageBox->setText(SourceString::Remove_Mirror_Device);
            g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
            //            QVariant* variant = new QVariant();
            //            variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
            //            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
            //            g_EventEngine->sendCustomEvent(event);
            //            m_DeviceMessageBox->setAutoHide(true);
            //            g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
            //            m_DeviceMessageBox->setText(SourceString::Remove_Mirror_Device);
            //            EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
            //            g_EventEngine->sendCustomEvent(event2);
            //            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        }
        break;
    }
    case LINK_SUCCESS: {
        g_Port->setStatus(Port::MirrorConnected);

         char data = Port::MirrorConnected;
        g_Port->responseMCU(Port::C_SoundStatus, &data, 1);

        EventEngine::CustomEvent<QString> event(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event);
        g_Widget->setWidgetType(Widget::T_Mirror, WidgetStatus::Show);
        m_MirrorToolWidget->setVisible(true);
        m_Timer->start();
        m_Parent->startTimer(250);
        break;
    }
    default: {
        break;
    }
    }
}

void MirrorLinkWidgetPrivate::touchBeginEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
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
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
        }
    }
}

void MirrorLinkWidgetPrivate::touchUpdateEventHandler(QEvent *event)
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
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchUpdate, touchPointXml);
        }
    }
}

void MirrorLinkWidgetPrivate::touchEndEventHandler(QEvent *event)
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
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchEnd, touchPointXml);
        }
    }
}

QString MirrorLinkWidgetPrivate::translateTouchEvent(const QList<TouchEvent> &list)
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
