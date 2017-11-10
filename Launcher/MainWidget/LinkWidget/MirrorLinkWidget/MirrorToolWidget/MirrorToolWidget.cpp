#include "MirrorToolWidget.h"
#include "BmpButton.h"
#include "Widget.h"
#include <QPainter>

class MirrorToolWidgetPrivate
{
    Q_DISABLE_COPY(MirrorToolWidgetPrivate)
public:
    explicit MirrorToolWidgetPrivate(MirrorToolWidget* parent);
    ~MirrorToolWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpButton* m_BlueToothBtn = NULL;
    BmpButton* m_MenuBtn = NULL;
    BmpButton* m_CarBtn = NULL;
    BmpButton* m_HomeBtn = NULL;
    BmpButton* m_BackBtn = NULL;
private:
    MirrorToolWidget* m_Parent = NULL;
};

MirrorToolWidget::MirrorToolWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MirrorToolWidgetPrivate(this))
{
}

MirrorToolWidget::~MirrorToolWidget()
{
}

void MirrorToolWidget::resizeEvent(QResizeEvent *event)
{
    int width(40);
    int height(40);
    int distance((720 - height * 5) / (5 + 1));
    g_Widget->geometryFit(0, 0, width, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, (distance + height) * 0 + (distance - height) * 0.5, width, height, m_Private->m_BlueToothBtn);
    g_Widget->geometryFit(0, (distance + height) * 1 + (distance - height) * 0.5, width, height, m_Private->m_MenuBtn);
    g_Widget->geometryFit(0, (distance + height) * 2 + (distance - height) * 0.5, width, height, m_Private->m_HomeBtn);
    g_Widget->geometryFit(0, (distance + height) * 3 + (distance - height) * 0.5, width, height, m_Private->m_BackBtn);
    g_Widget->geometryFit(0, (distance + height) * 4 + (distance - height) * 0.5, width, height, m_Private->m_CarBtn);
    QWidget::resizeEvent(event);
}

void MirrorToolWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void MirrorToolWidget::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
}

bool MirrorToolWidget::event(QEvent *event)
{
    bool ret(false);
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::MouseButtonDblClick: {
        ret = true;
        break;
    }
    default: {
        ret = QWidget::event(event);
        break;
    }
    }
    return ret;
}

void MirrorToolWidget::onToolBtnRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if (ptr == m_Private->m_CarBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Car);
    } else if (ptr == m_Private->m_BackBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Back);
    } else if (ptr == m_Private->m_HomeBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Home);
    } else if (ptr == m_Private->m_MenuBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Menu);
    } else if (ptr == m_Private->m_BlueToothBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_BlueTooth);
    }
}

MirrorToolWidgetPrivate::MirrorToolWidgetPrivate(MirrorToolWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MirrorToolWidgetPrivate::~MirrorToolWidgetPrivate()
{
}

void MirrorToolWidgetPrivate::initialize()
{
    m_BlueToothBtn = new BmpButton(m_Parent);
    m_BlueToothBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorBlueToothNormal"));
    m_BlueToothBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorBlueToothNormal"));
    m_BlueToothBtn->setVisible(true);
    m_CarBtn = new BmpButton(m_Parent);
    m_CarBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetCarBtnNormal"));
    m_CarBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetCarBtnNormal"));
    m_CarBtn->setVisible(true);
    m_HomeBtn = new BmpButton(m_Parent);
    m_HomeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetHomeBtnNormal"));
    m_HomeBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetHomeBtnNormal"));
    m_HomeBtn->setVisible(true);
    m_BackBtn = new BmpButton(m_Parent);
    m_BackBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetBackBtnNormal"));
    m_BackBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetBackBtnNormal"));
    m_BackBtn->setVisible(true);
    m_MenuBtn = new BmpButton(m_Parent);
    m_MenuBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetMenuBtnNormal"));
    m_MenuBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetMenuBtnNormal"));
    m_MenuBtn->setVisible(true);
}

void MirrorToolWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_CarBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_BackBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_HomeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_MenuBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_BlueToothBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,       SLOT(onToolBtnRelease()),
                     type);
}
