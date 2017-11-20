/****************************************************************************
** Meta object code from reading C++ file 'AudioServiceProxy.h'
**
** Created: Mon Nov 20 16:06:09 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AudioService/AudioServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerAudioManagerInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   38,   37,   37, 0x05,
      64,   59,   37,   37, 0x05,
      85,   80,   37,   37, 0x05,
     101,   59,   37,   37, 0x05,
     129,  117,   37,   37, 0x05,
     161,  153,   37,   37, 0x05,

 // slots: signature, parameters, type, tag, flags
     217,  210,  190,   37, 0x0a,
     241,   37,  190,   37, 0x0a,
     279,  210,  255,   37, 0x0a,
     303,   37,  190,   37, 0x0a,
     327,   37,  190,   37, 0x0a,
     345,   80,  190,   37, 0x0a,
     364,   37,  190,   37, 0x0a,
     382,   37,  190,   37, 0x0a,
     406,   59,  190,   37, 0x0a,
     425,   38,  190,   37, 0x0a,
     456,  449,  190,   37, 0x0a,
     478,   37,  190,   37, 0x0a,
     493,   37,  190,   37, 0x0a,
     511,   37,  190,   37, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerAudioManagerInterface[] = {
    "LocalDbusServerAudioManagerInterface\0"
    "\0freq\0onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "mode\0onIRChange(int)\0onIRIsOpen(int)\0"
    "type,volume\0onVolumeChange(int,int)\0"
    "min,max\0onVolumeRangeChange(int,int)\0"
    "QDBusPendingReply<>\0source\0"
    "releaseAudioSource(int)\0reqesetRest()\0"
    "QDBusPendingReply<bool>\0requestAudioSource(int)\0"
    "requestDecreaseVolume()\0requestFMToggle()\0"
    "requestIRMode(int)\0requestIRToggle()\0"
    "requestIncreaseVolume()\0requestOpenFM(int)\0"
    "requestSetFreqency(int)\0volume\0"
    "requestSetVolume(int)\0requestStart()\0"
    "requsetIsOpenFM()\0synchronize()\0"
};

const QMetaObject LocalDbusServerAudioManagerInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerAudioManagerInterface,
      qt_meta_data_LocalDbusServerAudioManagerInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerAudioManagerInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerAudioManagerInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerAudioManagerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerAudioManagerInterface))
        return static_cast<void*>(const_cast< LocalDbusServerAudioManagerInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerAudioManagerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onIRChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onIRIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: onVolumeRangeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: { QDBusPendingReply<> _r = releaseAudioSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 7: { QDBusPendingReply<> _r = reqesetRest();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 8: { QDBusPendingReply<bool> _r = requestAudioSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<bool>*>(_a[0]) = _r; }  break;
        case 9: { QDBusPendingReply<> _r = requestDecreaseVolume();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 10: { QDBusPendingReply<> _r = requestFMToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 11: { QDBusPendingReply<> _r = requestIRMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 12: { QDBusPendingReply<> _r = requestIRToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 13: { QDBusPendingReply<> _r = requestIncreaseVolume();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 14: { QDBusPendingReply<> _r = requestOpenFM((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 15: { QDBusPendingReply<> _r = requestSetFreqency((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 16: { QDBusPendingReply<> _r = requestSetVolume((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 17: { QDBusPendingReply<> _r = requestStart();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 18: { QDBusPendingReply<> _r = requsetIsOpenFM();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 19: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerAudioManagerInterface::onFMChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerAudioManagerInterface::onFMIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerAudioManagerInterface::onIRChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerAudioManagerInterface::onIRIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalDbusServerAudioManagerInterface::onVolumeChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalDbusServerAudioManagerInterface::onVolumeRangeChange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
