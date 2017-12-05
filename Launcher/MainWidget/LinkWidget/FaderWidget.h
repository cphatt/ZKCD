#ifndef FADERWIDGET_H
#define FADERWIDGET_H

#include <QWidget>

class FaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FaderWidget(QWidget *parent = 0);
    void start();
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    QTimer *timer;
    int currentAlpha;
    QColor startColor;
    int duration;
};

#endif // FADERWIDGET_H
