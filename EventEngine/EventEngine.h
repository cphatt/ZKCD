#ifndef CUSTOMEVENT_H
#define CUSTOMEVENT_H

#include "UserInterfaceUtility.h"
#include <QEvent>
#include <QCoreApplication>
#include <QScopedPointer>

class EventEnginePrivate;
class EventEngine
{
    Q_DISABLE_COPY(EventEngine)
#ifdef g_EventEngine
#undef g_EventEngine
#endif
#define g_EventEngine (EventEngine::instance())
public:
    inline static EventEngine* instance() {
        static EventEngine eventEngine;
        return &eventEngine;
    }
    template <class T>
    class CustomEvent : public QEvent {
    public:
        explicit CustomEvent(const QEvent::Type type, T* data = NULL)
            : QEvent(type)
            , m_Data(data) {
        }
        ~CustomEvent() {
            if (NULL != m_Data) {
                delete m_Data;
                m_Data = NULL;
            }
        }
        explicit CustomEvent(const CustomEvent& customEvent)
            : QEvent(customEvent.type())
            , m_Data(NULL) {
            if (NULL != customEvent.m_Data) {
                m_Data = new T(*customEvent.m_Data);
            }
        }
        CustomEvent& operator =(const CustomEvent& customEvent) {
            if (this == &customEvent) {
                return *this;
            } else {
                if (NULL != m_Data) {
                    delete m_Data;
                    m_Data = NULL;
                }
                if (NULL != customEvent.m_Data) {
                    m_Data = new T(*customEvent.m_Data);
                }
                return *this;
            }
        }
        T* m_Data;
    };
    void attachCustomEvent(QObject* receive);
    void detachCustomEvent(QObject* receive);
    void sendCustomEvent(QEvent& event);
private:
    EventEngine();
    ~EventEngine();
    friend class EventEnginePrivate;
    QScopedPointer<EventEnginePrivate> m_Private;
};

#endif // CUSTOMEVENT_H
