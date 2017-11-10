#ifndef IRWIDGET_H
#define IRWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class IRWidgetPrivate;
class IRWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(IRWidget)
public:
    explicit IRWidget(QWidget* parent = NULL);
    ~IRWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private slots:
    void onTimeout();
private:
    friend class IRWidgetPrivate;
    QScopedPointer<IRWidgetPrivate> m_Private;
};

#endif // IRWIDGET_H
