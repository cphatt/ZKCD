#ifndef FMTOOLWIDGETIDGET_H
#define FMTOOLWIDGETIDGET_H

#include "Audio.h"
#include <QWidget>
#include <QScopedPointer>

class FMToolWidgetPrivate;
class FMToolWidget
        : protected QWidget
{
    Q_OBJECT
public:
    explicit FMToolWidget(QWidget* parent = NULL);
    ~FMToolWidget();
protected:
    void resizeEvent(QResizeEvent* event);
protected slots:
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onVolumeChange(int type, const int volume);
private slots:
    void onToolButtonRelease();
private:
    friend class FMToolWidgetPrivate;
    QScopedPointer<FMToolWidgetPrivate> m_Private;
};

#endif // FMTOOLWIDGETIDGET_H
