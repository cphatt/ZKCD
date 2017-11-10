#ifndef VERSIONWIDGET_H
#define VERSIONWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VersionWidgetPrivate;
class VersionWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VersionWidget)
public:
    explicit VersionWidget(QWidget *parent = NULL);
    ~VersionWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class VersionWidgetPrivate;
    QScopedPointer<VersionWidgetPrivate> m_Private;
};

#endif // VERSIONWIDGET_H
