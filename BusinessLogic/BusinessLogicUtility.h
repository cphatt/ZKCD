#ifndef BUSINESSLOGICUTILITY_H
#define BUSINESSLOGICUTILITY_H

#include "AutoConnect.h"
#include "EventEngine.h"
#include <QObject>
#include <QEvent>
#include <QScopedPointer>

namespace CustomEventType {
static const QEvent::Type MainWidgetShow = static_cast<QEvent::Type>(QEvent::User + 1);
static const QEvent::Type IdleWidgetStatus = static_cast<QEvent::Type>(MainWidgetShow + 1);
static const QEvent::Type MessageBoxWidgetAddChild = static_cast<QEvent::Type>(IdleWidgetStatus + 1);
static const QEvent::Type MessageBoxWidgetStatus = static_cast<QEvent::Type>(MessageBoxWidgetAddChild + 1);
static const QEvent::Type TabBarWidgetAddChild = static_cast<QEvent::Type>(MessageBoxWidgetStatus + 1);
static const QEvent::Type StatusBarWidgetAddChild = static_cast<QEvent::Type>(TabBarWidgetAddChild + 1);
static const QEvent::Type ImageStatusWidgetAddChild = static_cast<QEvent::Type>(StatusBarWidgetAddChild + 1);
static const QEvent::Type MusicWidgetAddChild = static_cast<QEvent::Type>(ImageStatusWidgetAddChild + 1);
static const QEvent::Type VideoToolBarWidgetAddChild = static_cast<QEvent::Type>(MusicWidgetAddChild + 1);
static const QEvent::Type LinkMessageWidgetAddChild = static_cast<QEvent::Type>(VideoToolBarWidgetAddChild + 1);
static const QEvent::Type FMWidgetStatus = static_cast<QEvent::Type>(LinkMessageWidgetAddChild + 1);
static const QEvent::Type IRWidgetStatus = static_cast<QEvent::Type>(FMWidgetStatus + 1);
static const QEvent::Type VolumeWidgetStatus = static_cast<QEvent::Type>(IRWidgetStatus + 1);
static const QEvent::Type SDMultimediaType = static_cast<QEvent::Type>(VolumeWidgetStatus + 1);
static const QEvent::Type USBMultimediaType = static_cast<QEvent::Type>(SDMultimediaType + 1);
}

class BusinessLogicUtilityPrivate;
class BusinessLogicUtility
{
    Q_DISABLE_COPY(BusinessLogicUtility)
#ifdef g_BusinessLogicUtility
#undef g_BusinessLogicUtility
#endif
#define g_BusinessLogicUtility (BusinessLogicUtility::instance())
public:
    inline static BusinessLogicUtility* instance() {
        static BusinessLogicUtility businessLogicUtility;
        return &businessLogicUtility;
    }
private:
    BusinessLogicUtility();
    ~BusinessLogicUtility();
    friend class BusinessLogicUtilityPrivate;
    QScopedPointer<BusinessLogicUtilityPrivate> m_Private;
};

#endif // BUSINESSLOGICUTILITY_H
