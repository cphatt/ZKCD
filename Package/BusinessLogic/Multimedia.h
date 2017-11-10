#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "MultimediaService.h"
#include "DbusService.h"
#include "DiskDeviceWatcher.h"
#include <QObject>
#include <QScopedPointer>

class MultimediaPrivate;
class Multimedia
        : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Multimedia)
#ifdef g_Multimedia
#undef g_Multimedia
#endif
#define g_Multimedia (Multimedia::instance())
public:
    inline static Multimedia* instance() {
        static Multimedia* multimedia(new Multimedia(qApp));
        return multimedia;
    }
    void reset();
    void deviceWatcherCheckStatus(const int type);
    //    void deviceWatcherCheckStatus(const DeviceWatcherType type);
    void musicPlayerRequestFileNames();
    void musicPlayerSetPlayModeToggle();
    void musicPlayerSetPlayMode(const int mode);
    //    void musicPlayerSetPlayMode(const MusicPlayerPlayMode mode);
    void musicPlayerSetPlayStatusToggle();
    void musicPlayerSetPlayStatus(const int status);
    //    void musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status);
    void musicPlayerPlayListViewIndex(const int type, const int index, const int millesimal);
    //    void MultimediaService::musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int millesimal);
    void musicPlayerPlayPreviousListViewIndex();
    void musicPlayerPlayNextListViewIndex();
    void musicPlayerSeekToMillesimal(const int millesimal);
    void musicPlayerExit();
    void imagePlayerRequestFileNames(const int type);
    //    void imagePlayerRequestFileNames(const DeviceWatcherType type);
    void imagePlayerPlayListViewIndex(const int type, const int index);
    //    void ImagePlayer::imagePlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void imagePlayerPlayPreviousListViewIndex();
    void imagePlayerPlayNextListViewIndex();
    void imagePlayerRotateImage();
    void imagePlayerZoomInImage();
    void imagePlayerZoomOutImage();
    void imagePlayerSetPlayStatusToggle();
    void imagePlayerSetPlayStatus(const int status);
//        void imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status);
    void imagePlayerExit();
    void videoPlayerRequestFileNames(const int type);
    //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
    void videoPlayerSetPlayStatusToggle();
    void videoPlayerSetShowStatus(const int status);
    //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
    void videoPlayerSetPlayStatus(const int status);
    //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
    void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height, const int millesimal) ;
    //    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height, const int millesimal);
    void videoPlayerPlayPreviousListViewIndex();
    void videoPlayerPlayNextListViewIndex() ;
    void videoPlayerSeekToMillesimal(const int millesimal);
    void videoPlayerExit();
signals:
    void onDeviceWatcherStatus(const int type, const int status);
    //    void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicPlayerPlayMode(const int mode);
    //    void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerElapsedInformation(const int elapsedTime,
                                         const int elapsedMillesimal);
    void onMusicPlayerID3TagChange(const int type,
                                   const int index,
                                   const QString &fileName,
                                   const int endTime);
    //    void onMusicPlayerID3TagChange(const DeviceWatcherType type,
    //                                   const int index,
    //                                   const QString &fileName,
    //                                   const int endTime);
    void onMusicPlayerFileNames(const int type, const QString &xml);
    //    void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerFileNames(const int type, const QString &xml);
    //    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
    void onVideoPlayerShowStatus(const int status);
    //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerFileNames(const int type, const QString& xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
    //    void onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
private slots:
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
    void onMusicPlayerPlayStatusHandler(const int status);
    //    void onMusicPlayerPlayStatusHandler(const MusicPlayerPlayStatus status);
    void onImagePlayerPlayStatusHandler(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onVideoPlayerPlayStatusHandler(const int status);
    //    void onVideoPlayerPlayStatusHandler(const VideoPlayerPlayStatus status);
private:
    explicit Multimedia(QObject* parent = NULL);
    ~Multimedia();
    void initializePrivate();
    friend class MultimediaPrivate;
    QScopedPointer<MultimediaPrivate> m_Private;
};

#endif // MULTIMEDIA_H
