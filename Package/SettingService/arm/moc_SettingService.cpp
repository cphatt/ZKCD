/****************************************************************************
** Meta object code from reading C++ file 'SettingService.h'
**
** Created: Sat Nov 18 09:39:32 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingService/SettingService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingService[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      18,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // classinfo: key, value
      40,   15,

 // signals: signature, parameters, type, tag, flags
      66,   57,   56,   56, 0x05,
      94,   88,   56,   56, 0x05,
     118,   88,   56,   56, 0x05,
     140,   88,   56,   56, 0x05,
     169,  164,   56,   56, 0x05,
     208,  196,   56,   56, 0x05,
     251,  239,   56,   56, 0x05,

 // slots: signature, parameters, type, tag, flags
     271,   56,   56,   56, 0x0a,
     285,   56,   56,   56, 0x0a,
     293,   57,   56,   56, 0x0a,
     321,  310,   56,   56, 0x0a,
     344,  310,   56,   56, 0x0a,
     365,  310,   56,   56, 0x0a,
     388,  164,   56,   56, 0x0a,
     410,   56,   56,   56, 0x0a,
     445,  427,   56,   56, 0x0a,
     466,  164,   56,   56, 0x0a,
     478,   56,   56,   56, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingService[] = {
    "SettingService\0Local.DbusServer.Setting\0"
    "D-Bus Interface\0\0language\0"
    "onLanguageChange(int)\0value\0"
    "onBrightnessChange(int)\0onContrastChange(int)\0"
    "onSaturationChange(int)\0type\0"
    "onDisplayScreenChange(int)\0status,data\0"
    "onCalibrateChange(int,QString)\0"
    "type,status\0onAVStatus(int,int)\0"
    "synchronize()\0reset()\0setLanguage(int)\0"
    "type,value\0setBrightness(int,int)\0"
    "setContrast(int,int)\0setSaturation(int,int)\0"
    "setDisplayScreen(int)\0startCalibrate()\0"
    "type,width,height\0startAV(int,int,int)\0"
    "stopAV(int)\0onTimeout()\0"
};

const QMetaObject SettingService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SettingService,
      qt_meta_data_SettingService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingService))
        return static_cast<void*>(const_cast< SettingService*>(this));
    return QObject::qt_metacast(_clname);
}

int SettingService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onLanguageChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: onBrightnessChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onContrastChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: onSaturationChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: onDisplayScreenChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: onCalibrateChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: onAVStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: synchronize(); break;
        case 8: reset(); break;
        case 9: setLanguage((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 10: setBrightness((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 11: setContrast((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 12: setSaturation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 13: setDisplayScreen((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: startCalibrate(); break;
        case 15: startAV((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 16: stopAV((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 17: onTimeout(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void SettingService::onLanguageChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingService::onBrightnessChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingService::onContrastChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingService::onSaturationChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SettingService::onDisplayScreenChange(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SettingService::onCalibrateChange(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SettingService::onAVStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
