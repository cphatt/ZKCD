/****************************************************************************
** Meta object code from reading C++ file 'StatusBarWidget.h'
**
** Created: Thu Nov 16 14:21:45 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/StatusBarWidget/StatusBarWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StatusBarWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatusBarWidget[] = {

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
      29,   17,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_StatusBarWidget[] = {
    "StatusBarWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
};

const QMetaObject StatusBarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatusBarWidget,
      qt_meta_data_StatusBarWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatusBarWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatusBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatusBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatusBarWidget))
        return static_cast<void*>(const_cast< StatusBarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatusBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
