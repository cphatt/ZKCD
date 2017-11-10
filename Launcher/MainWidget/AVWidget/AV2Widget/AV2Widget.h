#ifndef AV2WIDGET_H
#define AV2WIDGET_H

#include "Widget.h"
#include "AV.h"
#include <QWidget>
#include <QScopedPointer>

class AV2WidgetPrivate;
class AV2Widget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(AV2Widget)
public:
    explicit AV2Widget(QWidget *parent = NULL);
    ~AV2Widget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVtatus status);
private slots:
    void onTimeout();
private:
    friend class AV2WidgetPrivate;
    QScopedPointer<AV2WidgetPrivate> m_Private;
};

#endif // AV2WIDGET_H
