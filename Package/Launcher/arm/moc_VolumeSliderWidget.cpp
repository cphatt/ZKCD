/****************************************************************************
** Meta object code from reading C++ file 'VolumeSliderWidget.h'
**
** Created: Mon Dec 11 15:59:03 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/VolumeWidget/VolumeToolWidget/VolumeSliderWidget/VolumeSliderWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolumeSliderWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VolumeSliderWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      38,   19,   19,   19, 0x05,
      66,   55,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VolumeSliderWidget[] = {
    "VolumeSliderWidget\0\0minusBtnRelease()\0"
    "plusBtnRelease()\0millesimal\0"
    "tickMarksMillesimalEnd(int)\0"
};

const QMetaObject VolumeSliderWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VolumeSliderWidget,
      qt_meta_data_VolumeSliderWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VolumeSliderWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VolumeSliderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VolumeSliderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VolumeSliderWidget))
        return static_cast<void*>(const_cast< VolumeSliderWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VolumeSliderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: minusBtnRelease(); break;
        case 1: plusBtnRelease(); break;
        case 2: tickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void VolumeSliderWidget::minusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VolumeSliderWidget::plusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VolumeSliderWidget::tickMarksMillesimalEnd(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
