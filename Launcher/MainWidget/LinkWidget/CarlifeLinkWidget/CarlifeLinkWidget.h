#ifndef CARLIFELINKWIDGET_H
#define CARLIFELINKWIDGET_H

#include "Link.h"
#include "Widget.h"
#include  "Port.h"
#include "MessageBox.h"
#include <QWidget>
#include <QScopedPointer>

class CarlifeLinkWidgetPrivate;
class CarlifeLinkWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CarlifeLinkWidget)
public:
    explicit CarlifeLinkWidget(QWidget *parent = NULL);
    ~CarlifeLinkWidget();
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

private slots:
    void onTimeout();
private:
    friend class CarlifeLinkWidgetPrivate;
    QScopedPointer<CarlifeLinkWidgetPrivate> m_Private;
};

#endif // CARLIFELINKWIDGET_H
