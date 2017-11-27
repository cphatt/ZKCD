/****************************************************************************
** Meta object code from reading C++ file 'Setting.h'
**
** Created: Sat Nov 25 15:29:00 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BusinessLogic/Setting.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Setting[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,    9,    8,    8, 0x05,
      55,   49,    8,    8, 0x05,
      79,   49,    8,    8, 0x05,
     101,   49,    8,    8, 0x05,
     130,  125,    8,    8, 0x05,
     169,  157,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     189,    9,    8,    8, 0x08,
     219,  211,    8,    8, 0x08,
     248,  211,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Setting[] = {
    "Setting\0\0language\0onLanguageTranslateChange(int)\0"
    "value\0onBrightnessChange(int)\0"
    "onContrastChange(int)\0onSaturationChange(int)\0"
    "type\0onDisplayScreenChange(int)\0"
    "type,status\0onAVStatus(int,int)\0"
    "onLanguageChange(int)\0service\0"
    "onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
};

const QMetaObject Setting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Setting,
      qt_meta_data_Setting, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Setting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Setting))
        return static_cast<void*>(const_cast< Setting*>(this));
    return QObject::qt_metacast(_clname);
}

int Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onLanguageTranslateChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: onSaturationChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: onDisplayScreenChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onAVStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: onLanguageChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Setting::onLanguageTranslateChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Setting::onBrightnessChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Setting::onContrastChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Setting::onSaturationChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Setting::onDisplayScreenChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Setting::onAVStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
