#ifndef SDDISKWIDGET_H
#define SDDISKWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskWidgetPrivate;
class SDDiskWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskWidget)
public:
    explicit SDDiskWidget(QWidget *parent = NULL);
    ~SDDiskWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
private:
    friend class SDDiskWidgetPrivate;
    QScopedPointer<SDDiskWidgetPrivate> m_Private;
};

#endif // SDDISKWIDGET_H




