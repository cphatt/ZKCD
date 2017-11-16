/****************************************************************************
** Meta object code from reading C++ file 'GeneralResetWidget.h'
**
** Created: Thu Nov 16 14:21:46 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/SettingWidget/GeneralWidget/GeneralResetWidget/GeneralResetWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeneralResetWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralResetWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GeneralResetWidget[] = {
    "GeneralResetWidget\0\0onToolButtonRelease()\0"
};

const QMetaObject GeneralResetWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GeneralResetWidget,
      qt_meta_data_GeneralResetWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralResetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralResetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralResetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralResetWidget))
        return static_cast<void*>(const_cast< GeneralResetWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GeneralResetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
