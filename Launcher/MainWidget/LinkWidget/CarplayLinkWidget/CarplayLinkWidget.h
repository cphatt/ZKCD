#ifndef CARPLAYLINKWIDGET_H
#define CARPLAYLINKWIDGET_H

#include "Link.h"
#include "Widget.h"
#include  "Port.h"
#include "MessageBox.h"
#include <QWidget>
#include <QScopedPointer>

class CarplayLinkWidgetPrivate;
class CarplayLinkWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CarplayLinkWidget)
public:
    explicit CarplayLinkWidget(QWidget *parent = NULL);
    ~CarplayLinkWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void customEvent(QEvent* event);
    void timerEvent(QTimerEvent* event);
    bool event(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onLinkStatusChange(const int type, const int status);
    //  void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
private:
    friend class CarplayLinkWidgetPrivate;
    QScopedPointer<CarplayLinkWidgetPrivate> m_Private;
};

#endif // CARPLAYLINKWIDGET_H
