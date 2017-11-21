#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include "Audio.h"
#include "Port.h"
#include <QWidget>
#include <QScopedPointer>

class VolumeWidgetPrivate;
class VolumeWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VolumeWidget)
public:
    explicit VolumeWidget(QWidget* parent = NULL);
    ~VolumeWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

protected slots:
    void onVolumeChange(int type, const int volume);
//    void onVolumeChange(OutPutSource type, const int volume);

private slots:
     void onMCUDataRecv( int size);
    void onTimeout();
private:
    friend class VolumeWidgetPrivate;
    QScopedPointer<VolumeWidgetPrivate> m_Private;
};

#endif // VOLUMEWIDGET_H
