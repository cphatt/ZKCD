#ifndef MUSICTOOLWIDGET_H
#define MUSICTOOLWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class MusicToolWidgetPrivate;
class MusicToolWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicToolWidget)
public:
    explicit MusicToolWidget(QWidget *parent = NULL);
    ~MusicToolWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void customEvent(QEvent *event);
protected slots:
    void onMusicPlayerPlayMode(const int mode);
    //        void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode);
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
    void onMusicPlayerID3TagChange(const int type,
                                   const int index,
                                   const QString &fileName,
                                   const int endTime);
    //    void onMusicPlayerID3TagChange(const DeviceWatcherType type,
    //                                   const int index,
    //                                   const QString &fileName,
    //                                   const int endTime);
    //    void onMusicPlayerID3TagChange(const DeviceWatcherType type,
    //                                   const int index,
    //                                   const QString &fileName,
    //                                   const int endTime);
public slots:
    void onTickMarksMillesimalStart();
    void onTickMarksMillesimalEnd(const int millesimal);
    void onToolButtonRelease();
private:
    friend class MusicToolWidgetPrivate;
    QScopedPointer<MusicToolWidgetPrivate> m_Private;
};

#endif // MUSICTOOLWIDGET_H
