/****************************************************************************
** Meta object code from reading C++ file 'SDDiskVideoListViewWidget.h'
**
** Created: Mon Dec 11 15:59:03 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Launcher/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SDDiskVideoListViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SDDiskVideoListViewWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   27,   26,   26, 0x09,
      81,   27,   26,   26, 0x09,
     121,  112,   26,   26, 0x09,
     164,  157,   26,   26, 0x09,
     221,  193,   26,   26, 0x09,
     297,  267,   26,   26, 0x09,
     344,  338,   26,   26, 0x08,
     376,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SDDiskVideoListViewWidget[] = {
    "SDDiskVideoListViewWidget\0\0type,status\0"
    "ontWidgetTypeChange(Widget::Type,QString)\0"
    "onDeviceWatcherStatus(int,int)\0type,xml\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "status\0onVideoPlayerPlayStatus(int)\0"
    "type,index,fileName,endTime\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "index\0onVideoListViewItemRelease(int)\0"
    "onToolButtonRelease()\0"
};

const QMetaObject SDDiskVideoListViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SDDiskVideoListViewWidget,
      qt_meta_data_SDDiskVideoListViewWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SDDiskVideoListViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SDDiskVideoListViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SDDiskVideoListViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SDDiskVideoListViewWidget))
        return static_cast<void*>(const_cast< SDDiskVideoListViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SDDiskVideoListViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ontWidgetTypeChange((*reinterpret_cast< const Widget::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: onVideoPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: onVideoPlayerInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 5: onVideoPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: onVideoListViewItemRelease((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: onToolButtonRelease(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
