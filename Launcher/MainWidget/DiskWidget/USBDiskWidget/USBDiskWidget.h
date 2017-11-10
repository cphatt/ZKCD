#ifndef USBDISKWIDGET_H
#define USBDISKWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskWidgetPrivate;
class USBDiskWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskWidget)
public:
    explicit USBDiskWidget(QWidget *parent = NULL);
    ~USBDiskWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
private:
    friend class USBDiskWidgetPrivate;
    QScopedPointer<USBDiskWidgetPrivate> m_Private;
};

#endif // USBDISKWIDGET_H
