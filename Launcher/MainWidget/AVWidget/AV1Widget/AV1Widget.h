#ifndef AV1WIDGET_H
#define AV1WIDGET_H

#include "Widget.h"
#include "AV.h"
#include <QWidget>
#include <QScopedPointer>

class AV1WidgetPrivate;
class AV1Widget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(AV1Widget)
public:
    explicit AV1Widget(QWidget *parent = NULL);
    ~AV1Widget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVStatus status);
private slots:
    void onTimeout();
private:
    friend class AV1WidgetPrivate;
    QScopedPointer<AV1WidgetPrivate> m_Private;
};

#endif // AV1WIDGET_H
