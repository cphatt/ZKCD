#include "USBDiskVideoListViewWidget.h"
#include "MessageBox.h"
#include "MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "BmpButton.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QDomDocument>

namespace SourceString {
static const QString No_Video_Resource = QString(QObject::tr("No Video Resource..."));
}

class USBDiskVideoListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskVideoListViewWidgetPrivate)
public:
    explicit USBDiskVideoListViewWidgetPrivate(USBDiskVideoListViewWidget* parent);
    ~USBDiskVideoListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_VideoListView = NULL;
    MessageBox* m_USBDiskVideoMessageBox = NULL;
    BmpButton* m_ListBtn = NULL;
    bool m_RequestShow = false;
    bool m_RequestToUSBDiskWidget = false;
    int m_Elapsed = 0;
    int m_LastIndex = -1;
    bool m_USBMultimedia = false;
private:
    USBDiskVideoListViewWidget* m_Parent = NULL;
};

USBDiskVideoListViewWidget::USBDiskVideoListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new USBDiskVideoListViewWidgetPrivate(this))
{
    setVisible(false);
}

USBDiskVideoListViewWidget::~USBDiskVideoListViewWidget()
{
}

void USBDiskVideoListViewWidget::showEvent(QShowEvent *event)
{
    if (m_Private->m_USBMultimedia) {
        m_Private->m_USBMultimedia = false;
        if (-1 != m_Private->m_LastIndex) {
            onVideoListViewItemRelease(m_Private->m_LastIndex);
        }
    }
}

void USBDiskVideoListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 223, g_Widget->baseWindowHeight(), m_Private->m_USBDiskVideoMessageBox);
    g_Widget->geometryFit(278 - 278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Private->m_VideoListView);
    QWidget::resizeEvent(event);
}

void USBDiskVideoListViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void USBDiskVideoListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::VideoToolBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            if (m_Private->m_ListBtn != ptr->m_Data->value<QWidget*>()) {
                m_Private->m_RequestToUSBDiskWidget = false;
                m_Private->m_ListBtn->setVisible(false);
            }
        }
        break;
    }
    case CustomEventType::USBMultimediaType: {
        if (m_Private->m_USBMultimedia) {
            g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::RequestShow);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void USBDiskVideoListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_USBDiskVideo: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskMusic: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(false);
        }
        break;
    }
    case Widget::T_Video:
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            if (isVisible()
                    || !m_Private->m_ListBtn->isHidden()) {
                m_Private->m_RequestToUSBDiskWidget = true;
            }
        }
        break;
    }
    case Widget::T_USBDisk: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            if (!isHidden()
                    && (!m_Private->m_USBMultimedia)) {
                g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::Show);
            }
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
        }
        break;
    }
    }
}

void USBDiskVideoListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskVideoListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBMultimedia = false;
            m_Private->m_LastIndex = -1;
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            m_Private->m_ListBtn->setVisible(false);
            if (m_Private->m_RequestToUSBDiskWidget) {
                g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::Show);
            }
            setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerFileNames(const int type, const QString& xml)
{
    if (DWT_USBDisk == type) {
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("VideoPlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("USBFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_VideoListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_VideoListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_USBDiskVideoMessageBox->setText(SourceString::No_Video_Resource);
                                m_Private->m_USBDiskVideoMessageBox->setVisible(true);
                                m_Private->m_VideoListView->setVisible(false);
                            } else {
                                m_Private->m_USBDiskVideoMessageBox->setVisible(false);
                                m_Private->m_VideoListView->setVisible(true);
                            }
                        } else if (QString("USBPersistant") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            int index = node.toElement().text().split(QChar('-')).at(0).toInt();
                                            m_Private->m_Elapsed = node.toElement().text().split(QChar('-')).at(1).toInt();
                                            if (m_Private->m_VideoListView->model()->rowCount(QModelIndex()) > index) {
                                                m_Private->m_VideoListView->setCurrentIndex(m_Private->m_VideoListView->model()->index(index, 0, QModelIndex()));
                                                m_Private->m_LastIndex = index;
                                            }
                                        }
                                    }
                                }
                            }
                        } else if (QString("USBType") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            if (MT_Video == node.toElement().text().toInt()) {
                                                m_Private->m_USBMultimedia = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                node = node.nextSibling();
            }
        }
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Start: {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::VideoToolBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(1191 + (1238 - 1191 - 70) * 0.5, (88 - 70) * 0.5, 70, 70, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
        }
        break;
    }
    case VPPS_Exit: {
        m_Private->m_ListBtn->setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << "USBDiskVideoListViewWidget::onVideoPlayerInformation" << index;
    if (DWT_USBDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_VideoListView->setCurrentIndex(m_Private->m_VideoListView->model()->index(index, 0, QModelIndex()));
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
    m_Private->m_Elapsed = elapsedTime;
}

void USBDiskVideoListViewWidget::onVideoListViewItemRelease(const int index)
{
    int milleasmial(0);
    if (index == m_Private->m_LastIndex) {
        if (!m_Private->m_ListBtn->isHidden()) {
            g_Multimedia->videoPlayerSetPlayStatus(VPPS_SuspendToggle);
            g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
            return ;
        }
        milleasmial = m_Private->m_Elapsed;
    }
    qDebug() << "USBDiskVideoListViewWidget::onVideoListViewItemRelease" << milleasmial << m_Private->m_Elapsed;
    m_Private->m_RequestShow = true;
    g_Multimedia->videoPlayerPlayListViewIndex(DWT_USBDisk, index, 0, 0, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor(), milleasmial);
}

void USBDiskVideoListViewWidget::onToolButtonRelease()
{
    g_Multimedia->videoPlayerSetPlayStatus(VPPS_SuspendToggle);
    g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::RequestShow);
}

USBDiskVideoListViewWidgetPrivate::USBDiskVideoListViewWidgetPrivate(USBDiskVideoListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

USBDiskVideoListViewWidgetPrivate::~USBDiskVideoListViewWidgetPrivate()
{
}

void USBDiskVideoListViewWidgetPrivate::initialize()
{
    m_USBDiskVideoMessageBox = new MessageBox(m_Parent);
    m_USBDiskVideoMessageBox->setAutoHide(false);
    m_USBDiskVideoMessageBox->hide();
    m_VideoListView = new MultimediaListView(m_Parent);
    m_VideoListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
}

void USBDiskVideoListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void USBDiskVideoListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_VideoListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onVideoListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
}
