#include "MainWidget.h"
#include "UserInterfaceUtility.h"
#include "StatusBarWidget/StatusBarWidget.h"
#include "MessageBox.h"
#include "Widget.h"
#include "MainWidget/HomeWidget/HomeWidget.h"
#include "MainWidget/DiskWidget/DiskWidget.h"
#include "BusinessLogicUtility.h"
#include "LinkWidget/LinkWidget.h"
#include "SettingWidget/SettingWidget.h"
#include "Widget.h"
#include "TabBarWidget/TabBarWidget.h"
#include "IdleWidget/IdleWidget.h"
#include "MessageBoxWidget/MessageBoxWidget.h"
#include "AVWidget/AVWidget.h"
#include "EventEngine.h"
#include "ArkApplication.h"
#include "AudioService.h"
#include "FMWidget/FMWidget.h"
#include "VolumeWidget/VolumeWidget.h"
#include "Utility.h"
#include "SettingPersistent.h"
#include "RunnableThread.h"
#include "MultimediaService.h"
#include "IRWidget/IRWidget.h"
//#include "CalibrateWidget/CalibrateWidget.h"
#include "UserInterfaceUtility.h"
#include "ark_api.h"
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QTimer>
//#include <QWSServer>
//#include <QWSCalibratedMouseHandler>
#include <QDomDocument>

class MainWidgetPrivate
{
    Q_DISABLE_COPY(MainWidgetPrivate)
public:
    explicit MainWidgetPrivate(MainWidget *parent);
    ~MainWidgetPrivate();
    void initializeBasicWidget();
    void initializeDiskWidget();
    void initializeLinkWidget();
    void initializeAVWidget();
    void initializeSettingWidget();
    void initializeVolumeWidget();
    void initializeFMWidget();
    void initializeIRWidget();
    void initializeMessageBoxWidget();
    void initializeIdleWidget();
    void receiveAllCustomEvent();
    void connectAllSlots();
    //    CalibrateWidget* m_CalibrateWidget;
    HomeWidget* m_HomeWidget = NULL;
    DiskWidget* m_DiskWidget = NULL;
    LinkWidget* m_LinkWidget = NULL;
    SettingWidget* m_SettingWidget = NULL;
    AVWidget* m_AVWidget = NULL;
    StatusBarWidget* m_StatusBarWidget = NULL;
    TabBarWidget* m_TabBarWidget = NULL;
    FMWidget* m_FMWidget = NULL;
    IRWidget* m_IRWidget = NULL;
    VolumeWidget* m_VolumeWidget = NULL;
    MessageBoxWidget* m_MessageBoxWidget = NULL;
    IdleWidget* m_IdleWidget = NULL;
    bool m_DisplayVisible = false;
    QTimer *m_Timer;
private:
    MainWidget* m_Parent = NULL;
};

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MainWidgetPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setVisible(true);
    ArkApp->flush();
    ArkApp->sendPostedEvents();
}

MainWidget::~MainWidget()
{
    qDebug() << "MainWidget::~MainWidget";
}

void MainWidget::timerEvent(QTimerEvent *event)
{
    m_Private->receiveAllCustomEvent();
    EventEngine::CustomEvent<int> event1(static_cast<QEvent::Type>(CustomEventType::MainWidgetShow), NULL);
    g_EventEngine->sendCustomEvent(event1);
    killTimer(event->timerId());
}

