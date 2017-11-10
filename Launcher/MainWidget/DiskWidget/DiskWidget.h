#ifndef DISKWIDGET_H
#define DISKWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class DiskWidgetPrivate;
class DiskWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(DiskWidget)
public:
    explicit DiskWidget(QWidget *parent = NULL);
    ~DiskWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class DiskWidgetPrivate;
    QScopedPointer<DiskWidgetPrivate> m_Private;
};

#endif // DISKWIDGET_H
