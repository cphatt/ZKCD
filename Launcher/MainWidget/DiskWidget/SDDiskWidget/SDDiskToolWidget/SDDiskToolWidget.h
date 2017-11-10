#ifndef SDDISKTOOLWIDGET_H
#define SDDISKTOOLWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskToolWidgetPrivate;
class SDDiskToolWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskToolWidget)
public:
    explicit SDDiskToolWidget(QWidget *parent = NULL);
    ~SDDiskToolWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
private slots:
    void onToolButtonRelease();
private:
    friend class SDDiskToolWidgetPrivate;
    QScopedPointer<SDDiskToolWidgetPrivate> m_Private;
};

#endif // SDDISKTOOLWIDGET_H
