#ifndef VIDEOSHORTCUTWIDGET_H
#define VIDEOSHORTCUTWIDGET_H

#include "BmpButton.h"
#include "Multimedia.h"
#include <QScopedPointer>

class VideoShortCutWidgetPrivate;
class VideoShortCutWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoShortCutWidget)
public:
    explicit VideoShortCutWidget(QWidget *parent = NULL);
    ~VideoShortCutWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
private slots:
    void onBmpButtonRelease();
private:
    friend class VideoShortCutWidgetPrivate;
    QScopedPointer<VideoShortCutWidgetPrivate> m_Private;
};

#endif // VIDEOSHORTCUTWIDGET_H
