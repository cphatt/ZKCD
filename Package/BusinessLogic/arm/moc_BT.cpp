/****************************************************************************
** Meta object code from reading C++ file 'BT.h'
**
** Created: Thu Nov 16 14:20:53 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BusinessLogic/BT.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BT[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,    4,    3,    3, 0x05,
      32,   27,    3,    3, 0x05,
      59,   54,    3,    3, 0x05,

 // slots: signature, parameters, type, tag, flags
      77,    3,    3,    3, 0x0a,
      91,    3,    3,    3, 0x0a,
     113,  105,    3,    3, 0x0a,
     135,    3,    3,    3, 0x0a,
     153,   54,    3,    3, 0x0a,
     185,  176,    3,    3, 0x0a,
     212,    3,    3,    3, 0x0a,
     230,    3,    3,    3, 0x0a,
     261,  253,    3,    3, 0x08,
     290,  253,    3,    3, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BT[] = {
    "BT\0\0status\0onBTStatus(int)\0code\0"
    "onBTPairCode(QString)\0name\0onBTName(QString)\0"
    "synchronize()\0requestRest()\0connect\0"
    "requestConnectBT(int)\0requestBTStatus()\0"
    "requestBTName(QString)\0paircode\0"
    "requsetBTPairCode(QString)\0requestBTToggle()\0"
    "requestPairPhoneName()\0service\0"
    "onServiceRegistered(QString)\0"
    "onServiceUnregistered(QString)\0"
};

const QMetaObject BT::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BT,
      qt_meta_data_BT, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BT))
        return static_cast<void*>(const_cast< BT*>(this));
    return QObject::qt_metacast(_clname);
}

int BT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onBTStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onBTPairCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: onBTName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: synchronize(); break;
        case 4: requestRest(); break;
        case 5: requestConnectBT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: requestBTStatus(); break;
        case 7: requestBTName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: requsetBTPairCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: requestBTToggle(); break;
        case 10: requestPairPhoneName(); break;
        case 11: onServiceRegistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: onServiceUnregistered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void BT::onBTStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BT::onBTPairCode(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BT::onBTName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
