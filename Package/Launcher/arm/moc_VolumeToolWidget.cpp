/****************************************************************************
** Meta object code from reading C++ file 'VolumeToolWidget.h'
**
** Created: Sat Dec 9 17:33:38 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolumeToolWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VolumeToolWidget[] = {

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
      30,   18,   17,   17, 0x0a,
      54,   17,   17,   17, 0x08,
      74,   17,   17,   17, 0x08,
     104,   93,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VolumeToolWidget[] = {
    "VolumeToolWidget\0\0type,volume\0"
    "onVolumeChange(int,int)\0onMinusBtnRelease()\0"
    "onPlusBtnRelease()\0millesimal\0"
    "onTickMarksMillesimalEnd(int)\0"
};

const QMetaObject VolumeToolWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VolumeToolWidget,
      qt_meta_data_VolumeToolWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VolumeToolWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VolumeToolWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VolumeToolWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VolumeToolWidget))
        return static_cast<void*>(const_cast< VolumeToolWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VolumeToolWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onVolumeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: onMinusBtnRelease(); break;
        case 2: onPlusBtnRelease(); break;
        case 3: onTickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