static void initializeRunnableCallback(void *paramater)
{
    qDebug() << "initializeRunnableCallback111" << paramater;
    MainWidget *m = ( MainWidget *)paramater;
    UserInterfaceUtility::elapsed(QString("<<<<<<<<<<<1111111111111111111"));
    initializeArkVideoResources();
//    ret = QProcess::startDetached(QString("/usr/bin/mirrordemo"));
//    qDebug() << "startDetached mirrordemo" << ret;
    QString serviceName("com.arkmicro.carplay");
    g_DbusService->startService(serviceName);
    serviceName = QString("com.arkmicro.bluetooth");
    g_DbusService->startService(serviceName);
    serviceName = QString("com.arkmicro.mirror");
    g_DbusService->startService(serviceName);
    serviceName = QString("com.arkmicro.carlife");
    g_DbusService->startService(serviceName);
    //    UserInterfaceUtility::elapsed(QString("start ArkMicroMultimediaService<<<<<"));
    QStringList cmd;
    cmd << QString("-t") << MultimediaApplication;
    bool ret = QProcess::startDetached(ArkApp->applicationFilePath(), cmd);
    qDebug() << "start" << ArkMicroMultimediaService << ret;
    //    g_DbusService->startService(ArkMicroMultimediaService);
//    cmd.clear();
//    cmd << QString("-t") << SettingApplication;
//    ret = QProcess::startDetached(ArkApp->applicationFilePath(), cmd);
//    qDebug() << "start" << SettingApplication << ret;
    UserInterfaceUtility::elapsed(QString(">>>>>>>>>>>>222222222222222222"));
//    m->m_Private->m_Timer->start();
}

bool MainWidget::event(QEvent* event)
{
    //qDebug() << "MainWidget::event" << event->type();
    if (!ArkApp->arguments().contains(QString("-calibrate"))) {
        switch (event->type()) {
        case QEvent::ActivationChange: {
            if ((NULL != m_Private)
                    && (!m_Private->m_DisplayVisible)) {
                m_Private->m_DisplayVisible = true;
//                SettingPersistent::restoreBrightness();
//                SettingPersistent::restoreContrast();
//                SettingPersistent::restoreSaturation();
                if (hideArkStartupLogo()) {
                    qDebug() << "Hide ArkLogo!";
                } else {
                    qDebug() << "Hide ArkLogo failed!";
                }
                if (!qgetenv("ARKTVOUT").isEmpty()) {
                    if (0 != arkapi_gui_tvout(1)) {
                        qWarning() << "arkapi_gui_tvout failed!";
                    }
                }
                UserInterfaceUtility::elapsed(QString("vvvvvvvvvvvvvvvvvvvvvvvvvvv"));
                qDebug() << SettingPersistent::getCalibrate();
//                if (qgetenv("QWS_ARK_MT_DEVICE").isEmpty()) {
//                    if (!SettingPersistent::getCalibrate()) {
//                        system("ts_calibrate");
//                        SettingPersistent::setCalibrate(true);
//                        system("sync");
//                        system("reboot");
//                        //                    exit(EXIT_SUCCESS);
//                        ArkApp->quit();
//                        break;
//                    }
//                }
                startTimer(0);
            }
            break;
        }
        default: {
            break;
        }
        }
    }
    return QWidget::event(event);
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
}

void MainWidget::customEvent(QEvent* event)
{
    qWarning() << " MainWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        static bool flag(false);
        if (!flag) {
            flag = true;
            m_Private->initializeDiskWidget();
//            m_Private->initializeLinkWidget();
            m_Private->initializeAVWidget();
            m_Private->connectAllSlots();
            ArkApp->processEvents();
#ifndef APPS
            bool ret = QDBusConnection::sessionBus().registerService(ArkApp->applicationName());
            if (!ret) {
                qCritical() << "LauncherService Register QDbus failed!";
                exit(EXIT_FAILURE);
            }
            UserInterfaceUtility::elapsed(QString("LauncherService Register QDbus ok111111111"));
#endif
            CustomRunnable* runnable = new CustomRunnable();
            runnable->setCallbackFunction(initializeRunnableCallback, this);
            QThreadPool::globalInstance()->start(runnable);
            UserInterfaceUtility::elapsed(QString("initializeRunnableCallback"));

            m_Private->initializeVolumeWidget();
        }
        break;
    }
    case CustomEventType::FMWidgetStatus: {
        m_Private->initializeFMWidget();
        break;
    }
    case CustomEventType::IRWidgetStatus: {
        m_Private->initializeIRWidget();
        break;
    }
    case CustomEventType::VolumeWidgetStatus: {

        break;
    }
    case CustomEventType::IdleWidgetStatus: {
        m_Private->initializeIdleWidget();
        break;
    }
    default: {
        break;
    }
    }
}

