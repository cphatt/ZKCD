#ifndef GeneralResetWidget_H
#define GeneralResetWidget_H

#include <QWidget>
#include <QScopedPointer>

class GeneralResetWidgetPrivate;
class GeneralResetWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralResetWidget)
public:
    explicit GeneralResetWidget(QWidget* parent = NULL);
    ~GeneralResetWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void timerEvent(QTimerEvent* event);
private slots:
    void onToolButtonRelease();
private:
    friend class GeneralResetWidgetPrivate;
    QScopedPointer<GeneralResetWidgetPrivate> m_Private;
};

#endif // GeneralResetWidget_H
