/****************************************************************************
** Meta object code from reading C++ file 'IRToolWidget.h'
**
** Created: Sat Dec 9 17:33:39 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/IRWidget/IRToolWidget/IRToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IRToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IRToolWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x09,
      40,   35,   13,   13, 0x09,
      68,   56,   13,   13, 0x09,
      92,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IRToolWidget[] = {
    "IRToolWidget\0\0open\0onIRIsOpen(int)\0"
    "mode\0onIRChange(int)\0type,volume\0"
    "onVolumeChange(int,int)\0onToolButtonRelease()\0"
};

const QMetaObject IRToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IRToolWidget,
      qt_meta_data_IRToolWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IRToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IRToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IRToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IRToolWidget))
        return static_cast<void*>(const_cast< IRToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int IRToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onIRIsOpen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onIRChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
