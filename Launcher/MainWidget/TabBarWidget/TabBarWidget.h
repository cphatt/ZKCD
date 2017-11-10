#ifndef TABBAR_H
#define TABBAR_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class TabBarWidgetPrivate;
class TabBarWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(TabBarWidget)
public:
    explicit TabBarWidget(QWidget *parent = NULL);
    ~TabBarWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onTabBarButtonRelease();
private:
    friend class TabBarWidgetPrivate;
    friend class BmpButton;
    QScopedPointer<TabBarWidgetPrivate> m_Private;
};

#endif // TABBAR_H
