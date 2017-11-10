#ifndef EFFECTCONTROLS_H
#define EFFECTCONTROLS_H

#include <QWidget>
#include <QScopedPointer>

class EffectSoundWidgetPrivate;
class EffectSoundWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(EffectSoundWidget)
public:
    explicit EffectSoundWidget(QWidget *parent = NULL);
    ~EffectSoundWidget();
protected:
    void resizeEvent(QResizeEvent* event) final;
    void changeEvent(QEvent* event) final;
    void paintEvent(QPaintEvent* event) final;
private:
    friend class EffectSoundWidgetPrivate;
    QScopedPointer<EffectSoundWidgetPrivate> m_Private;
};

#endif // EFFECTCONTROLS_H
