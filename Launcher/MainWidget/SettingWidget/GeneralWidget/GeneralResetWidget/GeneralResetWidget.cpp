#include "GeneralResetWidget.h"
#include "BusinessLogicUtility.h"
#include "EventEngine.h"
#include "Widget.h"
#include "BmpWidget.h"
#include "BmpButton.h"
#include "TextWidget.h"
#include "Audio.h"
#include "Setting.h"
#include "BT.h"
#include "Utility.h"
#include "Multimedia.h"
#include <QPainter>
#include <QEvent>

namespace SourceString {
static const QString ResetTip = QString(QObject::tr("Reset Device Will Delete History And Reboot!"));
static const QString Rebooting = QString(QObject::tr("Rebooting..."));
static const QString Confirm = QString(QObject::tr("Confirm"));
static const QString Cancel = QString(QObject::tr("Cancel"));
}

class GeneralResetWidgetPrivate
{
    Q_DISABLE_COPY(GeneralResetWidgetPrivate)
public:
    explicit GeneralResetWidgetPrivate(GeneralResetWidget* parent);
    ~GeneralResetWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background = NULL;
    TextWidget* m_TextWidget = NULL;
    BmpButton* m_ConfirmBtn = NULL;
    TextWidget* m_ConfirmText = NULL;
    BmpButton* m_CancelBtn = NULL;
    TextWidget* m_CancelText = NULL;
    BmpWidget* m_Loading = NULL;
private:
    GeneralResetWidget* m_Parent = NULL;
};

GeneralResetWidget::GeneralResetWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new GeneralResetWidgetPrivate(this))
{
}

GeneralResetWidget::~GeneralResetWidget()
{
}

void GeneralResetWidget::paintEvent(QPaintEvent *event)
{
#if defined(gcc)
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
#endif
    QWidget::paintEvent(event);
}

void GeneralResetWidget::resizeEvent(QResizeEvent *event)
{
    int width(853);
    int height(360);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    g_Widget->geometryFit((g_Widget->baseWindowWidth() - 278 - width) * 0.5, (626 - 73 - height) * 0.5, width, height, m_Private->m_Background);
    g_Widget->geometryFit((g_Widget->baseWindowWidth() - 278 - width) * 0.5, (626 - 73 - height) * 0.5, width, 240, m_Private->m_TextWidget);
    qDebug() << "m_Private->m_TextWidget" << m_Private->m_TextWidget->geometry();
    g_Widget->geometryFit((g_Widget->baseWindowWidth() - 278 - width) * 0.5 + width * 0.25 - 161 * 0.5, (626 - 73 - height) * 0.5 + 240, 161, 108, m_Private->m_ConfirmBtn);
    g_Widget->geometryFit(0, 0, 161, 108, m_Private->m_ConfirmText);
    g_Widget->geometryFit((g_Widget->baseWindowWidth() - 278 - width) * 0.5 + (width * 0.5) + width * 0.25 - 161 * 0.5, (626 - 73 - height) * 0.5 + 240, 161, 108, m_Private->m_CancelBtn);
    g_Widget->geometryFit(0, 0, 161, 108, m_Private->m_CancelText);
    g_Widget->geometryFit((g_Widget->baseWindowWidth() - 278 - 150) * 0.5, (626 - 73 - height) * 0.5 + 120 + (240 - 150) * 0.5, 150, 150, m_Private->m_Loading);
}

void GeneralResetWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    system("sync");
    system("reboot");
}

void GeneralResetWidget::onToolButtonRelease()
{
    qDebug() << "GeneralResetWidget::onToolButtonRelease";
    BmpButton* ptr = static_cast<BmpButton*>(sender());
    if (m_Private->m_ConfirmBtn == ptr) {
        grabMouse();
        m_Private->m_Loading->setVisible(true);
        m_Private->m_TextWidget->setText(SourceString::Rebooting);
        m_Private->m_CancelBtn->setVisible(false);
        m_Private->m_ConfirmBtn->setVisible(false);
        acquirePreemptiveResource(NULL, NULL);
        g_Audio->reqesetRest();
        g_Setting->reset();
        g_Multimedia->reset();
        g_BT->requestRest();
        startTimer(2222);
    } else if (m_Private->m_CancelBtn == ptr) {
        setVisible(false);
        qDebug() << "GeneralResetWidget::onToolButtonRelease m_Cancel";
    }
}

GeneralResetWidgetPrivate::GeneralResetWidgetPrivate(GeneralResetWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

GeneralResetWidgetPrivate::~GeneralResetWidgetPrivate()
{
}

void GeneralResetWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/MessageBackground"));
    m_Background->setVisible(true);
    m_TextWidget = new TextWidget(m_Parent);
    m_TextWidget->setText(SourceString::ResetTip);
    m_TextWidget->setVisible(true);
    m_ConfirmBtn = new BmpButton(m_Parent);
    m_ConfirmBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ConfirmBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ConfirmBtn->setVisible(true);
    m_ConfirmText = new TextWidget(m_ConfirmBtn);
    m_ConfirmText->setText(SourceString::Confirm);
    m_CancelBtn = new BmpButton(m_Parent);
    m_CancelBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_CancelBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_CancelBtn->setVisible(true);
    m_CancelText = new TextWidget(m_CancelBtn);
    m_CancelText->setText(SourceString::Cancel);
    m_Loading = new BmpWidget(m_Parent);
    m_Loading->setBackgroundBmpPath(QString(":/Images/Resources/Images/MultimediaLoadingBackground"));
    m_Loading->setVisible(false);
}

void GeneralResetWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_ConfirmBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_CancelBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
}
