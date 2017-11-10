#include "SettingPersistent.h"
#include "SettingService.h"
#include "ark_api.h"
#include "UserInterfaceUtility.h"
#include <QSettings>
#include <QCoreApplication>

static const QString persistentPath("/data/Setting.ini");
static const QString persistentPathBackup("/data/SettingBackup.ini");

static const QString Exists("Exists");
static const QString Calibrate("Calibrate");
static const QString Language("Language");
static const QString Brightness("Brightness");
static const QString Contrast("Contrast");
static const QString Saturation("Saturation");

class SettingSettings : public QSettings
{
    Q_DISABLE_COPY(SettingSettings)
#ifdef g_SettingSettings
#undef g_SettingSettings
#endif
#define g_SettingSettings (SettingSettings::instance())
public:
    inline static SettingSettings* instance() {
        static SettingSettings* settings(new SettingSettings(qApp));
        return settings;
    }
    void clear();
    void sync();
    void setValue(const QString &key, const QVariant &value);
private:
    explicit SettingSettings(QObject* parent = NULL);
    ~SettingSettings();
    QSettings m_SettingsBackup;
};

void SettingPersistent::setLanguage(const int value)
{
    qDebug() << "SettingPersistent::setLanguage" << value;
    g_SettingSettings->setValue(Language, value);
    g_SettingSettings->sync();
}

QString SettingPersistent::getLanguageResources()
{
    QString languagePath;
    switch (getLanguage()) {
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
    return languagePath;
}


bool SettingPersistent::restoreBrightness()
{
    qDebug() << "restoreBrightness";
#ifndef gcc
    int ret = arkapi_set_layer_brightness(OSD1_LAYER, 46 + 14 * getBrightness());
//    qDebug() << "arkapi_set_layer_brightness" << ret << arkapi_get_layer_brightness(OSD1_LAYER);
#endif
    return true;
}

bool SettingPersistent::restoreContrast()
{
    qDebug() << "restoreContrast";
#ifndef gcc
    int ret = arkapi_set_layer_contrast(OSD1_LAYER, 46 + 14 * getContrast());
//    qDebug() << "arkapi_set_layer_contrast" << ret << arkapi_get_layer_contrast(OSD1_LAYER);
#endif
    return true;
}

bool SettingPersistent::restoreSaturation()
{
    qDebug() << "restoreSaturation";
#ifndef gcc
    arkapi_set_layer_saturation(OSD2_LAYER, 60);
    arkapi_set_layer_saturation(VIDEO2_LAYER, 60);
    int ret = arkapi_set_layer_saturation(OSD1_LAYER, 46 + 14 * getSaturation());
//    qDebug() << "arkapi_set_layer_saturation" << ret << arkapi_get_layer_saturation(OSD1_LAYER);
#endif
    return true;
}

bool SettingPersistent::getCalibrate()
{
    bool flag(false);
    bool ret = g_SettingSettings->value(Calibrate, flag).toBool();
    qDebug() << "ret" << __FUNCTION__ << ret;
    return ret;
}

int SettingPersistent::getLanguage(const bool update)
{
    int defaultValue(LT_Chinese);
    bool flag(false);
    if (update) {
        g_SettingSettings->sync();
    }
    int ret = g_SettingSettings->value(Language, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setBrightness(const int value)
{
    qDebug() << "SettingPersistent::setBrightness" << value;
    g_SettingSettings->setValue(Brightness, value);
    g_SettingSettings->sync();
}

int SettingPersistent::getBrightness(const bool reload)
{
    int defaultValue(7);
    bool flag(false);
    if (reload) {
        g_SettingSettings->sync();
    }
    int ret = g_SettingSettings->value(Brightness, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setContrast(const int value)
{
    qDebug() << "SettingPersistent::setContrast" << value;
    g_SettingSettings->setValue(Contrast, value);
    g_SettingSettings->sync();
}

int SettingPersistent::getContrast(const bool reload)
{
    int defaultValue(7);
    bool flag(false);
    if (reload) {
        g_SettingSettings->sync();
    }
    int ret = g_SettingSettings->value(Contrast, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setSaturation(const int value)
{
    qDebug() << "SettingPersistent::setSaturation" << value;
    g_SettingSettings->setValue(Saturation, value);
    g_SettingSettings->sync();
}

void SettingPersistent::reset()
{
    g_SettingSettings->clear();
    g_SettingSettings->sync();
}

int SettingPersistent::getSaturation(const bool reload)
{
    int defaultValue(7);
    bool flag(false);
    if (reload) {
        g_SettingSettings->sync();
    }
    int ret = g_SettingSettings->value(Saturation, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setCalibrate(const bool flag)
{
    qDebug() << "SettingPersistent::setCalibrate" << g_SettingSettings->parent();
    g_SettingSettings->setValue(Calibrate, flag);
    g_SettingSettings->sync();
}

SettingPersistent::SettingPersistent()
{
}

SettingPersistent::~SettingPersistent()
{
}

void SettingSettings::clear()
{
    QSettings::clear();
    m_SettingsBackup.clear();
}

void SettingSettings::sync()
{
    QSettings::sync();
    m_SettingsBackup.sync();
}

void SettingSettings::setValue(const QString &key, const QVariant &value)
{
    if (!contains(Exists)) {
        QSettings::setValue(Exists, QVariant(bool(true)));
    }
    QSettings::setValue(key, value);
    if (!m_SettingsBackup.contains(Exists)) {
        m_SettingsBackup.setValue(Exists, QVariant(bool(true)));
    }
    m_SettingsBackup.setValue(key, value);
}

SettingSettings::SettingSettings(QObject *parent)
    : QSettings(persistentPath, QSettings::IniFormat, parent)
    , m_SettingsBackup(persistentPathBackup, QSettings::IniFormat, parent)
{
    bool ret(true);
    if (contains(Exists) && (!m_SettingsBackup.contains(Exists))) {
        QFile::remove(persistentPathBackup);
        ret = QFile::copy(persistentPath, persistentPathBackup);
    } else if ((!contains(Exists)) && m_SettingsBackup.contains(Exists)) {
        QFile::remove(persistentPath);
        ret = QFile::copy(persistentPathBackup, persistentPath);
    }
    if (!ret) {
        qWarning() << "copy failed!";
    }
}

SettingSettings::~SettingSettings()
{
    qDebug();
}
