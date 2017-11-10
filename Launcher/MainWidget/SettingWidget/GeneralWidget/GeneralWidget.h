#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class GeneralWidgetPrivate;
class GeneralWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralWidget)
public:
    explicit GeneralWidget(QWidget *parent = NULL);
    ~GeneralWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onGeneralListViewItemRelease(const int index);
private:
    friend class GeneralWidgetPrivate;
    QScopedPointer<GeneralWidgetPrivate> m_Private;
};

#endif // GENERALWIDGET_H
