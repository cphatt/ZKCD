/****************************************************************************
** Meta object code from reading C++ file 'GeneralSlider.h'
**
** Created: Fri Nov 10 14:18:51 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralSlider/GeneralSlider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeneralSlider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralSlider[] = {

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
      26,   15,   14,   14, 0x05,
      54,   14,   14,   14, 0x05,
      72,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GeneralSlider[] = {
    "GeneralSlider\0\0millesimal\0"
    "tickMarksMillesimalEnd(int)\0"
    "minusBtnRelease()\0plusBtnRelease()\0"
};

const QMetaObject GeneralSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GeneralSlider,
      qt_meta_data_GeneralSlider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralSlider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralSlider))
        return static_cast<void*>(const_cast< GeneralSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int GeneralSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tickMarksMillesimalEnd((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: minusBtnRelease(); break;
        case 2: plusBtnRelease(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GeneralSlider::tickMarksMillesimalEnd(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GeneralSlider::minusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GeneralSlider::plusBtnRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
