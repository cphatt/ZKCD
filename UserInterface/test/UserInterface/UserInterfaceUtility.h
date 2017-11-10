#ifndef USERINTERFACEUTILITY_H
#define USERINTERFACEUTILITY_H

#include <QObject>
#include <QBrush>

class UserInterfaceUtility
{
public:
    static QBrush listViewItemBrush();
    static QColor customBlackColor();
    static QColor videoColor();
    static QColor mainWidgetBackgroundColor();
    static QColor multimediaAlphaColor();
    static void startTime();
    static void elapsed(const QString &str);
private:
    UserInterfaceUtility();
    ~UserInterfaceUtility();
    UserInterfaceUtility(const UserInterfaceUtility &utility);
    UserInterfaceUtility& operator =(const UserInterfaceUtility &utility);
    static QTime time;
};

#endif // USERINTERFACEUTILITY_H
