/****************************************************************************
** Meta object code from reading C++ file 'LanguageWidget.h'
**
** Created: Sat Dec 9 17:33:38 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/SettingWidget/LanguageWidget/LanguageWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LanguageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LanguageWidget[] = {

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
      28,   16,   15,   15, 0x09,
      79,   70,   15,   15, 0x09,
     110,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LanguageWidget[] = {
    "LanguageWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "language\0onLanguageTranslateChange(int)\0"
    "onToolButtonRelease()\0"
};

const QMetaObject LanguageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LanguageWidget,
      qt_meta_data_LanguageWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LanguageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LanguageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LanguageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LanguageWidget))
        return static_cast<void*>(const_cast< LanguageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LanguageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onLanguageTranslateChange((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
