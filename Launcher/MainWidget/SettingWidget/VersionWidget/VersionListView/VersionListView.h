#ifndef VERSIONLISTVIEW_H
#define VERSIONLISTVIEW_H

#include "CustomListView.h"
#include <QScopedPointer>

class VersionListViewPrivate;
class VersionListView : protected CustomListView
{
    Q_OBJECT
    Q_DISABLE_COPY(VersionListView)
public:
    explicit VersionListView(QWidget* parent = NULL);
    ~VersionListView();
private:
    friend class VersionListViewPrivate;
    QScopedPointer<VersionListViewPrivate> m_Private;
};

#endif // VERSIONLISTVIEW_H
