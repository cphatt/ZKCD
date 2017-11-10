#ifndef USBDISKVIDEOLISTVIEWWIDGET_H
#define USBDISKVIDEOLISTVIEWWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskVideoListViewWidgetPrivate;
class USBDiskVideoListViewWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskVideoListViewWidget)
public:
    explicit USBDiskVideoListViewWidget(QWidget *parent = 0);
    ~USBDiskVideoListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onVideoPlayerFileNames(const int type, const QString& xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
    //    void onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
private slots:
    void onVideoListViewItemRelease(const int index);
    void onToolButtonRelease();
private:
    friend class USBDiskVideoListViewWidgetPrivate;
    QScopedPointer<USBDiskVideoListViewWidgetPrivate> m_Private;
};

#endif // USBDISKVIDEOLISTVIEWWIDGET_H
