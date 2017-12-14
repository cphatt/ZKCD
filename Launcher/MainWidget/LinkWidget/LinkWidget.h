#ifndef LINKWIDGET_H
#define LINKWIDGET_H

#include "Widget.h"
#include "Link.h"
#include <QWidget>
#include <QScopedPointer>

class LinkWidgetPrivate;
class LinkWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(LinkWidget)
public:
    explicit LinkWidget(QWidget *parent = NULL);
    ~LinkWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
    void customEvent(QEvent* event);
    void timerEvent(QTimerEvent* event);
//    void mouseDoubleClickEvent(QMouseEvent *);
//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//signals:
//    void clickCarlife();
//    void clickCarplay();
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onToolButtonRelease();
    void onMessageChange();
    void onTimeout();

private:
    friend class LinkWidgetPrivate;
    QScopedPointer<LinkWidgetPrivate> m_Private;
};

#endif // LINKWIDGET_H
