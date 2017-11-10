#include "EventEngine.h"
#include <QList>

class EventEnginePrivate
{
    Q_DISABLE_COPY(EventEnginePrivate)
public:
    explicit EventEnginePrivate(EventEngine* parent);
    ~EventEnginePrivate();
    QList<QObject*> m_AttachList;
private:
    EventEngine* m_Parent = NULL;
};

void EventEngine::attachCustomEvent(QObject *receive)
{
    if (NULL != receive) {
        if (!m_Private->m_AttachList.contains(receive)) {
            m_Private->m_AttachList.append(receive);
            qDebug() << "attachCustomEvent" << m_Private->m_AttachList.size() << receive;
        }
    }
}

void EventEngine::detachCustomEvent(QObject *receive)
{
    if (NULL != receive) {
        if (m_Private->m_AttachList.contains(receive)) {
            m_Private->m_AttachList.removeOne(receive);
        }
    }
}

void EventEngine::sendCustomEvent(QEvent& event)
{
    for (int i = 0; i < m_Private->m_AttachList.size(); ++i) {
        if (NULL != m_Private->m_AttachList.at(i)) {
            qDebug() << "sendEvent" << m_Private->m_AttachList.at(i) << m_Private->m_AttachList.size() << i;
            QCoreApplication::sendEvent(m_Private->m_AttachList.at(i), &event);
        }
    }
}

EventEngine::EventEngine()
    : m_Private(new EventEnginePrivate(this))
{
}

EventEngine::~EventEngine()
{
}

EventEnginePrivate::EventEnginePrivate(EventEngine *parent)
    : m_Parent(parent)
{
    m_AttachList.clear();
}

EventEnginePrivate::~EventEnginePrivate()
{
    m_AttachList.clear();
}
