/****************************************************************************
** Meta object code from reading C++ file 'MirrorLinkWidget.h'
**
** Created: Mon Dec 4 19:38:21 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MirrorLinkWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MirrorLinkWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   18,   17,   17, 0x09,
      72,   18,   17,   17, 0x09,
     107,  100,   17,   17, 0x09,
     128,  123,   17,   17, 0x09,
     155,  150,   17,   17, 0x09,
     178,  173,   17,   17, 0x08,
     218,   17,   17,   17, 0x08,
     236,  173,   17,   17, 0x08,
     258,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MirrorLinkWidget[] = {
    "MirrorLinkWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onLinkStatusChange(int,int)\0status\0"
    "onBTStatus(int)\0code\0onBTPairCode(QString)\0"
    "name\0onBTName(QString)\0type\0"
    "onMessageWidgetChange(MessageBox::Type)\0"
    "onPopBtnRelease()\0onToolBtnRelease(int)\0"
    "onTimeout()\0"
};

const QMetaObject MirrorLinkWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MirrorLinkWidget,
      qt_meta_data_MirrorLinkWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MirrorLinkWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MirrorLinkWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MirrorLinkWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MirrorLinkWidget))
        return static_cast<void*>(const_cast< MirrorLinkWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MirrorLinkWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onLinkStatusChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onBTStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: onBTPairCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: onBTName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: onMessageWidgetChange((*reinterpret_cast< const MessageBox::Type(*)>(_a[1]))); break;
        case 6: onPopBtnRelease(); break;
        case 7: onToolBtnRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: onTimeout(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
