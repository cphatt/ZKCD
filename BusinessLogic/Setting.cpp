#include "Setting.h"
#include "BusinessLogicUtility.h"
#include "Widget.h"
#include "ArkApplication.h"
#include "SettingService.h"
#include "SettingPersistent.h"
#include "UserInterfaceUtility.h"
#include <QProcess>
#include <QTranslator>
#include <QDBusServiceWatcher>

class SettingPrivate
{
    Q_DISABLE_COPY(SettingPrivate)
public:
    explicit SettingPrivate(Setting* parent);
    ~SettingPrivate();
    void initialize();
    void connectAllSlots();
    void onLanguageChange(const LanguageType language);
    Local::DbusServer::Setting* m_SettingServiceProxy = NULL;
private:
    Setting* m_Parent = NULL;
};

void Setting::reset()
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->reset();
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::reset" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setLanguage failed" << reply.error();
        }
    }
}

void Setting::setLanguage(const LanguageType language)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setLanguage(language);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::setLanguage" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setLanguage failed" << reply.error();
        }
    }
}

void Setting::setBrightness(const SettingType type, const int value)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setBrightness(type, value);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::setBrightness" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setBrightness failed" << reply.error();
        }
    }
}

void Setting::setContrast(const SettingType type, const int value)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setContrast(type, value);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::setContrast" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setContrast failed" << reply.error();
        }
    }
}

void Setting::setSaturation(const SettingType type, const int value)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setSaturation(type, value);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::setSaturation" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setSaturation failed" << reply.error();
        }
    }
}

void Setting::setDisplayScreen(const DisplayScreenType type)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setDisplayScreen(type);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::setDisplayScreen" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::setDisplayScreen failed" << reply.error();
        }
    }
}

void Setting::startCalibrate()
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->startCalibrate();
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::startCalibrate" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::startCalibrate failed" << reply.error();
        }
    }
}

void Setting::startAV(const AVType type, const int width, const int height)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->startAV(type, width, height);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::startAV" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::startAV failed" << reply.error();
        }
    }
}

void Setting::stopAV(const AVType type)
{
    initializePrivate();
    if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->stopAV(type);
        reply.waitForFinished();
        qWarning() << "Dbus call Setting::stopAV" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call Setting::stopAV failed" << reply.error();
        }
    }
}

void Setting::onLanguageChange(const LanguageType language)
{
    qWarning() << "onLanguageChange" << language;
    m_Private->onLanguageChange(language);
}

void Setting::onServiceRegistered(const QString &service)
{
    qWarning() << "Setting::onServiceRegistered" << service;
    //    if (ArkMicroSettingService == service) {
    //        if (NULL != m_Private->m_SettingService) {
    //            m_Private->m_SettingService->synchronize();
    //        } else if (NULL != m_Private->m_SettingServiceProxy) {
    //            QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->synchronize();
    //            reply.waitForFinished();
    //            qWarning() << "Dbus call m_SettingServiceProxy synchronize" << reply.isFinished();
    //            if (reply.isError()) {
    //                qWarning() << "method call synchronize failed" << reply.error();
    //            }
    //        }
    //    }
}

void Setting::onServiceUnregistered(const QString &service)
{
    qWarning() << "Setting::onServiceUnregistered" << service;
    if (ArkMicroSettingService == service) {
        g_DbusService->startService(ArkMicroSettingService);
        //        g_DbusService->startService(ArkMicroSettingService);
    }
}

Setting::Setting(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    connectSignalAndSlotByNamesake(g_DbusService, this);
    g_DbusService->addWatchedService(ArkMicroSettingService);
}

Setting::~Setting()
{
}

void Setting::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new SettingPrivate(this));
    }
}

SettingPrivate::SettingPrivate(Setting *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

SettingPrivate::~SettingPrivate()
{
}

void SettingPrivate::initialize()
{
    if (NULL == m_SettingServiceProxy) {
        m_SettingServiceProxy = new Local::DbusServer::Setting(ArkMicroSettingService,
                                                               ArkMicroSettingPath,
                                                               QDBusConnection::sessionBus(),
                                                               qApp);
    }
}

void SettingPrivate::connectAllSlots()
{
    if (NULL != m_SettingServiceProxy) {
        connectSignalAndSignalByNamesake(m_SettingServiceProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_SettingServiceProxy, SIGNAL(onLanguageChange(const int)),
                         m_Parent,              SLOT(onLanguageChange(const int)),
                         type);
    }
}

void SettingPrivate::onLanguageChange(const LanguageType language)
{
    QString languagePath;
    languagePath.clear();
    switch (language) {
    case LT_Chinese: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_CN.qm");
        break;
    }
    case LT_Japaness: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_JP.qm");
        break;
    }
    case LT_Korean: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_KO.qm");
        break;
    }
    case LT_Spanish: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_SP.qm");
        break;
    }
    case LT_Portuguese: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_PO.qm");
        break;
    }
    case LT_Russian: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_RU.qm");
        break;
    }
    case LT_German: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_DE.qm");
        break;
    }
    case LT_French: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_FR.qm");
        break;
    }
    case LT_English:
    default: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_EN.qm");
        break;
    }
    }
    if (ArkApp->installTranslatorPath(languagePath)) {
        emit m_Parent->onLanguageTranslateChange(language);
    } else {
        qWarning() << "QTranslator load" << language << languagePath << "fail!";
    }
}
