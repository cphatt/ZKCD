#include "SDDiskVideoListViewWidget.h"
#include "MessageBox.h"
#include "MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "BmpButton.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include <QVariant>
#include <QPainter>
#include <QDomDocument>

namespace SourceString {
static const QString No_Video_Resource = QString(QObject::tr("No Video Resource..."));
}

class SDDiskVideoListViewWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskVideoListViewWidgetPrivate)
public:
    explicit SDDiskVideoListViewWidgetPrivate(SDDiskVideoListViewWidget* parent);
    ~SDDiskVideoListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_VideoListView = NULL;
    MessageBox* m_SDDiskVideoMessageBox = NULL;
    BmpButton* m_ListBtn = NULL;
    bool m_RequestShow = false;
    bool m_RequestToSDDiskWidget = false;
    int m_Elapsed = 0;
    int m_LastIndex = -1;
    bool m_SDMultimedia = false;
private:
    SDDiskVideoListViewWidget* m_Parent = NULL;
};

SDDiskVideoListViewWidget::SDDiskVideoListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SDDiskVideoListViewWidgetPrivate(this))
{
    setVisible(false);
}

SDDiskVideoListViewWidget::~SDDiskVideoListViewWidget()
{
}

void SDDiskVideoListViewWidget::showEvent(QShowEvent *event)
{
    if (m_Private->m_SDMultimedia) {
        m_Private->m_SDMultimedia = false;
        if (-1 != m_Private->m_LastIndex) {
            onVideoListViewItemRelease(m_Private->m_LastIndex);
        }
    }
}

void SDDiskVideoListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 223, g_Widget->baseWindowHeight(), m_Private->m_SDDiskVideoMessageBox);
    g_Widget->geometryFit(278 - 278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Private->m_VideoListView);
}

void SDDiskVideoListViewWidget::paintEvent(QPaintEvent *event)
{
}

void SDDiskVideoListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::VideoToolBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (NULL != ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (NULL != ptr->m_Data->value<QWidget*>())) {
            if (m_Private->m_ListBtn != ptr->m_Data->value<QWidget*>()) {
                m_Private->m_RequestToSDDiskWidget = false;
                m_Private->m_ListBtn->setVisible(false);
            }
        }
        break;
    }
    case CustomEventType::SDMultimediaType: {
        if (m_Private->m_SDMultimedia) {
            g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::RequestShow);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void SDDiskVideoListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "SDDiskVideoListViewWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_SDDiskVideo: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskMusic: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
            setVisible(false);
        }
        break;
    }
    case Widget::T_Video:
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            if (isVisible()
                    || !m_Private->m_ListBtn->isHidden()) {
                m_Private->m_RequestToSDDiskWidget = true;
            }
        }
        break;
    }
    case Widget::T_SDDisk: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
            if (!isHidden()
                    && (!m_Private->m_SDMultimedia)) {
                g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::Show);
            }
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
        }
        break;
    }
    }
}

void SDDiskVideoListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "SDDiskVideoListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_LastIndex = -1;
            m_Private->m_SDMultimedia = false;
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            m_Private->m_ListBtn->setVisible(false);
            if (m_Private->m_RequestToSDDiskWidget) {
                g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
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

void SDDiskVideoListViewWidget::onVideoPlayerFileNames(const int type, const QString& xml)
{
    if (DWT_SDDisk == type) {
        //        qDebug() << "SDDiskVideoListViewWidget::onVideoPlayerFileNames" << type << xml;
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
                        if (QString("SDFileNames") == element.tagName()) {
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
                            qDebug() << __FUNCTION__ << "nodeList.length()" << nodeList.length();
                            if (0 == nodeList.length()) {
                                m_Private->m_SDDiskVideoMessageBox->setText(SourceString::No_Video_Resource);
                                m_Private->m_SDDiskVideoMessageBox->setVisible(true);
                                m_Private->m_VideoListView->setVisible(false);
                            } else {
                                m_Private->m_SDDiskVideoMessageBox->setVisible(false);
                                m_Private->m_VideoListView->setVisible(true);
                            }
                        } else if (QString("SDPersistant") == element.tagName()) {
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
                        } else if (QString("SDType") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            if (MT_Video == node.toElement().text().toInt()) {
                                                m_Private->m_SDMultimedia = true;
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

void SDDiskVideoListViewWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "SDDiskVideoListViewWidget::onVideoPlayerPlayStatus" << status;
    if (VPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::VideoToolBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
            g_Widget->geometryFit(1181 - ((1241 - 1181) / 2), (88 - 70) / 2 , 70, 70, m_Private->m_ListBtn);
        }
    } else if (VPPS_Exit == status) {
        m_Private->m_ListBtn->setVisible(false);
    }
}

void SDDiskVideoListViewWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << "SDDiskVideoListViewWidget::onVideoPlayerInformation" << index;
    if (DWT_SDDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_VideoListView->setCurrentIndex(m_Private->m_VideoListView->model()->index(index, 0, QModelIndex()));
    }
}

void SDDiskVideoListViewWidget::onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
    m_Private->m_Elapsed = elapsedTime;
}

void SDDiskVideoListViewWidget::onVideoListViewItemRelease(const int index)
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
    g_Multimedia->videoPlayerPlayListViewIndex(DWT_SDDisk, index, 0, 0, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor(), milleasmial);
}

void SDDiskVideoListViewWidget::onToolButtonRelease()
{
    g_Multimedia->videoPlayerSetPlayStatus(VPPS_SuspendToggle);
    g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::RequestShow);
}

SDDiskVideoListViewWidgetPrivate::SDDiskVideoListViewWidgetPrivate(SDDiskVideoListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

SDDiskVideoListViewWidgetPrivate::~SDDiskVideoListViewWidgetPrivate()
{
}

void SDDiskVideoListViewWidgetPrivate::initialize()
{
    m_SDDiskVideoMessageBox = new MessageBox(m_Parent);
    m_SDDiskVideoMessageBox->setAutoHide(false);
    m_SDDiskVideoMessageBox->hide();
    m_VideoListView = new MultimediaListView(m_Parent);
    m_VideoListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
}

void SDDiskVideoListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SDDiskVideoListViewWidgetPrivate::connectAllSlots()
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