void MainWidget::paintEvent(QPaintEvent* event)
{
    if ((NULL != m_Private)
            && (m_Private->m_DisplayVisible)) {
        QPainter painter(this);
        painter.fillRect(rect(), QBrush(UserInterfaceUtility::mainWidgetBackgroundColor()));
    }
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    UserInterfaceUtility::elapsed(QString("MainWidget::mousePressEvent"));
    qDebug() << __FUNCTION__ << "aaaaaaaaaaaaaaaaaaaaaaaaaaa" << event->pos();
}

void MainWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::RequestShow == status) {
        switch (type) {
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo:
        case Widget::T_Link: {
            m_Private->initializeMessageBoxWidget();
            break;
        }
//        case Widget::T_AV1: {
//            m_Private->initializeAV1Widget();
//            break;
//        }
//        case Widget::T_AV2: {
//            m_Private->initializeAV2Widget();
//            break;
//        }
        case Widget::T_Setting: {
            m_Private->initializeSettingWidget();
            break;
        }
        default: {
            break;
        }
        }
    }
}

void MainWidget::onStartCalibrate()
{
    qDebug() << "MainWidget::onStartCalibrate";
    setVisible(false);
}
void MainWidget::onTimeout()
{
    m_Private->initializeLinkWidget();
    g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
}
void MainWidget::onFinishCalibrate(const QString& xml)
{
    qDebug() << "MainWidget::onFinishCalibrate" << xml;
    //    QWSPointerCalibrationData data;
    //    QPoint *screenPoints = data.screenPoints;
    //    QPoint *devicePoints = data.devPoints;
    //    QDomDocument document;
    //    document.setContent(xml);
    //    QDomElement root = document.documentElement();
    //    if ((!root.isNull())
    //            && (root.isElement())
    //            && (QString("Calibrate") == root.toElement().tagName())
    //            && (root.hasChildNodes())) {
    //        QDomNode node = root.firstChild();
    //        while (!node.isNull()) {
    //            if (node.isElement()) {
    //                QDomElement element = node.toElement();
    //                if (!element.isNull()) {
    //                    if ((QString("ScreenPoints") == element.tagName())
    //                            || (QString("DevicePoints") == element.tagName())) {
    //                        QDomNodeList nodeList = element.childNodes();
    //                        for (int i = 0, j = 0, k = 0; i < nodeList.size(); ++i) {
    //                            QDomNode node = nodeList.at(i);
    //                            if (node.isElement()) {
    //                                if (!node.toElement().isNull()) {
    //                                    if (QString("ScreenPoints") == element.tagName()) {
    //                                        if (node.toElement().tagName().contains(QString("ScreenPointsX:"))) {
    //                                            screenPoints[j].setX(node.toElement().text().toInt());
    //                                        } else if (node.toElement().tagName().contains(QString("ScreenPointsY:"))) {
    //                                            screenPoints[j].setY(node.toElement().text().toInt());
    //                                            ++j;
    //                                        }
    //                                    } else if (QString("DevicePoints") == element.tagName()) {
    //                                        if (node.toElement().tagName().contains(QString("DevicePointsX:"))) {
    //                                            devicePoints[k].setX(node.toElement().text().toInt());
    //                                        } else if (node.toElement().tagName().contains(QString("DevicePointsY:"))) {
    //                                            devicePoints[k].setY(node.toElement().text().toInt());
    //                                            ++k;
    //                                        }
    //                                    }
    //                                    qDebug() << root.toElement().tagName();
    //                                    qDebug() << "Index:" << node.toElement().tagName();
    //                                    qDebug() << "value:" << node.toElement().text();
    //                                }
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //            node = node.nextSibling();
    //        }
    //    }
    //    qDebug() << "calibrate";
    //    for (int i = 0; i < 5; ++i) {
    //        qDebug() << screenPoints[i].x() << screenPoints[i].y();
    //        qDebug() << devicePoints[i].x() << devicePoints[i].y();
    //    }
    //    QWSServer::mouseHandler()->calibrate(&(data));
    setVisible(true);
}

MainWidgetPrivate::MainWidgetPrivate(MainWidget *parent)
    : m_Parent(parent)
{
    UserInterfaceUtility::elapsed("MainWidgetPrivate<<");
    //    if (ArkApp->arguments().contains(QString("-calibrate"))) {
    //        m_CalibrateWidget = new CalibrateWidget(m_Parent);
    //    } else {
    initializeBasicWidget();
    //    }
    UserInterfaceUtility::elapsed("MainWidgetPrivate>>");
}

