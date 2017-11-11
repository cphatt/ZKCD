/****************************************************************************
** Meta object code from reading C++ file 'SettingServiceProxy.h'
**
** Created: Sat Nov 11 09:23:44 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SettingService/SettingServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerSettingInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      45,   33,   32,   32, 0x05,
      71,   65,   32,   32, 0x05,
     107,   95,   32,   32, 0x05,
     138,   65,   32,   32, 0x05,
     165,  160,   32,   32, 0x05,
     201,  192,   32,   32, 0x05,
     223,   65,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
     267,   32,  247,   32, 0x0a,
     286,  275,  247,   32, 0x0a,
     309,  275,  247,   32, 0x0a,
     330,  160,  247,   32, 0x0a,
     352,  192,  247,   32, 0x0a,
     369,  275,  247,   32, 0x0a,
     410,  392,  247,   32, 0x0a,
     431,   32,  247,   32, 0x0a,
     448,  160,  247,   32, 0x0a,
     460,   32,  247,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerSettingInterface[] = {
    "LocalDbusServerSettingInterface\0\0"
    "type,status\0onAVStatus(int,int)\0value\0"
    "onBrightnessChange(int)\0status,data\0"
    "onCalibrateChange(int,QString)\0"
    "onContrastChange(int)\0type\0"
    "onDisplayScreenChange(int)\0language\0"
    "onLanguageChange(int)\0onSaturationChange(int)\0"
    "QDBusPendingReply<>\0reset()\0type,value\0"
    "setBrightness(int,int)\0setContrast(int,int)\0"
    "setDisplayScreen(int)\0setLanguage(int)\0"
    "setSaturation(int,int)\0type,width,height\0"
    "startAV(int,int,int)\0startCalibrate()\0"
    "stopAV(int)\0synchronize()\0"
};

const QMetaObject LocalDbusServerSettingInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerSettingInterface,
      qt_meta_data_LocalDbusServerSettingInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerSettingInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerSettingInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerSettingInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerSettingInterface))
        return static_cast<void*>(const_cast< LocalDbusServerSettingInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerSettingInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onAVStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: onBrightnessChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onCalibrateChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onContrastChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onDisplayScreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onLanguageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: onSaturationChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { QDBusPendingReply<> _r = reset();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 8: { QDBusPendingReply<> _r = setBrightness((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 9: { QDBusPendingReply<> _r = setContrast((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 10: { QDBusPendingReply<> _r = setDisplayScreen((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 11: { QDBusPendingReply<> _r = setLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 12: { QDBusPendingReply<> _r = setSaturation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 13: { QDBusPendingReply<> _r = startAV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 14: { QDBusPendingReply<> _r = startCalibrate();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 15: { QDBusPendingReply<> _r = stopAV((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 16: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerSettingInterface::onAVStatus(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerSettingInterface::onBrightnessChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerSettingInterface::onCalibrateChange(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerSettingInterface::onContrastChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalDbusServerSettingInterface::onDisplayScreenChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalDbusServerSettingInterface::onLanguageChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LocalDbusServerSettingInterface::onSaturationChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
