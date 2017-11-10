#include "MultimediaListView.h"
#include "CustomItemDelegate.h"
#include "CustomScrollBar.h"
#include "Widget.h"
#include "UserInterfaceUtility.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMetaType>
#include <QPainter>
#include <QFontMetrics>
#ifdef SVG
#include <QSvgRenderer>
#endif
#include <QFile>
#include <QPixmap>

class MultimediaVariant
{
public:
    MultimediaVariant();
    ~MultimediaVariant();
    QString m_Text;
};
Q_DECLARE_METATYPE(MultimediaVariant)

class MultimediaDelegate : public CustomItemDelegate
{
    Q_DISABLE_COPY(MultimediaDelegate)
public:
    explicit MultimediaDelegate(QWidget* widget = NULL);
    ~MultimediaDelegate();
protected:
    void mousePressEvent(QMouseEvent* event,
                         QAbstractItemModel *model,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index);
    void mouseMoveEvent(QMouseEvent* event,
                        QAbstractItemModel *model,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index);
    void mouseReleaseEvent(QMouseEvent* event,
                           QAbstractItemModel *model,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index);
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
protected slots:
    void onCurrentIndexChange(const QModelIndex &index);
    void onPressIndexChanged(const QModelIndex &index);
private:
    QModelIndex m_PressIndex;
    QModelIndex m_CurrentIndex;
    QScopedPointer<QPixmap> m_CheckPixmap;
#ifdef SVG
    QScopedPointer<QSvgRenderer> m_CheckSvg;
#endif
};

class MultimediaListViewPrivate
{
    Q_DISABLE_COPY(MultimediaListViewPrivate)
public:
    explicit MultimediaListViewPrivate(MultimediaListView* parent);
    ~MultimediaListViewPrivate();
    void initialize();
    QStandardItemModel* m_StandardItemModel = NULL;
    MultimediaDelegate* m_MultimediaDelegate = NULL;
    CustomScrollBar* m_CustomScrollBar = NULL;
private:
    MultimediaListView* m_Parent = NULL;
};

MultimediaListView::MultimediaListView(QWidget *parent)
    : CustomListView(parent)
    , m_Private(new MultimediaListViewPrivate(this))
{
}

MultimediaListView::~MultimediaListView()
{
}

void MultimediaListView::clearListView()
{
    m_Private->m_StandardItemModel->clear();
    verticalScrollBar()->setValue(0);
    horizontalScrollBar()->setValue(0);
}

void MultimediaListView::appendListView(QString path)
{
    QStandardItem* root = m_Private->m_StandardItemModel->invisibleRootItem();
    QStandardItem* item = new QStandardItem();
    item->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    MultimediaVariant variant;
    variant.m_Text = path;
    item->setData(qVariantFromValue(variant), Qt::DisplayRole);
    root->setChild(root->rowCount(), 0, item);
}

void MultimediaListView::setCurrentIndex(const QModelIndex &index)
{
    CustomListView::setCurrentIndex(index);
    emit onCurrentIndexChange(index);
}

MultimediaListViewPrivate::MultimediaListViewPrivate(MultimediaListView *parent)
    : m_Parent(parent)
{
    initialize();
}

MultimediaListViewPrivate::~MultimediaListViewPrivate()
{
}

