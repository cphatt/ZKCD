#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

#define ArkMicroLauncherService       QString("com.arkmicro.launcher")

class MainWidgetPrivate;
class MainWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWidget)
public:
    explicit MainWidget(QWidget* parent = NULL);
    ~MainWidget();
protected:
    void timerEvent(QTimerEvent* event);
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onStartCalibrate();
    void onFinishCalibrate(const QString& xml);
    void onTimeout();
public:
    friend class MainWidgetPrivate;
    QScopedPointer<MainWidgetPrivate> m_Private;
};

#endif // MAINWINDOW_H
