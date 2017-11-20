/****************************************************************************
** Meta object code from reading C++ file 'BTService.h'
**
** Created: Mon Nov 20 16:06:11 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BTService/BTService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BTService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BTService[] = {

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
      18,   11,   10,   10, 0x05,
      39,   34,   10,   10, 0x05,
      66,   61,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   10,   10,   10, 0x0a,
      98,   10,   10,   10, 0x0a,
     120,  112,   10,   10, 0x0a,
     142,   10,   10,   10, 0x0a,
     160,   61,   10,   10, 0x0a,
     192,  183,   10,   10, 0x0a,
     219,   10,   10,   10, 0x0a,
     237,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BTService[] = {
    "BTService\0\0status\0onBTStatus(int)\0"
    "code\0onBTPairCode(QString)\0name\0"
    "onBTName(QString)\0synchronize()\0"
    "requestRest()\0connect\0requestConnectBT(int)\0"
    "requestBTStatus()\0requestBTName(QString)\0"
    "paircode\0requsetBTPairCode(QString)\0"
    "requestBTToggle()\0requestPairPhoneName()\0"
};

const QMetaObject BTService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BTService,
      qt_meta_data_BTService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BTService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BTService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BTService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BTService))
        return static_cast<void*>(const_cast< BTService*>(this));
    return QObject::qt_metacast(_clname);
}

int BTService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BTService::onBTStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BTService::onBTPairCode(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BTService::onBTName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
