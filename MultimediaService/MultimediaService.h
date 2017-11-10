#ifndef MULTIMEDIASERVICE_H
#define MULTIMEDIASERVICE_H

#include "MultimediaServiceProxy.h"
#include <QObject>
#include <QScopedPointer>

#define MultimediaApplication                   QString("-multimedia")
#define ArkMicroMultimediaService               QString("com.arkmicro.multimedia")
#define ArkMicroMultimediaPath                  QString("/com/arkmicro/multimedia")
#define ArkMicroMultimediaInterface             QString("Local.DbusServer.Multimedia")

enum DeviceWatcherType {
    DWT_Undefine = -1,
    DWT_SDDisk = 0,
    DWT_USBDisk = 1,
};
#define DeviceWatcherType int

enum DeviceWatcherStatus {
    DWS_Undefine = -1,
    DWS_Empty = 0,
    DWS_Unsupport = 1,
    DWS_Busy = 2,
    DWS_Ready = 3,
    DWS_Remove = 4,
};
#define DeviceWatcherStatus int

enum MusicPlayerPlayMode {
    MPPM_AllRepeat = 0,
    MPPM_Shuffle = 1,
    MPPM_RepeatOnce = 2,
};
#define MusicPlayerPlayMode int

enum MusicPlayerPlayStatus {
    MPPS_Undefine = -1,
    MPPS_Start = 0,
    MPPS_Unsupport = 1,
    MPPS_Stop = 2,
    MPPS_Pause = 3,
    MPPS_Play = 4,
    MPPS_Exit = 6,
};
#define MusicPlayerPlayStatus int

enum ImagePlayerPlayStatus {
    IPPS_Start = 0,
    IPPS_Pause = 1,
    IPPS_Play = 2,
    IPPS_SuspendToggle = 3,
    IPPS_Exit = 4,
};
#define ImagePlayerPlayStatus int

enum VideoPlayerPlayStatus {
    VPPS_Undefine = -1,
    VPPS_Start = 0,
    VPPS_Unsupport = 1,
    VPPS_Stop = 2,
    VPPS_Pause = 3,
    VPPS_SuspendToggle = 4,
    VPPS_Play = 5,
    VPPS_Exit = 6,
};
#define VideoPlayerPlayStatus int

enum VideoPlayerShowStatus {
    VPSS_Normal = 0,
    VPSS_FullScreen = 1,
};
#define VideoPlayerShowStatus int

enum MultimediaType {
    MT_Undefine = -1,
    MT_Idle = 0,
    MT_Music = 1,
    MT_Image = 2,
    MT_Video = 3,
};
#define MultimediaType int

class MultimediaServicePrivate;
class MultimediaService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Multimedia")
#ifdef g_MultimediaService
#undef g_MultimediaService
#endif
#define g_MultimediaService (MultimediaService::instance())
public:
    explicit MultimediaService(QObject* parent = NULL);
    ~MultimediaService();
public slots:
//    void releaseAudioSource(const int source);
//    //    void releaseAudioSource(const AudioSource source);
    void synchronize();
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
    //    void imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status);
    void imagePlayerExit();
    void videoPlayerRequestFileNames(const int type);
    //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
    void videoPlayerSetPlayStatusToggle();
    void videoPlayerSetShowStatus(const int status);
    //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
    void videoPlayerSetPlayStatus(const int status);
    //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
    void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height, const int millesimal);
    //    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void videoPlayerPlayPreviousListViewIndex();
    void videoPlayerPlayNextListViewIndex();
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
private:
    friend class MultimediaServicePrivate;
    QScopedPointer<MultimediaServicePrivate> m_Private;
};

#endif // MULTIMEDIASERVICE_H
