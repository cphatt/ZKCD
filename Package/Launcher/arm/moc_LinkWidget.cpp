/****************************************************************************
** Meta object code from reading C++ file 'LinkWidget.h'
**
** Created: Mon Dec 4 20:47:31 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/LinkWidget/LinkWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LinkWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LinkWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   42,   11,   11, 0x09,
      96,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LinkWidget[] = {
    "LinkWidget\0\0clickCarlife()\0clickCarplay()\0"
    "type,status\0ontWidgetTypeChange(Widget::Type,QString)\0"
    "onToolButtonRelease()\0"
};

const QMetaObject LinkWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LinkWidget,
      qt_meta_data_LinkWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinkWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinkWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinkWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinkWidget))
        return static_cast<void*>(const_cast< LinkWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LinkWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickCarlife(); break;
        case 1: clickCarplay(); break;
        case 2: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LinkWidget::clickCarlife()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LinkWidget::clickCarplay()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
