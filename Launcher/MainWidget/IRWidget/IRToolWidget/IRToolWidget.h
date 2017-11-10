#ifndef IRTOOLWIDGET_H
#define IRTOOLWIDGET_H

#include "Audio.h"
#include <QWidget>
#include <QScopedPointer>

class IRToolWidgetPrivate;
class IRToolWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(IRToolWidget)
public:
    explicit IRToolWidget(QWidget* parent = NULL);
    ~IRToolWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void onIRIsOpen(int open);
    void onIRChange(int mode);
    void onVolumeChange(int type, const int volume);
//    void onIRChange(IR_Mode mode);
private slots:
    void onToolButtonRelease();
private:
    friend class IRToolWidgetPrivate;
    QScopedPointer<IRToolWidgetPrivate> m_Private;
};

#endif // IRTOOLWIDGET_H
