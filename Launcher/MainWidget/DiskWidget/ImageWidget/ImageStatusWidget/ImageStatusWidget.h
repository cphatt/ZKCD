#ifndef IMAGESTATUSWIDGET_H
#define IMAGESTATUSWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class ImageStatusWidgetPrivate;
class ImageStatusWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageStatusWidget)
public:
    explicit ImageStatusWidget(QWidget *parent = NULL);
    ~ImageStatusWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type,const QString &status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
private:
    friend class ImageStatusWidgetPrivate;
    QScopedPointer<ImageStatusWidgetPrivate> m_Private;
};

#endif // IMAGESTATUSWIDGET_H