void MultimediaListViewPrivate::initialize()
{
    m_CustomScrollBar = new CustomScrollBar(m_Parent);
    int width = 89 * g_Widget->widthScalabilityFactor();
    m_CustomScrollBar->setStyleSheet("QScrollBar:vertical{"
                                     "width:" + QString::number(width) + "px;"
                                                                         "background:rgba(0, 94, 187, 255);"
                                                                         "margin:0px, 0px, 0px, 0px;"
                                                                         "padding-top:0px;"
                                                                         "padding-bottom:0px;"
                                                                         "}"
                                                                         "QScrollBar::handle:vertical{"
                                                                         "width:" + QString::number(width) + "px;"
                                                                                                             "background:rgba(158, 158, 47, 255);"
                                                                                                             "min-height:" + QString::number(width) + "px;"
                                                                                                                                                      "}"
                                                                                                                                                      "QScrollBar::handle:vertical:pressed{"
                                                                                                                                                      "width:" + QString::number(width) + "px;"
                                                                                                                                                                                          "background:rgba(158, 158, 47, 255);"
                                                                                                                                                                                          "}"
                                                                                                                                                                                          "QScrollBar::handle:vertical:disabled{"
                                                                                                                                                                                          "width:" + QString::number(width) + "px;"
                                                                                                                                                                                                                              "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                                                              "}"
                                                                                                                                                                                                                              "QScrollBar::add-line:vertical{"
                                                                                                                                                                                                                              "height:0px;"
                                                                                                                                                                                                                              "subcontrol-position:bottom;"
                                                                                                                                                                                                                              "}"
                                                                                                                                                                                                                              "QScrollBar::sub-line:vertical{"
                                                                                                                                                                                                                              "height:0px;"
                                                                                                                                                                                                                              "subcontrol-position:top;"
                                                                                                                                                                                                                              "}"
                                                                                                                                                                                                                              "QScrollBar::add-page:vertical{"
                                                                                                                                                                                                                              "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                                                              "}"
                                                                                                                                                                                                                              "QScrollBar::sub-page:vertical{"
                                                                                                                                                                                                                              "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                                                              "}");
    m_StandardItemModel = new QStandardItemModel(m_Parent);
    m_MultimediaDelegate = new MultimediaDelegate(m_Parent);
    m_Parent->setVerticalScrollBar(m_CustomScrollBar);
    m_Parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_Parent->setItemDelegate(m_MultimediaDelegate);
    m_Parent->setModel(m_StandardItemModel);
}

MultimediaVariant::MultimediaVariant()
{
    m_Text.clear();
}

MultimediaVariant::~MultimediaVariant()
{
}

MultimediaDelegate::MultimediaDelegate(QWidget *widget)
    : CustomItemDelegate(widget)
{
    QString path(QString(":/Images/Resources/Images/MultimediaListViewCheck"));
    if (QFile(path + QString(".png")).exists()) {
        m_CheckPixmap.reset(new QPixmap(path + QString(".png")));
    }
#ifdef SVG
    else if (QFile(path + QString(".svg")).exists()) {
        m_CheckSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
#endif
}

MultimediaDelegate::~MultimediaDelegate()
{
}

void MultimediaDelegate::mousePressEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::mouseMoveEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::mouseReleaseEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    //    qDebug() << "MultimediaDelegate::paint" << option.rect << option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0);
    painter->fillRect(option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0), UserInterfaceUtility::listViewItemBrush());
    MultimediaVariant variant = qVariantValue<MultimediaVariant>(index.data(Qt::DisplayRole));
    QFont font;
    font.setPointSize(20 *g_Widget->widthScalabilityFactor());
    painter->setFont(font);
    QString text = QString::number(index.row() + 1) + QString(". ") + variant.m_Text;
    QRect textRect = option.rect.adjusted(75 * g_Widget->widthScalabilityFactor(), 0, -75 * g_Widget->widthScalabilityFactor(), 0);
    QFontMetrics fontMetrics(font);
    text = fontMetrics.elidedText(text, Qt::ElideRight, textRect.width());
    if (m_CurrentIndex == index) {
        if (!m_CheckPixmap.isNull()) {
            painter->drawPixmap(QRect(17 * g_Widget->widthScalabilityFactor(),
                                      option.rect.y() + (option.rect.height() - m_CheckPixmap->height() * g_Widget->heightScalabilityFactor()) * 0.5,
                                      m_CheckPixmap->width() * g_Widget->widthScalabilityFactor(), m_CheckPixmap->height() * g_Widget->heightScalabilityFactor()), *m_CheckPixmap);
        }
#ifdef SVG
        else if (!m_CheckSvg.isNull()) {
            m_CheckSvg->render(painter, QRect(17 * g_Widget->widthScalabilityFactor(),
                                              option.rect.y() + (option.rect.height() - m_CheckSvg->defaultSize().height()) * 0.5 * g_Widget->heightScalabilityFactor(),
                                              m_CheckSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                              m_CheckSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
        }
#endif
    }
    if (m_PressIndex == index) {
        painter->setPen(QColor(158, 158, 47, 255));
    } else {
        painter->setPen(Qt::white);
    }
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    painter->setPen(UserInterfaceUtility::customBlackColor());
    painter->drawLine(QPoint(0, option.rect.y() + option.rect.height() - 1), QPoint(option.rect.width() - 17 * g_Widget->widthScalabilityFactor(), option.rect.y() + option.rect.height() - 1));
    painter->restore();
}

void MultimediaDelegate::onCurrentIndexChange(const QModelIndex &index)
{
    m_CurrentIndex = index;
}

void MultimediaDelegate::onPressIndexChanged(const QModelIndex &index)
{
    m_PressIndex = index;
}
