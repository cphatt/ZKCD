#ifndef MIRRORLINKWIDGET_H
#define MIRRORLINKWIDGET_H

#include "Link.h"
#include "Widget.h"
#include "MessageBox.h"
#include "BT.h"
#include <QWidget>
#include <QScopedPointer>

class MirrorLinkWidgetPrivate;
class MirrorLinkWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MirrorLinkWidget)
public:
    explicit MirrorLinkWidget(QWidget *parent = NULL);
    ~MirrorLinkWidget();
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
    void onBTStatus(int status);
    void onBTPairCode(QString code);
    void onBTName(QString name);
private slots:
    void onMessageWidgetChange(const MessageBox::Type type);
    void onPopBtnRelease();
    void onToolBtnRelease(const int type);
    void onTimeout();
private:
    friend class MirrorLinkWidgetPrivate;
    QScopedPointer<MirrorLinkWidgetPrivate> m_Private;
};

#endif // MIRRORLINKWIDGET_H
