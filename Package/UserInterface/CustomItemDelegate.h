#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QItemDelegate>
#include <QScopedPointer>

class CustomItemDelegatePrivate;
class CustomItemDelegate : public QItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(CustomItemDelegate)
public:
    explicit CustomItemDelegate(QWidget *parent = NULL);
    ~CustomItemDelegate();
protected:
    virtual void mousePressEvent(QMouseEvent* event,
                                 QAbstractItemModel *model,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index);
    virtual void mouseMoveEvent(QMouseEvent* event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index);
    virtual void mouseReleaseEvent(QMouseEvent* event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index);
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    bool editorEvent(QEvent* event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;
    QWidget* createEditor(QWidget* editor,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget* editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    void setEditorData(QWidget* editor,
                       const QModelIndex &index) const override;
    void setModelData(QWidget* editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
protected slots:
    virtual void onCurrentIndexChange(const QModelIndex &index);
    virtual void onPressIndexChanged(const QModelIndex &index);
private:
    friend class CustomItemDelegatePrivate;
    QScopedPointer<CustomItemDelegatePrivate> m_Private;
};

#endif // CUSTOMITEMDELEGATE_H
