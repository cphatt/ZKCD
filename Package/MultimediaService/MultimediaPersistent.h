#ifndef MULTIMEDIAPERSISTENT_H
#define MULTIMEDIAPERSISTENT_H

#include "MultimediaService.h"
#include <QtGlobal>

class MultimediaPersistent
{
    Q_DISABLE_COPY(MultimediaPersistent)
public:
    static int getMultimediaType(const int deviceWatcherType, const bool reload = true);
//    static int getMultimediaType(const DeviceWatcherType distType, const MultimediaType multimediaType, const bool reload = true);
    static int getMusicMillesmial(const int type, const bool reload = true);
//    static int getMusicMillesmial(const DeviceWatcherType type, const bool reload = true);
    static QString getMusicPathInfo(const int type, const bool reload = true);
//    static QString getMusicPath(const DeviceWatcherType type, const bool reload = true);
    static QString getImagePathInfo(const int type, const bool reload = true);
//    static QString getImagePath(const DeviceWatcherType type, const bool reload = true);
    static int getVideoMillesmial(const int type, const bool reload = true);
//    static int getVideoMillesmial(const DeviceWatcherType type, const bool reload = true);
    static QString getVideoPathInfo(const int type, const bool reload = true);
//    static QString getVideoPathInfo(const DeviceWatcherType type, const bool reload = true);
protected:
    friend class MultimediaService;
    friend class MusicPlayerPrivate;
    friend class ImagePlayerPrivate;
    friend class VideoPlayerPrivate;
    static void setMultimediaType(const int deviceWatcherType, const int multimediaType);
//    static void setUSBMultimediaType(const DeviceWatcherType distType, const MultimediaType multimediaType);
    static void setMusicMillesmial(const int type, const int millesmial);
//    static void setMusicMillesmial(const DeviceWatcherType type, const int millesmial);
    static void setMusicPathInfo(const int type, const QString& pathpathInfo);
//    static void setMusicPathInfo(const DeviceWatcherType type, const QString& pathInfo);
    static void setImagePathInfo(const int type, const QString& pathpathInfo);
//    static void setImagePathInfo(const DeviceWatcherType type, const QString& pathInfo);
    static void setVideoMillesmial(const int type, const int millesmial);
//    static void setVideoMillesmial(const DeviceWatcherType type, const int millesmial);
    static void setVideoPathInfo(const int type, const QString& pathInfo);
//    static void setVideoPathInfo(const DeviceWatcherType type, const QString& pathInfo);
    static void reset();
private:
    MultimediaPersistent();
    ~MultimediaPersistent();
};

#endif // MULTIMEDIAPERSISTENT_H
