#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class StatusBarWidgetPrivate;
class StatusBarWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(StatusBarWidget)
public:
    explicit StatusBarWidget(QWidget *parent = NULL);
    ~StatusBarWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void paintEvent(QPaintEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class StatusBarWidgetPrivate;
    friend class TextWidget;
    QScopedPointer<StatusBarWidgetPrivate> m_Private;
};

#endif // STATUSBAR_H