MainWidgetPrivate::~MainWidgetPrivate()
{
}

void MainWidgetPrivate::initializeBasicWidget()
{

    ArkApp->installTranslatorPath(SettingPersistent::getLanguageResources());
    m_LinkWidget = new LinkWidget(m_Parent);

//    m_StatusBarWidget = new StatusBarWidget(m_Parent);
    UserInterfaceUtility::elapsed("StatusBarWidget>>");
    m_HomeWidget = new HomeWidget(m_Parent);
    UserInterfaceUtility::elapsed("HomeWidget>>");
    m_TabBarWidget = new TabBarWidget(m_Parent);
    UserInterfaceUtility::elapsed("TabBarWidget>>");
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(1000);

    g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
    //    QStringList cmd;
    //    cmd << QString("-t") << QString("-qws") << QString("-calibrate");
    //    QDBusConnection::sessionBus().connect(QString(),
    //                                          CALIBRATEPATH,
    //                                          CALIBRATEINTERFACE,
    //                                          CALIBRATESTARTMETHOD,
    //                                          m_Parent,
    //                                          SLOT(onStartCalibrate()));
    //    QDBusConnection::sessionBus().connect(QString(),
    //                                          CALIBRATEPATH,
    //                                          CALIBRATEINTERFACE,
    //                                          CALIBRATEFINISHMETHOD,
    //                                          m_Parent,
    //                                          SLOT(onFinishCalibrate(const QString&)));
    //    bool ret = QProcess::startDetached(ArkApp->applicationFilePath(), cmd);
    //    qDebug() << "start" << QString("-calibrate") << ret;
}

void MainWidgetPrivate::initializeDiskWidget()
{
    if (NULL == m_DiskWidget) {
        m_DiskWidget = new DiskWidget(m_Parent);
    }
}

void MainWidgetPrivate::initializeLinkWidget()
{
    if (NULL == m_LinkWidget) {
        m_LinkWidget = new LinkWidget(m_Parent);
    }
}

void MainWidgetPrivate::initializeAVWidget()
{
    if (NULL == m_AVWidget) {
        m_AVWidget = new AVWidget(m_Parent);
    }
}

//void MainWidgetPrivate::initializeAV1Widget()
//{
//    static bool AV1(true);
//    if (AV1) {
//        AV1 = false;
//        g_Widget->setWidgetType(Widget::T_AV1, WidgetStatus::RequestShow);
//    }
//}

//void MainWidgetPrivate::initializeAV2Widget()
//{
//    static bool AV2(true);
//    if (AV2) {
//        AV2 = false;
//        g_Widget->setWidgetType(Widget::T_AV2, WidgetStatus::RequestShow);
//    }
//}

void MainWidgetPrivate::initializeSettingWidget()
{
    if (NULL == m_SettingWidget) {
        m_SettingWidget = new SettingWidget(m_Parent);
    }
}

void MainWidgetPrivate::initializeVolumeWidget()
{
    if (NULL == m_VolumeWidget) {
        m_VolumeWidget = new VolumeWidget(m_Parent);
    }
}

void MainWidgetPrivate::initializeFMWidget()
{
    if (NULL == m_FMWidget) {
        m_FMWidget = new FMWidget(m_Parent);
        EventEngine::CustomEvent<QString> event(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    }
}

void MainWidgetPrivate::initializeIRWidget()
{
    if (NULL == m_IRWidget) {
        m_IRWidget = new IRWidget(m_Parent);
        EventEngine::CustomEvent<QString> event(CustomEventType::IRWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    }
}

void MainWidgetPrivate::initializeMessageBoxWidget()
{
    if (NULL == m_MessageBoxWidget) {
        m_MessageBoxWidget = new MessageBoxWidget(m_Parent);
    }
}

void MainWidgetPrivate::initializeIdleWidget()
{
    if (NULL == m_IdleWidget) {
        m_IdleWidget = new IdleWidget(m_Parent);
    }
}

void MainWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MainWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}
