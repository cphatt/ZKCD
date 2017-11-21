/****************************************************************************
** Meta object code from reading C++ file 'AudioService.h'
**
** Created: Tue Nov 21 14:13:52 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AudioService/AudioService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioService[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      19,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
      43,   13,

 // signals: signature, parameters, type, tag, flags
      72,   60,   59,   59, 0x05,
     104,   96,   59,   59, 0x05,
     138,  133,   59,   59, 0x05,
     159,  154,   59,   59, 0x05,
     175,  154,   59,   59, 0x05,
     196,  191,   59,   59, 0x05,

 // slots: signature, parameters, type, tag, flags
     224,  217,  212,   59, 0x0a,
     248,  217,   59,   59, 0x0a,
     272,   59,   59,   59, 0x0a,
     286,   59,   59,   59, 0x0a,
     300,   59,   59,   59, 0x0a,
     324,   59,   59,   59, 0x0a,
     348,   59,   59,   59, 0x0a,
     366,   59,   59,   59, 0x0a,
     384,   59,   59,   59, 0x0a,
     402,  191,   59,   59, 0x0a,
     421,  154,   59,   59, 0x0a,
     447,  440,   59,   59, 0x0a,
     469,  133,   59,   59, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AudioService[] = {
    "AudioService\0Local.DbusServer.AudioManager\0"
    "D-Bus Interface\0\0type,volume\0"
    "onVolumeChange(int,int)\0min,max\0"
    "onVolumeRangeChange(int,int)\0freq\0"
    "onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "onIRIsOpen(int)\0mode\0onIRChange(int)\0"
    "bool\0source\0requestAudioSource(int)\0"
    "releaseAudioSource(int)\0synchronize()\0"
    "reqesetRest()\0requestIncreaseVolume()\0"
    "requestDecreaseVolume()\0requsetIsOpenFM()\0"
    "requestFMToggle()\0requestIRToggle()\0"
    "requestIRMode(int)\0requestOpenFM(int)\0"
    "volume\0requestSetVolume(int)\0"
    "requestSetFreqency(int)\0"
};

const QMetaObject AudioService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AudioService,
      qt_meta_data_AudioService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioService))
        return static_cast<void*>(const_cast< AudioService*>(this));
    return QObject::qt_metacast(_clname);
}

int AudioService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: onVolumeRangeChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onFMChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onFMIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onIRIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onIRChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { bool _r = requestAudioSource((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: releaseAudioSource((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: synchronize(); break;
        case 9: reqesetRest(); break;
        case 10: requestIncreaseVolume(); break;
        case 11: requestDecreaseVolume(); break;
        case 12: requsetIsOpenFM(); break;
        case 13: requestFMToggle(); break;
        case 14: requestIRToggle(); break;
        case 15: requestIRMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: requestOpenFM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: requestSetVolume((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 18: requestSetFreqency((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void AudioService::onVolumeChange(int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AudioService::onVolumeRangeChange(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AudioService::onFMChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AudioService::onFMIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AudioService::onIRIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AudioService::onIRChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
