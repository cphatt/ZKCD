#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class SettingWidgetPrivate;
class SettingWidget
        : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingWidget)
public:
    explicit SettingWidget(QWidget *parent = NULL);
    ~SettingWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onBmpButtonRelease();
private:
    friend class SettingWidgetPrivate;
    QScopedPointer<SettingWidgetPrivate> m_Private;
};

#endif // SETTINGWIDGET_H
