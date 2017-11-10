#include "USBDiskImageListViewWidget.h"
#include "MessageBox.h"
#include "MainWidget/DiskWidget/MultimediaListView.h"
#include "BmpButton.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskListViewWidget.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QDomDocument>

namespace SourceString {
static const QString No_Image_Resource = QString(QObject::tr("No Image Resource..."));
}

class USBDiskImageListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskImageListViewWidgetPrivate)
public:
    explicit USBDiskImageListViewWidgetPrivate(USBDiskImageListViewWidget* parent);
    ~USBDiskImageListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_ImageListView = NULL;
    MessageBox* m_USBDiskImageMessageBox = NULL;
    BmpButton* m_ListBtn = NULL;
    bool m_RequestShow = false;
    bool m_RequestToUSBDiskWidget = false;
    int m_LastIndex = -1;
    bool m_USBMultimedia = false;
private:
    USBDiskImageListViewWidget* m_Parent = NULL;
};

USBDiskImageListViewWidget::USBDiskImageListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new USBDiskImageListViewWidgetPrivate(this))
{
    setVisible(false);
}

USBDiskImageListViewWidget::~USBDiskImageListViewWidget()
{
}

void USBDiskImageListViewWidget::showEvent(QShowEvent *event)
{
    qDebug() << "USBDiskImageListViewWidget::showEvent" << m_Private->m_USBMultimedia << m_Private->m_LastIndex;
    if (m_Private->m_USBMultimedia) {
        m_Private->m_USBMultimedia = false;
        if (-1 != m_Private->m_LastIndex) {
            onImageListViewItemRelease(m_Private->m_LastIndex);
        }
    }
}

void USBDiskImageListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 223, g_Widget->baseWindowHeight(), m_Private->m_USBDiskImageMessageBox);
    g_Widget->geometryFit(278 - 278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Private->m_ImageListView);
}

void USBDiskImageListViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void USBDiskImageListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::ImageStatusWidgetAddChild: {
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
            g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::RequestShow);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void USBDiskImageListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "USBDiskImageListViewWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_USBDiskImage: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskMusic:
    case Widget::T_USBDiskVideo: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(false);
        }
        break;
    }
    case Widget::T_Image:
    case Widget::T_ImageFullScreen: {
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
                g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::Show);
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

void USBDiskImageListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskImageListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBMultimedia = false;
            m_Private->m_LastIndex = -1;
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
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

void USBDiskImageListViewWidget::onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml)
{
    if (DWT_USBDisk == type) {
        //        qDebug() << "USBDiskImageListViewWidget::onImagePlayerFileNames" << type << xml;
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("ImagePlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("USBFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_ImageListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_ImageListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_USBDiskImageMessageBox->setText(SourceString::No_Image_Resource);
                                m_Private->m_USBDiskImageMessageBox->setVisible(true);
                                m_Private->m_ImageListView->setVisible(false);
                            } else {
                                m_Private->m_USBDiskImageMessageBox->setVisible(false);
                                m_Private->m_ImageListView->setVisible(true);
                            }
                        } else if (QString("USBPersistant") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            int index = node.toElement().text().toInt();
                                            if (m_Private->m_ImageListView->model()->rowCount(QModelIndex()) > index) {
                                                m_Private->m_LastIndex = index;
                                                m_Private->m_ImageListView->setCurrentIndex(m_Private->m_ImageListView->model()->index(index, 0, QModelIndex()));
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
                                            if (MT_Image == node.toElement().text().toInt()) {
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

void USBDiskImageListViewWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "USBDiskImageListViewWidget::onImagePlayerPlayStatus" << status;
    if (IPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            m_Private->m_RequestToUSBDiskWidget = true;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::ImageStatusWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(1181 - ((1241 - 1181) / 2), (88 - 70) / 2 , 70, 70, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::RequestShow);
        }
    } else if (IPPS_Exit == status) {
        m_Private->m_ListBtn->setVisible(false);
    }
}

void USBDiskImageListViewWidget::onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate)
{
    qDebug() << "USBDiskImageListViewWidget::onImagePlayerChange" << index;
    if (DWT_USBDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_ImageListView->setCurrentIndex(m_Private->m_ImageListView->model()->index(index, 0, QModelIndex()));
    }
}

void USBDiskImageListViewWidget::onImageListViewItemRelease(const int index)
{
    qDebug() << "USBDiskImageListViewWidget::onImageListViewItemRelease" << index << sender();
    if (index == m_Private->m_LastIndex) {
        if (!m_Private->m_ListBtn->isHidden()) {
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::RequestShow);
            return ;
        }
    }
    m_Private->m_RequestShow = true;
    g_Multimedia->imagePlayerPlayListViewIndex(DWT_USBDisk, index);
}

void USBDiskImageListViewWidget::onListBtnRelease()
{
    qDebug() << "USBDiskImageListViewWidget::onListBtnRelease";
    g_Multimedia->imagePlayerSetPlayStatus(IPPS_SuspendToggle);
    g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::RequestShow);
}

USBDiskImageListViewWidgetPrivate::USBDiskImageListViewWidgetPrivate(USBDiskImageListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

USBDiskImageListViewWidgetPrivate::~USBDiskImageListViewWidgetPrivate()
{
}

void USBDiskImageListViewWidgetPrivate::initialize()
{
    m_USBDiskImageMessageBox = new MessageBox(m_Parent);
    m_USBDiskImageMessageBox->setAutoHide(false);
    m_USBDiskImageMessageBox->hide();
    m_ImageListView = new MultimediaListView(m_Parent);
    m_ImageListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListNormal"));
    m_ListBtn->hide();
}

void USBDiskImageListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void USBDiskImageListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_ImageListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onImageListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent,   SLOT(onListBtnRelease()),
                     type);
}
