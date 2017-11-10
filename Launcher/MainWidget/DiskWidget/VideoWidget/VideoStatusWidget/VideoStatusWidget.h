#ifndef VIDEOSTATUSWIDGET_H
#define VIDEOSTATUSWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoStatusWidgetPrivate;
class VideoStatusWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoStatusWidget)
public:
    explicit VideoStatusWidget(QWidget *parent = NULL);
    ~VideoStatusWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
private:
    friend class VideoStatusWidgetPrivate;
    QScopedPointer<VideoStatusWidgetPrivate> m_Private;
};

#endif // VIDEOSTATUSWIDGET_H
