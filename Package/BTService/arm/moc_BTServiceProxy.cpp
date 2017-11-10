/****************************************************************************
** Meta object code from reading C++ file 'BTServiceProxy.h'
**
** Created: Fri Nov 10 14:15:25 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BTService/BTServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BTServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerBluetoothInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      40,   35,   34,   34, 0x05,
      63,   58,   34,   34, 0x05,
      92,   85,   34,   34, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   35,  108,   34, 0x0a,
     151,   34,  108,   34, 0x0a,
     169,   34,  108,   34, 0x0a,
     195,  187,  108,   34, 0x0a,
     217,   34,  108,   34, 0x0a,
     240,   34,  108,   34, 0x0a,
     263,  254,  108,   34, 0x0a,
     290,   34,  108,   34, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerBluetoothInterface[] = {
    "LocalDbusServerBluetoothInterface\0\0"
    "name\0onBTName(QString)\0code\0"
    "onBTPairCode(QString)\0status\0"
    "onBTStatus(int)\0QDBusPendingReply<>\0"
    "requestBTName(QString)\0requestBTStatus()\0"
    "requestBTToggle()\0connect\0"
    "requestConnectBT(int)\0requestPairPhoneName()\0"
    "requestRest()\0paircode\0"
    "requsetBTPairCode(QString)\0synchronize()\0"
};

const QMetaObject LocalDbusServerBluetoothInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerBluetoothInterface,
      qt_meta_data_LocalDbusServerBluetoothInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerBluetoothInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerBluetoothInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerBluetoothInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerBluetoothInterface))
        return static_cast<void*>(const_cast< LocalDbusServerBluetoothInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerBluetoothInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onBTName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: onBTPairCode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: onBTStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { QDBusPendingReply<> _r = requestBTName((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 4: { QDBusPendingReply<> _r = requestBTStatus();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 5: { QDBusPendingReply<> _r = requestBTToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 6: { QDBusPendingReply<> _r = requestConnectBT((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 7: { QDBusPendingReply<> _r = requestPairPhoneName();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 8: { QDBusPendingReply<> _r = requestRest();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 9: { QDBusPendingReply<> _r = requsetBTPairCode((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 10: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerBluetoothInterface::onBTName(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerBluetoothInterface::onBTPairCode(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerBluetoothInterface::onBTStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
