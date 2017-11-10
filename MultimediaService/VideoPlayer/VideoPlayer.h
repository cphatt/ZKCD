#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "DeviceWatcher/DeviceWatcher.h"
#include <QObject>
#include <QProcess>
#include <QScopedPointer>

class VideoPlayerPrivate;
class VideoPlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayer)
#ifdef g_VideoPlayer
#undef g_VideoPlayer
#endif
#define g_VideoPlayer (VideoPlayer::instance())
public:
    inline static VideoPlayer* instance() {
        static VideoPlayer* videoPlayer(new VideoPlayer(qApp));
        return videoPlayer;
    }
//    void releaseAudioSource(const int source);
////    void releaseAudioSource(const AudioSource source);
    void videoPlayerRequestFileNames(const int type);
    //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
    void videoPlayerSetPlayStatusToggle();
    void videoPlayerSetShowStatus(const int status);
    //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
    void videoPlayerSetPlayStatus(const int status);
    //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
    void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height, const int millesimal);
//    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height, const int millesimal);
    void videoPlayerPlayPreviousListViewIndex();
    void videoPlayerPlayNextListViewIndex();
    void videoPlayerSeekToMillesimal(const int millesimal);
    void videoPlayerExit();
signals:
    void onVideoPlayerShowStatus(const int status);
    //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerFileNames(const int type, const QString &xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
//    void onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
protected slots:
    void onDeviceWatcherStatus(const int type, const int status);
    //    virtual void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onVideoFilePath(const QString &path, const int type);
    //    virtual void onVideoFilePath(const QString &path, const DeviceWatcherType type);
private slots:
    void onTimeout();
    void onStarted();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onError(QProcess::ProcessError error);
    void onStateChanged(QProcess::ProcessState state);
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
private:
    explicit VideoPlayer(QObject* parent = NULL);
    ~VideoPlayer();
    friend class VideoPlayerPrivate;
    QScopedPointer<VideoPlayerPrivate> m_Private;
};

#endif // VIDEOPLAYER_H
