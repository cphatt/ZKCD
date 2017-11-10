#ifndef IMAGEPLAYER_H
#define IMAGEPLAYER_H

#include "DeviceWatcher/DeviceWatcher.h"
#include <QObject>
#include <QImage>
#include <QScopedPointer>

class ImagePlayerPrivate;
class ImagePlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ImagePlayer)
#ifdef g_ImagePlayer
#undef g_ImagePlayer
#endif
#define g_ImagePlayer (ImagePlayer::instance())
public:
    inline static ImagePlayer* instance() {
        static ImagePlayer* imagePlayer(new ImagePlayer(qApp));
        return imagePlayer;
    }
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
signals:
    void onImagePlayerFileNames(const int type, const QString &xml);
    //    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const QString &fileName, const int width, const int height, const int format, const QByteArray &imageData);
protected slots:
    void onDeviceWatcherStatus(const int type, const int status);
    //    virtual void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onImageFilePath(const QString &path, const int type);
    //    virtual void onImageFilePath(const QString &path, const DeviceWatcherType type);
private slots:
    void onTimeout();
//    void onAnimationTimerTimeout();
private:
    explicit ImagePlayer(QObject *parent = NULL);
    ~ImagePlayer();
    //    void emitOnImageChange(const QString &fileName, const QImage &image);
    friend class ImagePlayerPrivate;
    QScopedPointer<ImagePlayerPrivate> m_Private;
};

#endif // IMAGEPLAYER_H
