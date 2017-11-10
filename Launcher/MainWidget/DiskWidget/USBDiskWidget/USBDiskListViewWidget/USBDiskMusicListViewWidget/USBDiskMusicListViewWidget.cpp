#include "USBDiskMusicListViewWidget.h"
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
static const QString No_Music_Resource = QString(QObject::tr("No Music Resource..."));
}

class USBDiskMusicListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskMusicListViewWidgetPrivate)
public:
    explicit USBDiskMusicListViewWidgetPrivate(USBDiskMusicListViewWidget* parent);
    ~USBDiskMusicListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_MusicListView = NULL;
    MessageBox* m_USBDiskMusicMessageBox = NULL;
    BmpButton* m_ListBtn = NULL;
    bool m_RequestShow = false;
    bool m_RequestToUSBDiskWidget = false;
    int m_Elapsed = 0;
    int m_LastIndex = -1;
    bool m_USBMultimedia = false;
private:
    USBDiskMusicListViewWidget* m_Parent = NULL;
};

USBDiskMusicListViewWidget::USBDiskMusicListViewWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new USBDiskMusicListViewWidgetPrivate(this))
{
    setVisible(false);
}

USBDiskMusicListViewWidget::~USBDiskMusicListViewWidget()
{
}

void USBDiskMusicListViewWidget::showEvent(QShowEvent *event)
{
    if (m_Private->m_USBMultimedia) {
        m_Private->m_USBMultimedia = false;
        if (-1 != m_Private->m_LastIndex) {
            onMusicListViewItemRelease(m_Private->m_LastIndex);
        }
    }
}

void USBDiskMusicListViewWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 223, g_Widget->baseWindowHeight(), m_Private->m_USBDiskMusicMessageBox);
    g_Widget->geometryFit(278 - 278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Private->m_MusicListView);
}

void USBDiskMusicListViewWidget::paintEvent(QPaintEvent *event)
{
}

void USBDiskMusicListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MusicWidgetAddChild: {
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
            g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::RequestShow);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void USBDiskMusicListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Back: {
        qDebug() << "USBDiskMusicListViewWidget::ontWidgetTypeChange" << type << status << isVisible() << m_Private->m_ListBtn->isVisible();
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        } else if (m_Private->m_ListBtn->isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_USBDiskMusic: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskVideo: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestToUSBDiskWidget = false;
            setVisible(false);
        }
        break;
    }
    case Widget::T_Music: {
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
                g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::Show);
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

void USBDiskMusicListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskMusicListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->clearListView();
            m_Private->m_MusicListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            if (isVisible()) {
                g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::Show);
            }
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBMultimedia = false;
            m_Private->m_LastIndex = -1;
            m_Private->m_USBDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->setVisible(false);
            m_Private->m_MusicListView->clearListView();
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

void USBDiskMusicListViewWidget::onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml)
{
    if (DWT_USBDisk == type) {
        qDebug() << "USBDiskMusicListViewWidget::onMusicPlayerFileNames" << type << xml;
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("MusicPlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("USBFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_MusicListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_MusicListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_USBDiskMusicMessageBox->setText(SourceString::No_Music_Resource);
                                m_Private->m_USBDiskMusicMessageBox->setVisible(true);
                                m_Private->m_MusicListView->setVisible(false);
                            } else {
                                m_Private->m_USBDiskMusicMessageBox->setVisible(false);
                                m_Private->m_MusicListView->setVisible(true);
                            }
                        } else if (QString("USBPersistant") == element.tagName()) {
                            QDomElement node = element.toElement();
                            if (node.isElement()) {
                                if (!node.toElement().isNull()) {
                                    if (node.isElement()) {
                                        if (!node.toElement().text().isEmpty()) {
                                            int index = node.toElement().text().split(QChar('-')).at(0).toInt();
                                            m_Private->m_Elapsed = node.toElement().text().split(QChar('-')).at(1).toInt();
                                            if (m_Private->m_MusicListView->model()->rowCount(QModelIndex()) > index) {
                                                m_Private->m_MusicListView->setCurrentIndex(m_Private->m_MusicListView->model()->index(index, 0, QModelIndex()));
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
                                            if (MT_Music == node.toElement().text().toInt()) {
                                                m_Private->m_USBMultimedia = true;
                                            } else if (MT_Idle == node.toElement().text().toInt()) {
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

void USBDiskMusicListViewWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "USBDiskMusicListViewWidget::onMusicPlayerPlayStatus" << status;
    if (MPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MusicWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(113 + (155 - 113 - 70) / 2, 548 + (602 - 548 - 70) * 0.5, 70, 70, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::RequestShow);
        }
    } else if (MPPS_Exit == status) {
        m_Private->m_ListBtn->setVisible(false);
    }
}

void USBDiskMusicListViewWidget::onMusicPlayerID3TagChange(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << "USBDiskMusicListViewWidget::onMusicPlayerID3TagChange" << index;
    if (DWT_USBDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_MusicListView->setCurrentIndex(m_Private->m_MusicListView->model()->index(index, 0, QModelIndex()));
    }
}

void USBDiskMusicListViewWidget::onMusicPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
    m_Private->m_Elapsed = elapsedTime;
}

void USBDiskMusicListViewWidget::onMusicListViewItemRelease(const int index)
{
    qWarning() << "USBDiskMusicListViewWidget" << sender();
    int elapsed(0);
    if (index == m_Private->m_LastIndex) {
        if (!m_Private->m_ListBtn->isHidden()) {
            g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::RequestShow);
            return ;
        }
        elapsed = m_Private->m_Elapsed;
    }
    m_Private->m_RequestShow = true;
    qWarning() << "m_Private->m_Milleasmial" << m_Private->m_Elapsed;
    qWarning() << "m_PrivateonMusicListViewItemRelease" << m_Private->m_ListBtn->isVisible() << m_Private->m_ListBtn->isHidden();
    g_Multimedia->musicPlayerPlayListViewIndex(DWT_USBDisk, index, elapsed);
}

void USBDiskMusicListViewWidget::onToolButtonRelease()
{
    g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::RequestShow);
}

USBDiskMusicListViewWidgetPrivate::USBDiskMusicListViewWidgetPrivate(USBDiskMusicListViewWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

USBDiskMusicListViewWidgetPrivate::~USBDiskMusicListViewWidgetPrivate()
{
}

void USBDiskMusicListViewWidgetPrivate::initialize()
{
    m_USBDiskMusicMessageBox = new MessageBox(m_Parent);
    m_USBDiskMusicMessageBox->setAutoHide(false);
    m_USBDiskMusicMessageBox->hide();
    m_MusicListView = new MultimediaListView(m_Parent);
    m_MusicListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetListNormal"));
}

void USBDiskMusicListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void USBDiskMusicListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_MusicListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onMusicListViewItemRelease(const int)),
                     type);
    QObject::connect(m_MusicListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onMusicListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn,   SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
}
