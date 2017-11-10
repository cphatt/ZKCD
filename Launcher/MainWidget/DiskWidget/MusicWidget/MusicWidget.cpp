#include "MusicWidget.h"
#include "Setting.h"
#include "UserInterfaceUtility.h"
#include "BmpButton.h"
#include "BmpWidget.h"
#include "Slider.h"
#include "TextWidget.h"
#include "MusicShortCutWidget/MusicShortCutWidget.h"
#include "MusicToolWidget/MusicToolWidget.h"
#include "MusicLoadingWidget/MusicLoadingWidget.h"
#include "EventEngine.h"
#include "AutoConnect.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

namespace SourceString {
static const QString Unsupport = QString(QObject::tr("Unsupport..."));
}

class MusicWidgetPrivate
{
    Q_DISABLE_COPY(MusicWidgetPrivate)
public:
    explicit MusicWidgetPrivate(MusicWidget *parent);
    ~MusicWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MusicToolWidget* m_MusicToolWidget = NULL;
    TextWidget* m_Unsupport = NULL;
    MusicLoadingWidget* m_MusicLoadingWidget = NULL;
    MusicShortCutWidget* m_MusicShortCutWidget = NULL;
private:
    MusicWidget* m_Parent = NULL;
};

MusicWidget::MusicWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MusicWidgetPrivate(this))
{
}

MusicWidget::~MusicWidget()
{
}

void MusicWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(734, 255, 970 - 734, 306 - 255, m_Private->m_Unsupport);
}

void MusicWidget::paintEvent(QPaintEvent *event)
{
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.drawPixmap(QRect(0, itemHeight * 2, 250, 250), m_Private->m_Conver);
    //    painter.drawRect(QRect(0, itemHeight * 2, 250, 250));
}

void MusicWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "MusicWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Music: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    default : {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    }
}

void MusicWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    switch (status) {
    case MPPS_Unsupport: {
        m_Private->m_Unsupport->setVisible(true);
        break;
    }
    case MPPS_Start: {
        m_Private->m_Unsupport->setVisible(false);
//        setVisible(true);
        break;
    }
    case MPPS_Play: {
//        setVisible(true);
        break;
    }
    case MPPS_Pause:
    case MPPS_Stop: {
//        setVisible(true);
        break;
    }
    default : {
        break;
    }
    }
}

MusicWidgetPrivate::MusicWidgetPrivate(MusicWidget *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MusicWidgetPrivate::~MusicWidgetPrivate()
{
}

void MusicWidgetPrivate::initialize()
{
    m_MusicToolWidget = new MusicToolWidget(m_Parent);
    m_Unsupport = new TextWidget(m_Parent);
    m_Unsupport->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_Unsupport->setText(SourceString::Unsupport);
    m_Unsupport->setVisible(false);
    m_MusicLoadingWidget = new MusicLoadingWidget(m_Parent);
    m_MusicShortCutWidget = new MusicShortCutWidget(m_Parent);
}

void MusicWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
