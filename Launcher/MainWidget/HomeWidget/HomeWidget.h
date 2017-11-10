#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class HomeWidgetPrivate;
class HomeWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(HomeWidget)
public:
    explicit HomeWidget(QWidget *parent = NULL);
    ~HomeWidget();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent *event);
    void customEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class HomeWidgetPrivate;
    QScopedPointer<HomeWidgetPrivate> m_Private;
};

#endif // HOMEWIDGET_H
