/****************************************************************************
** Meta object code from reading C++ file 'AV2Widget.h'
**
** Created: Sat Dec 9 17:33:38 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/AVWidget/AV2Widget/AV2Widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AV2Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AV2Widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   11,   10,   10, 0x09,
      65,   11,   10,   10, 0x09,
      85,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AV2Widget[] = {
    "AV2Widget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onAVStatus(int,int)\0onTimeout()\0"
};

const QMetaObject AV2Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AV2Widget,
      qt_meta_data_AV2Widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AV2Widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AV2Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AV2Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AV2Widget))
        return static_cast<void*>(const_cast< AV2Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AV2Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onAVStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onTimeout(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
