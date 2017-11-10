#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "VideoToolBarWidget/VideoToolBarWidget.h"
#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoWidgetPrivate;
class VideoWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoWidget)
public:
    explicit VideoWidget(QWidget *parent = NULL);
    ~VideoWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
    //    void onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime);
private slots:
    void onTimeout();
private:
    friend class VideoWidgetPrivate;
    QScopedPointer<VideoWidgetPrivate> m_Private;
};

#endif // VIDEOWIDGET_H
