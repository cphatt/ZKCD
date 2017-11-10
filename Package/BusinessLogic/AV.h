#ifndef AV_H
#define AV_H

#include "Setting.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class AVPrivate;
class AV : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AV)
#ifdef g_AV
#undef g_AV
#endif
#define g_AV (AV::instance())
public:
    inline static AV* instance() {
        static AV* av(new AV(qApp));
        return av;
    }
public slots:
    void startAV(const int type, const int width, const int height);
    //    void startAV(const AVType type, const int width, const int height);
    void stopAV(const int type);
    //    void stopAV(const AVType type);
signals:
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVStatus status);
private slots:
    void onAVStatusHandler(const int type, const int status);
private:
    explicit AV(QObject *parent = NULL);
    ~AV();
    void initializePrivate();
    friend class AVPrivate;
    QScopedPointer<AVPrivate> m_Private;
};

#endif // AV_H
