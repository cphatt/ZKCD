#ifndef FMWIDGET_H
#define FMWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class FMWidgetPrivate;
class FMWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(FMWidget)
public:
    explicit FMWidget(QWidget* parent = NULL);
    ~FMWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private slots:
    void onTimeout();
private:
    friend class FMWidgetPrivate;
    QScopedPointer<FMWidgetPrivate> m_Private;
};

#endif // FMWIDGET_H
