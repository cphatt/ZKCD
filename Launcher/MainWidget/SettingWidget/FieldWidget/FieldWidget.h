#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class FieldWidgetPrivate;
class FieldWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(FieldWidget)
public:
    explicit FieldWidget(QWidget *parent = NULL);
    ~FieldWidget();
protected:
    void showEvent(QShowEvent* event) final;
    void resizeEvent(QResizeEvent* event) final;
    void paintEvent(QPaintEvent* event) final;
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status) final;
private:
    friend class FieldWidgetPrivate;
    QScopedPointer<FieldWidgetPrivate> m_Private;
};

#endif // FIELDWIDGET_H
