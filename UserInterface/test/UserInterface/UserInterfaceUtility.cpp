#include "UserInterfaceUtility.h"
#include <QColor>
#include <QTime>
#include <QDebug>

QTime UserInterfaceUtility::time;

QBrush UserInterfaceUtility::listViewItemBrush()
{
    return QBrush(QColor(0, 94, 187));
}

QColor UserInterfaceUtility::customBlackColor()
{
    return QColor(0, 0, 1);
}

QColor UserInterfaceUtility::videoColor()
{
    return QColor(0, 0, 0);
}

QColor UserInterfaceUtility::mainWidgetBackgroundColor()
{
    return QColor(16, 6, 119);
}

QColor UserInterfaceUtility::multimediaAlphaColor()
{
    return QColor(210, 210, 210, 180);
}

void UserInterfaceUtility::startTime()
{
    time.restart();
}

void UserInterfaceUtility::elapsed(const QString &str)
{
    qDebug() << "UserInterfaceUtility::elapsed" << time.elapsed() << str;
}
