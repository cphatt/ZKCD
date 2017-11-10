#ifndef USBDISKMUSICLISTVIEWWIDGET_H
#define USBDISKMUSICLISTVIEWWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskMusicListViewWidgetPrivate;
class USBDiskMusicListViewWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskMusicListViewWidget)
public:
    explicit USBDiskMusicListViewWidget(QWidget *parent = 0);
    ~USBDiskMusicListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicPlayerFileNames(const int type, const QString &xml);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerID3TagChange(const int type,
                                   const int index,
                                   const QString &fileName,
                                   const int endTime);
    void onMusicPlayerElapsedInformation(const int elapsedTime,
                                         const int elapsedMillesimal);
    //    void onMusicPlayerID3TagChange(const DeviceWatcherType type,
    //                                   const int index,
    //                                   const QString &fileName,
    //                                   const int endTime);
private slots:
    void onMusicListViewItemRelease(const int index);
    void onToolButtonRelease();
private:
    friend class USBDiskMusicListViewWidgetPrivate;
    QScopedPointer<USBDiskMusicListViewWidgetPrivate> m_Private;
};

#endif // USBDISKMUSICLISTVIEWWIDGET_H
