#include "GeneralWidget.h"
#include "UserInterfaceUtility.h"
#include "AutoConnect.h"
#include "GeneralListView/GeneralListView.h"
#include "BmpButton.h"
#include "Setting.h"
#include "GeneralResetWidget/GeneralResetWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>

class GeneralWidgetPrivate
{
    Q_DISABLE_COPY(GeneralWidgetPrivate)
public:
    explicit GeneralWidgetPrivate(GeneralWidget* parent);
    ~GeneralWidgetPrivate();
    void initializeGeneralListView();
    void initializeGeneralResetWidget();
    void connectAllSlots();
    GeneralListView* m_GeneralListView = NULL;
    GeneralResetWidget* m_GeneralResetWidget = NULL;
private:
    GeneralWidget* m_Parent = NULL;
};

GeneralWidget::GeneralWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new GeneralWidgetPrivate(this))
{
    setVisible(true);
}

GeneralWidget::~GeneralWidget()
{
}

void GeneralWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
}

void GeneralWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::Show);
    if (NULL != m_Private) {
        m_Private->connectAllSlots();
    }
}

void GeneralWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "GeneralWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_SettingGeneral: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingLanguage:
    case Widget::T_SettingEffect:
    case Widget::T_SettingField:
    case Widget::T_SettingVersion: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void GeneralWidget::onGeneralListViewItemRelease(const int index)
{
    qDebug() << "GeneralWidget::onGeneralListViewItemRelease" << index;
    switch (index) {
    case 4: {
        if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
            this->parentWidget()->parentWidget()->setVisible(false);
            //        g_Setting->startCalibrate();
            system("ts_calibrate");
            system("reboot");
        }
        break;
    }
    case 5: {
        m_Private->initializeGeneralResetWidget();
        m_Private->m_GeneralResetWidget->setVisible(true);
        break;
    }
    default: {
        break;
    }
    }
}

GeneralWidgetPrivate::GeneralWidgetPrivate(GeneralWidget *parent)
    : m_Parent(parent)
{
    initializeGeneralListView();
}

GeneralWidgetPrivate::~GeneralWidgetPrivate()
{
}

void GeneralWidgetPrivate::initializeGeneralListView()
{
    if (NULL == m_GeneralListView) {
        m_GeneralListView = new GeneralListView(m_Parent);
    }
}

void GeneralWidgetPrivate::initializeGeneralResetWidget()
{
    if (NULL == m_GeneralResetWidget) {
        m_GeneralResetWidget = new GeneralResetWidget(m_Parent);
    }
}

void GeneralWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    if (NULL != m_GeneralListView) {
        QObject::connect(m_GeneralListView, SIGNAL(listViewItemRelease(const int)),
                         m_Parent,          SLOT(onGeneralListViewItemRelease(const int)),
                         type);
    }
}
