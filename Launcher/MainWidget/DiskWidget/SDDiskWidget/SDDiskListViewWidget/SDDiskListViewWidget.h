#ifndef SDDISKLISTVIEWWIDGET_H
#define SDDISKLISTVIEWWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskListViewWidgetPrivate;
class SDDiskListViewWidget
        : protected QWidget
{
    Q_OBJECT
public:
    explicit SDDiskListViewWidget(QWidget *parent = NULL);
    ~SDDiskListViewWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class SDDiskListViewWidgetPrivate;
    QScopedPointer<SDDiskListViewWidgetPrivate> m_Private;
};

#endif // SDDISKLISTVIEWWIDGET_H
