/****************************************************************************
** Meta object code from reading C++ file 'Audio.h'
**
** Created: Mon Dec 11 15:58:20 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BusinessLogic/Audio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Audio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Audio[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,    7,    6,    6, 0x05,
      51,   43,    6,    6, 0x05,
      85,   80,    6,    6, 0x05,
     106,  101,    6,    6, 0x05,
     122,  101,    6,    6, 0x05,
     143,  138,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     167,  159,    6,    6, 0x08,
     196,  159,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Audio[] = {
    "Audio\0\0type,volume\0onVolumeChange(int,int)\0"
    "min,max\0onVolumeRangeChange(int,int)\0"
    "freq\0onFMChange(int)\0open\0onFMIsOpen(int)\0"
    "onIRIsOpen(int)\0mode\0onIRChange(int)\0"
    "service\0onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
};

const QMetaObject Audio::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Audio,
      qt_meta_data_Audio, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Audio::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Audio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Audio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Audio))
        return static_cast<void*>(const_cast< Audio*>(this));
    return QObject::qt_metacast(_clname);
}

int Audio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 6: onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Audio::onVolumeChange(int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Audio::onVolumeRangeChange(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Audio::onFMChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Audio::onFMIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Audio::onIRIsOpen(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Audio::onIRChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
