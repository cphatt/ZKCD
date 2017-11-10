#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include "Multimedia.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class MusicWidgetPrivate;
class MusicWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicWidget)
public:
    explicit MusicWidget(QWidget *parent = NULL);
    ~MusicWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
private:
    friend class MusicWidgetPrivate;
    QScopedPointer<MusicWidgetPrivate> m_Private;
};

#endif // MUSICWIDGET_H
