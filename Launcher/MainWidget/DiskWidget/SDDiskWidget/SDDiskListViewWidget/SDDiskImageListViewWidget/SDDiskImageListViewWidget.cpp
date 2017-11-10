#include "SDDiskImageListViewWidget.h"
#include "MessageBox.h"
#include "MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterfaceUtility.h"
#include "BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "BmpButton.h"
#include "EventEngine.h"
#include "UserInterfaceUtility.h"
#include <QPainter>
#include <QDomDocument>

namespace SourceString {
static const QString No_Image_Resource = QString(QObject::tr("No Image Resource..."));
}

class SDDiskImageListViewWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskImageListViewWidgetPrivate)
public:
    explicit SDDiskImageListViewWidgetPrivate(SDDiskImageListViewWidget* parent);
    ~SDDiskImageListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_ImageListView = NULL;
    MessageBox* m_SDDiskImageMessageBox = NULL;
    BmpButton* m_ListBtn = NULL;
    bool m_RequestShow = false;
    bool m_RequestToSDDiskWidget = false;
    int m_LastIndex = -1;
    bool m_SDMultimedia = false;
private:
    SDDiskImageListViewWidget* m_Parent = NULL;
};

SDDiskImageListViewWidget::SDDiskImageListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SDDiskImageListViewWidgetPrivate(this))
{
    setVisible(false);
}

SDDiskImageListViewWidget::~SDDiskImageListViewWidget()
{
}

void SDDiskImageListViewWidget::showEvent(QShowEvent *event)
{
    if (m_Private->m_SDMultimedia) {
        m_Private->m_SDMultimedia = false;
        if (-1 != m_Private->m_LastIndex) {
            onImageListViewItemRelease(m_Private->m_LastIndex);
        }
    }
}

void SDDiskImageListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 223, g_Widget->baseWindowHeight(), m_Private->m_SDDiskImageMessageBox);
    g_Widget->geometryFit(278 - 278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Private->m_ImageListView);
}

void SDDiskImageListViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void SDDiskImageListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::ImageStatusWidgetAddChild: {
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
            g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::RequestShow);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void SDDiskImageListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "SDDiskImageListViewWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_SDDiskImage: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_SDDiskMusic:
    case Widget::T_SDDiskVideo:
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToSDDiskWidget = false;
            setVisible(false);
        }
        break;
    case Widget::T_Image:
    case Widget::T_ImageFullScreen: {
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
                g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::Show);
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

void SDDiskImageListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "SDDiskImageListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_LastIndex = -1;
            m_Private->m_SDMultimedia = false;
            m_Private->m_SDDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
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

void SDDiskImageListViewWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    if (IPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
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

void SDDiskImageListViewWidget::onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml)
{
    if (DWT_SDDisk == type) {
        //        qDebug() << "SDDiskImageListViewWidget::onImagePlayerFileNames" << type << xml;
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
                        if (QString("SDFileNames") == element.tagName()) {
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
                                m_Private->m_SDDiskImageMessageBox->setText(SourceString::No_Image_Resource);
                                m_Private->m_SDDiskImageMessageBox->setVisible(true);
                                m_Private->m_ImageListView->setVisible(false);
                            } else {
                                m_Private->m_SDDiskImageMessageBox->setVisible(false);
                                m_Private->m_ImageListView->setVisible(true);
                            }
                        } else if (QString("SDPersistant") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            int index = node.toElement().text().toInt();
                                            if (m_Private->m_ImageListView->model()->rowCount(QModelIndex()) > index) {
                                                m_Private->m_ImageListView->setCurrentIndex(m_Private->m_ImageListView->model()->index(index, 0, QModelIndex()));
                                                m_Private->m_LastIndex = index;
                                                qDebug() << "11m_Private->m_LastIndex" << m_Private->m_LastIndex;
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
                                            if (MT_Image == node.toElement().text().toInt()) {
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

void SDDiskImageListViewWidget::onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate)
{
    qDebug() << "SDDiskImageListViewWidget::onImagePlayerChange" << index;
    if (DWT_SDDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_ImageListView->setCurrentIndex(m_Private->m_ImageListView->model()->index(index, 0, QModelIndex()));
    }
}

void SDDiskImageListViewWidget::onImageListViewItemRelease(const int index)
{
    qDebug() << "SDDiskImageListViewWidget::onImageListViewItemRelease" << index;
    if (index == m_Private->m_LastIndex) {
        if (!m_Private->m_ListBtn->isHidden()) {
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::RequestShow);
            return ;
        }
    }
    m_Private->m_RequestShow = true;
    g_Multimedia->imagePlayerPlayListViewIndex(DWT_SDDisk, index);
}

void SDDiskImageListViewWidget::onListBtnRelease()
{
    g_Multimedia->imagePlayerSetPlayStatus(IPPS_SuspendToggle);
    g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::RequestShow);
}

SDDiskImageListViewWidgetPrivate::SDDiskImageListViewWidgetPrivate(SDDiskImageListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

SDDiskImageListViewWidgetPrivate::~SDDiskImageListViewWidgetPrivate()
{
}

void SDDiskImageListViewWidgetPrivate::initialize()
{
    m_SDDiskImageMessageBox = new MessageBox(m_Parent);
    m_SDDiskImageMessageBox->setAutoHide(false);
    m_SDDiskImageMessageBox->hide();
    m_ImageListView = new MultimediaListView(m_Parent);
    m_ImageListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListNormal"));
    m_ListBtn->hide();
}

void SDDiskImageListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SDDiskImageListViewWidgetPrivate::connectAllSlots()
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
