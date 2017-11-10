#include "CustomListView.h"
#include "AutoConnect.h"
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPoint>
#include <QTime>

static int deaccelerate(const int &speed, int a = 1, int max = 93)
{
    int y = qBound(-max, speed, max);
    y = (y == 0) ? y : (y > 0) ? qMax(0, y - a) : qMin(0, y + a);
    return y;
}

class CustomListViewPrivate
{
public:
    typedef enum {
        Steady = 0,
        Pressed = 1,
        ManualScroll = 2,
        AutoScroll = 3,
        Stop = 4,
    } State;
    explicit CustomListViewPrivate(CustomListView* parent);
    ~CustomListViewPrivate();
    QPoint m_StartMovePoint;
    unsigned int m_Threshold;
    bool m_Filter;
    State m_State;
    int threshold;
    int pressPos;
    int offset;
    int delta;
    int speed;
    QTime timeStamp;
private:
    CustomListView* m_Parent;
};

CustomListView::CustomListView(QWidget *parent)
    : QListView(parent)
    , m_Private(new CustomListViewPrivate(this))
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    setPalette(palette);
    setFrameShape(QListView::NoFrame);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setEditTriggers(QListView::NoEditTriggers);
    setSpacing(0);
    setDragEnabled(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionBehavior(QListView::SelectRows);
    setSelectionMode(QListView::SingleSelection);
}

CustomListView::~CustomListView()
{
}

void CustomListView::setItemDelegate(QAbstractItemDelegate *delegate)
{
    connectSignalAndSlotByNamesake(this, delegate);
    QListView::setItemDelegate(delegate);
}

bool CustomListView::event(QEvent *event)
{
    bool ret(true);
    switch (event->type()) {
#ifndef gcc
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove: {
        ret = QListView::event(event);
        break;
    }
#endif
    default: {
        ret = QListView::event(event);
        break;
    }
    }
    return ret;
}

void CustomListView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "CustomListView::mousePressEvent";
    switch (m_Private->m_State) {
    case CustomListViewPrivate::Steady: {
        m_Private->m_State = CustomListViewPrivate::Pressed;
        m_Private->pressPos = event->pos().y();
        m_Private->m_StartMovePoint = event->pos();
        m_Private->m_Filter = false;
        QModelIndex modelIndex = indexAt(event->pos());
        if (modelIndex.isValid()) {
            emit onPressIndexChanged(modelIndex);
            update(modelIndex);
        }
        break;
    }
    case CustomListViewPrivate::AutoScroll: {
        m_Private->m_State = CustomListViewPrivate::Stop;
        m_Private->speed = 0;
        m_Private->pressPos = event->pos().y();
        m_Private->offset = verticalOffset();
        break;
    }
    default: {
        break;
    }
    }
    QListView::mousePressEvent(event);
}

void CustomListView::mouseMoveEvent(QMouseEvent *event)
{
    int delta;
    switch (m_Private->m_State) {
    case CustomListViewPrivate::Pressed:
    case CustomListViewPrivate::Stop: {
        delta = event->pos().y() - m_Private->pressPos;
        if (delta < qAbs(m_Private->threshold)) {
            m_Private->timeStamp = QTime::currentTime();
            m_Private->m_State = CustomListViewPrivate::ManualScroll;
            m_Private->delta = 0;
            m_Private->pressPos = event->pos().y();
            emit onPressIndexChanged(QModelIndex());
        }
        break;
    }
    case CustomListViewPrivate::ManualScroll: {
        delta = event->pos().y() - m_Private->pressPos;
        verticalScrollBar()->setValue(m_Private->offset - delta);
        if (m_Private->timeStamp.elapsed() > 100) {
            m_Private->timeStamp = QTime::currentTime();
            m_Private->speed = delta - m_Private->delta;
            m_Private->delta = delta;
        }
        break;
    }
    default: {
        break;
    }
    }
    //    QPoint relativePos = m_Private->m_StartMovePoint - event->pos();
    //    int deltaEnd = event->pos().y() - m_Private->m_StartMovePoint.y();
    //    if (m_Private->m_Filter) {
    //        m_Private->m_StartMovePoint = event->pos();
    //        verticalScrollBar()->setValue(verticalOffset() + relativePos.y());
    //    } else if ((qAbs(deltaEnd) > m_Private->m_Threshold)) {
    //        emit onPressIndexChanged(QModelIndex());
    //        m_Private->m_Filter = true;
    //        m_Private->m_StartMovePoint = event->pos();
    //    }
    //    QListView::mouseReleaseEvent(event);
}

void CustomListView::mouseReleaseEvent(QMouseEvent *event)
{
    int delta;
    switch (m_Private->m_State) {
    case CustomListViewPrivate::Pressed: {
        m_Private->m_State = CustomListViewPrivate::Steady;
        QModelIndex modelIndex = indexAt(event->pos());
        if (modelIndex.isValid()) {
            emit listViewItemRelease(modelIndex.row());
        }
        break;
    }
    case CustomListViewPrivate::ManualScroll:
        qDebug() << "FlickablePrivate::ManualScroll";
        event->accept();
        delta = event->pos().y() - m_Private->pressPos;
        if (m_Private->timeStamp.elapsed() > 100) {
            m_Private->timeStamp = QTime::currentTime();
            m_Private->speed = delta - m_Private->delta;
            m_Private->delta = delta;
        }
        m_Private->offset = verticalOffset();
        m_Private->pressPos = event->pos().y();
        qDebug() << "d->speed1" << m_Private->speed;
        if (0 == m_Private->speed) {
            m_Private->m_State = CustomListViewPrivate::Steady;
        } else {
            m_Private->speed /= 8;
            qDebug() << "d->speed2" << m_Private->speed;
            m_Private->m_State = CustomListViewPrivate::AutoScroll;
            startTimer(50);
        }
        break;

    case CustomListViewPrivate::Stop:
        m_Private->m_State = CustomListViewPrivate::Steady;
        m_Private->offset = verticalOffset();
        break;

    default:
        break;
    }
    //    if (!m_Private->m_Filter) {
    //        QModelIndex modelIndex = indexAt(event->pos());
    //        if (modelIndex.isValid()) {
    //            emit listViewItemRelease(modelIndex.row());
    //        }
    //    }
    //    emit onPressIndexChanged(QModelIndex());
    //    m_Private->m_Filter = false;
    //    QListView::mouseReleaseEvent(event);
}

void CustomListView::timerEvent(QTimerEvent *event)
{
    if (m_Private->m_State == CustomListViewPrivate:: AutoScroll) {
        m_Private->speed = deaccelerate(m_Private->speed);
        qDebug() << __FUNCTION__ << m_Private->speed;
        verticalScrollBar()->setValue(m_Private->offset - m_Private->speed);
        m_Private->offset = verticalOffset();
        if (0 == m_Private->speed) {
            m_Private->m_State = CustomListViewPrivate::Steady;
            killTimer(event->timerId());
        }
    }
}

CustomListViewPrivate::CustomListViewPrivate(CustomListView *parent)
    : m_Parent(parent)
{
    m_State = Steady;
    threshold = 10;//从鼠标点击位置拖动偏离10才开始移动界面
    timeStamp = QTime::currentTime();
    m_StartMovePoint = QPoint(0, 0);
    m_Threshold = 10;
    m_Filter = false;
}

CustomListViewPrivate::~CustomListViewPrivate()
{
}
