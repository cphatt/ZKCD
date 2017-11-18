/****************************************************************************
** Meta object code from reading C++ file 'MultimediaServiceProxy.h'
**
** Created: Sat Nov 18 09:39:40 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MultimediaServiceProxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultimediaServiceProxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalDbusServerMultimediaInterface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: signature, parameters, type, tag, flags
      48,   36,   35,   35, 0x05,
     114,   79,   35,   35, 0x05,
     168,  159,   35,   35, 0x05,
     211,  204,   35,   35, 0x05,
     270,  240,   35,   35, 0x05,
     311,  159,   35,   35, 0x05,
     375,  347,   35,   35, 0x05,
     427,  422,   35,   35, 0x05,
     454,  204,   35,   35, 0x05,
     483,  240,   35,   35, 0x05,
     524,  159,   35,   35, 0x05,
     560,  347,   35,   35, 0x05,
     606,  204,   35,   35, 0x05,
     635,  204,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
     689,  684,  664,   35, 0x0a,
     719,   35,  664,   35, 0x0a,
     748,  737,  664,   35, 0x0a,
     786,   35,  664,   35, 0x0a,
     821,   35,  664,   35, 0x0a,
     860,  684,  664,   35, 0x0a,
     893,   35,  664,   35, 0x0a,
     918,  204,  664,   35, 0x0a,
     948,   35,  664,   35, 0x0a,
     981,   35,  664,   35, 0x0a,
    1006,   35,  664,   35, 0x0a,
    1032,   35,  664,   35, 0x0a,
    1072, 1050,  664,   35, 0x0a,
    1114,   35,  664,   35, 0x0a,
    1149,   35,  664,   35, 0x0a,
    1188,   35,  664,   35, 0x0a,
    1229, 1218,  664,   35, 0x0a,
    1262,  422,  664,   35, 0x0a,
    1290,   35,  664,   35, 0x0a,
    1321,  204,  664,   35, 0x0a,
    1351,   35,  664,   35, 0x0a,
    1384,   35,  664,   35, 0x0a,
    1392,   35,  664,   35, 0x0a,
    1406,   35,  664,   35, 0x0a,
    1463, 1424,  664,   35, 0x0a,
    1521,   35,  664,   35, 0x0a,
    1556,   35,  664,   35, 0x0a,
    1595,  684,  664,   35, 0x0a,
    1628, 1218,  664,   35, 0x0a,
    1661,  204,  664,   35, 0x0a,
    1691,   35,  664,   35, 0x0a,
    1724,  204,  664,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalDbusServerMultimediaInterface[] = {
    "LocalDbusServerMultimediaInterface\0\0"
    "type,status\0onDeviceWatcherStatus(int,int)\0"
    "type,filePath,index,percent,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "type,xml\0onImagePlayerFileNames(int,QString)\0"
    "status\0onImagePlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "onMusicPlayerFileNames(int,QString)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "mode\0onMusicPlayerPlayMode(int)\0"
    "onMusicPlayerPlayStatus(int)\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onVideoPlayerShowStatus(int)\0"
    "QDBusPendingReply<>\0type\0"
    "deviceWatcherCheckStatus(int)\0"
    "imagePlayerExit()\0type,index\0"
    "imagePlayerPlayListViewIndex(int,int)\0"
    "imagePlayerPlayNextListViewIndex()\0"
    "imagePlayerPlayPreviousListViewIndex()\0"
    "imagePlayerRequestFileNames(int)\0"
    "imagePlayerRotateImage()\0"
    "imagePlayerSetPlayStatus(int)\0"
    "imagePlayerSetPlayStatusToggle()\0"
    "imagePlayerZoomInImage()\0"
    "imagePlayerZoomOutImage()\0musicPlayerExit()\0"
    "type,index,millesimal\0"
    "musicPlayerPlayListViewIndex(int,int,int)\0"
    "musicPlayerPlayNextListViewIndex()\0"
    "musicPlayerPlayPreviousListViewIndex()\0"
    "musicPlayerRequestFileNames()\0millesimal\0"
    "musicPlayerSeekToMillesimal(int)\0"
    "musicPlayerSetPlayMode(int)\0"
    "musicPlayerSetPlayModeToggle()\0"
    "musicPlayerSetPlayStatus(int)\0"
    "musicPlayerSetPlayStatusToggle()\0"
    "reset()\0synchronize()\0videoPlayerExit()\0"
    "type,index,x,y,width,height,millesimal\0"
    "videoPlayerPlayListViewIndex(int,int,int,int,int,int,int)\0"
    "videoPlayerPlayNextListViewIndex()\0"
    "videoPlayerPlayPreviousListViewIndex()\0"
    "videoPlayerRequestFileNames(int)\0"
    "videoPlayerSeekToMillesimal(int)\0"
    "videoPlayerSetPlayStatus(int)\0"
    "videoPlayerSetPlayStatusToggle()\0"
    "videoPlayerSetShowStatus(int)\0"
};

const QMetaObject LocalDbusServerMultimediaInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_LocalDbusServerMultimediaInterface,
      qt_meta_data_LocalDbusServerMultimediaInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalDbusServerMultimediaInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalDbusServerMultimediaInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalDbusServerMultimediaInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalDbusServerMultimediaInterface))
        return static_cast<void*>(const_cast< LocalDbusServerMultimediaInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int LocalDbusServerMultimediaInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onDeviceWatcherStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: onImagePlayerChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: onImagePlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: onImagePlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onMusicPlayerElapsedInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: onMusicPlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: onMusicPlayerID3TagChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: onMusicPlayerPlayMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: onMusicPlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: onVideoPlayerElapsedInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: onVideoPlayerFileNames((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: onVideoPlayerInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 12: onVideoPlayerPlayStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: onVideoPlayerShowStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: { QDBusPendingReply<> _r = deviceWatcherCheckStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 15: { QDBusPendingReply<> _r = imagePlayerExit();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 16: { QDBusPendingReply<> _r = imagePlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 17: { QDBusPendingReply<> _r = imagePlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 18: { QDBusPendingReply<> _r = imagePlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 19: { QDBusPendingReply<> _r = imagePlayerRequestFileNames((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 20: { QDBusPendingReply<> _r = imagePlayerRotateImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 21: { QDBusPendingReply<> _r = imagePlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 22: { QDBusPendingReply<> _r = imagePlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 23: { QDBusPendingReply<> _r = imagePlayerZoomInImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 24: { QDBusPendingReply<> _r = imagePlayerZoomOutImage();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 25: { QDBusPendingReply<> _r = musicPlayerExit();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 26: { QDBusPendingReply<> _r = musicPlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 27: { QDBusPendingReply<> _r = musicPlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 28: { QDBusPendingReply<> _r = musicPlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 29: { QDBusPendingReply<> _r = musicPlayerRequestFileNames();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 30: { QDBusPendingReply<> _r = musicPlayerSeekToMillesimal((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 31: { QDBusPendingReply<> _r = musicPlayerSetPlayMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 32: { QDBusPendingReply<> _r = musicPlayerSetPlayModeToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 33: { QDBusPendingReply<> _r = musicPlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 34: { QDBusPendingReply<> _r = musicPlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 35: { QDBusPendingReply<> _r = reset();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 36: { QDBusPendingReply<> _r = synchronize();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 37: { QDBusPendingReply<> _r = videoPlayerExit();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 38: { QDBusPendingReply<> _r = videoPlayerPlayListViewIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 39: { QDBusPendingReply<> _r = videoPlayerPlayNextListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 40: { QDBusPendingReply<> _r = videoPlayerPlayPreviousListViewIndex();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 41: { QDBusPendingReply<> _r = videoPlayerRequestFileNames((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 42: { QDBusPendingReply<> _r = videoPlayerSeekToMillesimal((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 43: { QDBusPendingReply<> _r = videoPlayerSetPlayStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 44: { QDBusPendingReply<> _r = videoPlayerSetPlayStatusToggle();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        case 45: { QDBusPendingReply<> _r = videoPlayerSetShowStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 46;
    }
    return _id;
}

// SIGNAL 0
void LocalDbusServerMultimediaInterface::onDeviceWatcherStatus(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalDbusServerMultimediaInterface::onImagePlayerChange(int _t1, const QString & _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalDbusServerMultimediaInterface::onImagePlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalDbusServerMultimediaInterface::onImagePlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalDbusServerMultimediaInterface::onMusicPlayerElapsedInformation(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalDbusServerMultimediaInterface::onMusicPlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LocalDbusServerMultimediaInterface::onMusicPlayerID3TagChange(int _t1, int _t2, const QString & _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LocalDbusServerMultimediaInterface::onMusicPlayerPlayMode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LocalDbusServerMultimediaInterface::onMusicPlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void LocalDbusServerMultimediaInterface::onVideoPlayerElapsedInformation(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void LocalDbusServerMultimediaInterface::onVideoPlayerFileNames(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void LocalDbusServerMultimediaInterface::onVideoPlayerInformation(int _t1, int _t2, const QString & _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void LocalDbusServerMultimediaInterface::onVideoPlayerPlayStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void LocalDbusServerMultimediaInterface::onVideoPlayerShowStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_END_MOC_NAMESPACE
