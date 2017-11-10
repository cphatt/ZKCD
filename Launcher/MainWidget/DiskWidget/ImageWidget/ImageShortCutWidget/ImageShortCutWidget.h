#ifndef IMAGESHORTCUTWIDGET_H
#define IMAGESHORTCUTWIDGET_H

#include "BmpButton.h"
#include "Multimedia.h"
#include <QScopedPointer>

class ImageShortCutWidgetPrivate;
class ImageShortCutWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageShortCutWidget)
public:
    explicit ImageShortCutWidget(QWidget *parent = NULL);
    ~ImageShortCutWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void onImagePlayerPlayStatus(const int status);
    //    void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
private slots:
    void onBmpButtonRelease();
private:
    friend class ImageShortCutWidgetPrivate;
    QScopedPointer<ImageShortCutWidgetPrivate> m_Private;
};

#endif // IMAGESHORTCUTWIDGET_H
