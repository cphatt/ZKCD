#ifndef CarlifeShortCutWidget_H
#define CarlifeShortCutWidget_H

#include "BmpButton.h"
#include "Link.h"
#include <QScopedPointer>

class CarlifeShortCutWidgetPrivate;
class CarlifeShortCutWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CarlifeShortCutWidget)
public:
    explicit CarlifeShortCutWidget(QWidget *parent = NULL);
    ~CarlifeShortCutWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void onLinkStatusChange(const int type, const int status);
    //  void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
private slots:
    void onBmpButtonRelease();
private:
    friend class CarlifeShortCutWidgetPrivate;
    QScopedPointer<CarlifeShortCutWidgetPrivate> m_Private;
};

#endif // CarlifeShortCutWidget_H
