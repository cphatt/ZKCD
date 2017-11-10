#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "Setting.h"
#include "Widget.h"
#include <QWidget>
#include <QScopedPointer>

class LanguageWidgetPrivate;
class LanguageWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(LanguageWidget)
public:
    explicit LanguageWidget(QWidget *parent = NULL);
    ~LanguageWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onLanguageTranslateChange(const int language);
    //    void onLanguageTranslateChange(const LanguageType language);
private slots:
    void onToolButtonRelease();
private:
    friend class LanguageWidgetPrivate;
    QScopedPointer<LanguageWidgetPrivate> m_Private;
};

#endif // LANGUAGEWIDGET_H
