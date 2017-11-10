#include "VersionListView.h"
#include "CustomItemDelegate.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include "Utility.h"
#include <QStandardItemModel>
#include <QPainter>
#include <QDebug>

class VersionDelegate : public CustomItemDelegate
{
    Q_DISABLE_COPY(VersionDelegate)
public:
    explicit VersionDelegate(QWidget* parent = NULL);
    ~VersionDelegate();
protected:
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

class VersionListViewPrivate
{
    Q_DISABLE_COPY(VersionListViewPrivate)
public:
    explicit VersionListViewPrivate(VersionListView* parent);
    ~VersionListViewPrivate();
    void initialize();
    VersionDelegate* m_VersionDelegate = NULL;
    QStandardItemModel* m_StandardItemModel = NULL;
private:
    VersionListView* m_Parent = NULL;
};

VersionListView::VersionListView(QWidget *parent)
    : CustomListView(parent)
    , m_Private(new VersionListViewPrivate(this))
{
    setVisible(true);
}

VersionListView::~VersionListView()
{
}

VersionListViewPrivate::VersionListViewPrivate(VersionListView *parent)
    : m_Parent(parent)
{
    initialize();
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 626 - 73 + 5, m_Parent);
}

VersionListViewPrivate::~VersionListViewPrivate()
{
}

void VersionListViewPrivate::initialize()
{
    m_VersionDelegate = new VersionDelegate(m_Parent);
    m_Parent->setItemDelegate(m_VersionDelegate);
    m_StandardItemModel = new QStandardItemModel();
    QStandardItem* appItem = new QStandardItem();
    appItem->setSizeHint(QSize((626 - 73) * g_Widget->widthScalabilityFactor(), 93 * g_Widget->heightScalabilityFactor() * 2));
    appItem->setData(QVariant(QString("APP:") + compilerDate()), Qt::DisplayRole);
    QStandardItem* linkItem = new QStandardItem();
    linkItem->setSizeHint(QSize((626 - 73) * g_Widget->widthScalabilityFactor(), 93 * g_Widget->heightScalabilityFactor() * 2));
    linkItem->setData(QVariant(QString("LINK:")), Qt::DisplayRole);
    QStandardItem* osItem = new QStandardItem();
    osItem->setSizeHint(QSize((626 - 73) * g_Widget->widthScalabilityFactor(), 93 * g_Widget->heightScalabilityFactor() * 2));
    osItem->setData(QVariant(QString("OS:") + osVersion()), Qt::DisplayRole);
    QStandardItem* root = m_StandardItemModel->invisibleRootItem();
    root->setChild(0, 0, appItem);
    root->setChild(1, 0, linkItem);
    root->setChild(2, 0, osItem);
    m_Parent->setModel(m_StandardItemModel);
}

VersionDelegate::VersionDelegate(QWidget *parent)
    : CustomItemDelegate(parent)
{
}

VersionDelegate::~VersionDelegate()
{
}

void VersionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QFont font;
    font.setPointSize(20 *g_Widget->widthScalabilityFactor());
    painter->setFont(font);
    painter->setPen(Qt::white);
    QString text = index.data(Qt::DisplayRole).toString();
    painter->drawText(option.rect, Qt::AlignCenter, text);
    painter->setPen(UserInterfaceUtility::customBlackColor());
    painter->drawLine(QPoint(0, option.rect.y() + option.rect.height() - 1), QPoint(option.rect.width(), option.rect.y() + option.rect.height() - 1));
    painter->restore();
}
