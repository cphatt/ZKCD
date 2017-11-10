#ifndef USBDISKLISTVIEWWIDGET_H
#define USBDISKLISTVIEWWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskListViewWidgetPrivate;
class USBDiskListViewWidget
        : protected QWidget
{
    Q_OBJECT
public:
    explicit USBDiskListViewWidget(QWidget *parent = NULL);
    ~USBDiskListViewWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class USBDiskListViewWidgetPrivate;
    QScopedPointer<USBDiskListViewWidgetPrivate> m_Private;
};

#endif // USBDISKLISTVIEWWIDGET_H
