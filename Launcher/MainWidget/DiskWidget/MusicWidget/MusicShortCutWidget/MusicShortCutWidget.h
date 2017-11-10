#ifndef MUSICSHORTCUTWIDGET_H
#define MUSICSHORTCUTWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include "BmpButton.h"
#include <QScopedPointer>

class MusicShortCutWidgetPrivate;
class MusicShortCutWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicShortCutWidget)
public:
    explicit MusicShortCutWidget(QWidget *parent = NULL);
    ~MusicShortCutWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void timerEvent(QTimerEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
private slots:
    void onBmpButtonRelease();
private:
    friend class MusicShortCutWidgetPrivate;
    QScopedPointer<MusicShortCutWidgetPrivate> m_Private;
};

#endif // MUSICSHORTCUTWIDGET_H
