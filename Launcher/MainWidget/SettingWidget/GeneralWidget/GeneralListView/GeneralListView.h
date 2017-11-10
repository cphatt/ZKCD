#ifndef GENERALLISTVIEW_H
#define GENERALLISTVIEW_H

#include "CustomListView.h"
#include "Audio.h"
#include "Setting.h"
#include <QScopedPointer>

class GeneralListViewPrivate;
class GeneralListView
        : public CustomListView
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralListView)
public:
    explicit GeneralListView(QWidget* parent = NULL);
    ~GeneralListView();
protected slots:
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onSaturationChange(const int value);
    //    void onDisplayScreenChange(const DisplayScreenType type);
    void onVolumeChange(int type, const int volume);
//    void onVolumeChange(OutPutSource type, const int volume);
private slots:
    void onMinusBtnRelease();
    void onPlusBtnRelease();
    void onTickMarksMillesimalEnd(const int millesimal);
private:
    friend class GeneralListViewPrivate;
    QScopedPointer<GeneralListViewPrivate> m_Private;
};

#endif // GENERALLISTVIEW_H
