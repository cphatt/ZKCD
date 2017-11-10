#ifndef IMAGETOOLBARWIDGET_H
#define IMAGETOOLBARWIDGET_H

#include "Widget.h"
#include "Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class ImageToolBarWidgetPrivate;
class ImageToolBarWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageToolBarWidget)
public:
    explicit ImageToolBarWidget(QWidget *parent = NULL);
    ~ImageToolBarWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onImagePlayerPlayStatus(const int status);
    //void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
private slots:
    void onToolButtonRelease();
private:
    friend class ImageToolBarWidgetPrivate;
    QScopedPointer<ImageToolBarWidgetPrivate> m_Private;
};

#endif // IMAGETOOLBARWIDGET_H
