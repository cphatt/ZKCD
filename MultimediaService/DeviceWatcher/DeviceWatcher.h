#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H

#include "MultimediaService.h"
#include "DiskDeviceWatcher.h"
#include <QObject>
#include <QProcess>
#include <QScopedPointer>

class DeviceWatcherPrivate;
class DeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeviceWatcher)
#ifdef g_DeviceWatcher
#undef g_DeviceWatcher
#endif
#define g_DeviceWatcher (DeviceWatcher::instance())
public:
    inline static DeviceWatcher* instance() {
        static DeviceWatcher* deviceWatcher(new DeviceWatcher(qApp));
        return deviceWatcher;
    }
    void synchronize();
    void deviceWatcherCheckStatus(const int type);
    //    void deviceWatcherCheckStatus(const DeviceWatcherType type);
signals:
    void onDeviceWatcherStatus(const int type, const int status);
    //    void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicFilePath(const QString &path, const int type);
    //    void onMusicFilePath(const QString &path, const DeviceWatcherType type);
    void onImageFilePath(const QString &path, const int type);
    //    void onImageFilePath(const QString &path, const DeviceWatcherType type);
    void onVideoFilePath(const QString &path, const int type);
    //    void onVideoFilePath(const QString &path, const DeviceWatcherType type);
protected:
    void timerEvent(QTimerEvent* event);
private slots:
    void onDiskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action);
    void onUSBFilePath(const QString &path, const int index);
    void onSDFilePath(const QString &path, const int index);
    void onFinish();
    void onTimeout();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onError(QProcess::ProcessError error);
    void onStateChanged(QProcess::ProcessState state);
    void onReadyReadStandardOutput();
private:
    explicit DeviceWatcher(QObject *parent = NULL);
    ~DeviceWatcher();
    friend class DeviceWatcherPrivate;
    QScopedPointer<DeviceWatcherPrivate> m_Private;
};

#endif // DEVICEWATCHER_H
