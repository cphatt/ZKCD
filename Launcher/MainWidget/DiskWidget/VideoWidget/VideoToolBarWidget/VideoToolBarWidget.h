#ifndef VIDEOTOOLBARWIDGET_H
#define VIDEOTOOLBARWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoToolBarWidgetPrivate;
class VideoToolBarWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoToolBarWidget)
public:
    explicit VideoToolBarWidget(QWidget *parent = NULL);
    ~VideoToolBarWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
    //    void onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
private slots:
    void onToolButtonRelease();
    void onTickMarksMillesimalStart();
    void onTickMarksMillesimalEnd(const int millesimal);
private:
    friend class VideoToolBarWidgetPrivate;
    QScopedPointer<VideoToolBarWidgetPrivate> m_Private;
};

#endif // VIDEOTOOLBARWIDGET_H
