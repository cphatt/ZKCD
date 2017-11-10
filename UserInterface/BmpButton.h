#ifndef BMPBUTTON_H
#define BMPBUTTON_H

#include <QWidget>
#include <QScopedPointer>

class BmpButtonPrivate;
class BmpButton : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(BmpButton)
public:
    enum ButtonStatus {
        B_Normal = 0,
        B_Press,
        B_Check,
    };
    explicit BmpButton(QWidget *parent = NULL);
    ~BmpButton();
    void setText(const QString &text);
    QString getText();
    void setNormalBmpPath(const QString &path);
    void setPressBmpPath(const QString &path);
    void setCheckBmpPath(const QString &path);
    void setStatus(const BmpButton::ButtonStatus &status);
    BmpButton::ButtonStatus getStatus();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    virtual void normalPaint(QPainter& painter);
    virtual void pressPaint(QPainter& painter);
    virtual void checkPaint(QPainter& painter);
signals:
    void bmpButtomPress();
    void bmpButtonRelease();
private:
    friend class BmpButtonPrivate;
    QScopedPointer<BmpButtonPrivate> m_Private;
};

#endif // BMPBUTTON_H
