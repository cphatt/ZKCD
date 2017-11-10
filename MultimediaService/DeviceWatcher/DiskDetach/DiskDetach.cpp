#include "DiskDetach.h"
#include "UserInterfaceUtility.h"
#include <QTimer>
#include <QRegExp>

class DiskDetachPrivate
{
    Q_DISABLE_COPY(DiskDetachPrivate)
public:
    explicit DiskDetachPrivate(DiskDetach* parent);
    ~DiskDetachPrivate();
    void initialize();
    void connectAllSlots();
    bool regExpUSBPath(const QString& path);
    bool regExpSDPath(const QString& path);
    QTimer* m_USBTimer = NULL;
    QString m_USBPartition;
    QTimer* m_SDTimer = NULL;
    QString m_SDPartition;
    DiskDeviceWatcher* m_DiskDeviceWatcher = NULL;
private:
    DiskDetach* m_Parent = NULL;
};

DiskDetach::DiskDetach(QObject *parent)
    : QObject(parent)
    , m_Private(new DiskDetachPrivate(this))
{
}

DiskDetach::~DiskDetach()
{
}

void DiskDetach::onTimeout()
{
    QTimer* ptr = qobject_cast<QTimer*>(sender());
    if (ptr == m_Private->m_USBTimer) {
        qDebug() << "m_USBPartition->add" << m_Private->m_USBPartition;
        emit diskPartition(m_Private->m_USBPartition, DiskDeviceWatcher::A_Add);
    } else if (ptr == m_Private->m_SDTimer) {
        qDebug() << "m_SDPartition->add" << m_Private->m_SDPartition;
        emit diskPartition(m_Private->m_SDPartition, DiskDeviceWatcher::A_Add);
    }
}

void DiskDetach::onDiskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action)
{
    qDebug() << "DiskDetach::onDiskDeviceChange" << device << action << m_Private->m_USBPartition << m_Private->m_SDPartition << device << action;
    if (DiskDeviceWatcher::A_Add == action) {
        bool condition1(false);
        bool condition2(false);
        bool condition3(false);
        if (m_Private->regExpUSBPath(device)) {
            condition1 = m_Private->m_USBPartition.isEmpty();
            if (!condition1
                    && (device.length() > 0)) {
                condition2 = device.at(device.length() - 1).isNumber();
                condition3 = condition2 && (device.at(device.length() - 1) > QChar('0'));
            }
            if (condition1
                    || condition2
                    || condition3) {
                if ((condition1) || (m_Private->m_USBPartition.length() > 0)
                        && ((!m_Private->m_USBPartition.at(m_Private->m_USBPartition.length() - 1).isNumber())
                            || (m_Private->m_USBPartition.at(m_Private->m_USBPartition.length() - 1).isNumber()
                                && (!(m_Private->m_USBPartition.at(m_Private->m_USBPartition.length() - 1) > QChar('0')))))) {
                    m_Private->m_USBPartition = device;
                }
            }
            m_Private->m_USBTimer->start();
        } else if (m_Private->regExpSDPath(device)) {
            condition1 = m_Private->m_SDPartition.isEmpty();
            if (!condition1
                    && (device.length() > 0)) {
                condition2 = device.at(device.length() - 1).isNumber();
                condition3 = condition2 && (device.at(device.length() - 1) > QChar('0'));
            }
            if (condition1
                    || condition2
                    || condition3) {
                if ((condition1) || (m_Private->m_SDPartition.length() > 0)
                        && ((!m_Private->m_SDPartition.at(m_Private->m_SDPartition.length() - 1).isNumber())
                            || (m_Private->m_SDPartition.at(m_Private->m_SDPartition.length() - 1).isNumber()
                                && (!(m_Private->m_SDPartition.at(m_Private->m_SDPartition.length() - 1) > QChar('0')))))) {
                    m_Private->m_SDPartition = device;
                }
            }
            m_Private->m_SDTimer->start();
        }
    } else if (DiskDeviceWatcher::A_Remove == action) {
        if ((m_Private->regExpUSBPath(device))
                && (device == m_Private->m_USBPartition)) {
            m_Private->m_USBTimer->stop();
            emit diskPartition(m_Private->m_USBPartition, DiskDeviceWatcher::A_Remove);
            qDebug() << "m_Private->m_USBPartition->remove" << m_Private->m_USBPartition;
            m_Private->m_USBPartition.clear();
        } else if ((m_Private->regExpSDPath(device))
                   && (device == m_Private->m_SDPartition)) {
            m_Private->m_SDTimer->stop();
            emit diskPartition(m_Private->m_SDPartition, DiskDeviceWatcher::A_Remove);
            qDebug() << "m_Private->m_SDPartition->remove" << m_Private->m_SDPartition;
            m_Private->m_SDPartition.clear();
        }
    }
}

DiskDetachPrivate::DiskDetachPrivate(DiskDetach *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

DiskDetachPrivate::~DiskDetachPrivate()
{
}

void DiskDetachPrivate::initialize()
{
    m_USBTimer = new QTimer(m_Parent);
    m_USBTimer->setSingleShot(true);
    m_USBTimer->setInterval(55);
    m_SDTimer = new QTimer(m_Parent);
    m_SDTimer->setSingleShot(true);
    m_SDTimer->setInterval(55);
    m_DiskDeviceWatcher = new DiskDeviceWatcher(m_Parent);
}

void DiskDetachPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_DiskDeviceWatcher, SIGNAL(diskDeviceChange(const QString &, const DiskDeviceWatcher::Action)),
                     m_Parent,            SLOT(onDiskDeviceChange(const QString &, const DiskDeviceWatcher::Action)),
                     type);
    QObject::connect(m_USBTimer,  SIGNAL(timeout()),
                     m_Parent,    SLOT(onTimeout()),
                     type);
    QObject::connect(m_SDTimer,  SIGNAL(timeout()),
                     m_Parent,   SLOT(onTimeout()),
                     type);
}

bool DiskDetachPrivate::regExpUSBPath(const QString &path)
{
    //    QRegExp usbRegExp("^/dev/sd[a-z][0-9]{0,1}");
    //    return usbRegExp.exactMatch(path);
    return path.startsWith(QString("/dev/sd"));
}

bool DiskDetachPrivate::regExpSDPath(const QString &path)
{
    //    QRegExp sdRegExp("^/dev/mmcblk[0-9]p[0-9]");
    //    return sdRegExp.exactMatch(path);
    return path.startsWith(QString("/dev/mmcblk"));
}
