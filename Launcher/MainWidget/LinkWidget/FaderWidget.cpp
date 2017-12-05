#include "FaderWidget.h"
#include <QTimer>
#include <QPainter>
#include <stdio.h>
#include <QDebug>
FaderWidget::FaderWidget(QWidget *parent) :
    QWidget(parent)
{
    if(parent)
        startColor = parent->palette().window().color();
    else
        startColor = Qt::white;

    currentAlpha = 0;
    duration = 1000;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(update()));

    setAttribute(Qt::WA_DeleteOnClose);
    resize(parent->size());
}

void FaderWidget::start(){
    qDebug() << "1111";
    currentAlpha = 10;
    timer->start(1000);
    show();
}

void FaderWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QColor color = startColor;
    color.setAlpha(2);

    painter.fillRect(rect(), color);
//    qWarning() << currentAlpha;
//    if(currentAlpha-- <= 0){
//        currentAlpha = 10;
//        timer->stop();
//        close();
//    }
}

void FaderWidget::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
}
void FaderWidget::mouseReleaseEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
}
void FaderWidget::mouseMoveEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
}
