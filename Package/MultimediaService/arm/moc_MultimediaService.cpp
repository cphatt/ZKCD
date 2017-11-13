/****************************************************************************
** Meta object code from reading C++ file 'MultimediaService.h'
**
** Created: Mon Nov 13 10:09:32 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MultimediaService/MultimediaService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultimediaService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultimediaService[] = {

 // content:
       5,       // revision
       0,       // classname
       1,   14, // classinfo
      46,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // classinfo: key, value
      46,   18,

 // signals: signature, parameters, type, tag, flags
      75,   63,   62,   62, 0x05,
     111,  106,   62,   62, 0x05,
     145,  138,   62,   62, 0x05,
     204,  174,   62,   62, 0x05,
     273,  245,   62,   62, 0x05,
     329,  320,   62,   62, 0x05,
     365,  320,   62,   62, 0x05,
     401,  138,   62,   62, 0x05,
     465,  430,   62,   62, 0x05,
     510,  138,   62,   62, 0x05,
     539,  138,   62,   62, 0x05,
     568,  320,   62,   62, 0x05,
     604,  245,   62,   62, 0x05,
     650,  174,   62,   62, 0x05,

 // slots: signature, parameters, type, tag, flags
     691,   62,   62,   62, 0x0a,
     705,   62,   62,   62, 0x0a,
     718,  713,   62,   62, 0x0a,
     748,   62,   62,   62, 0x0a,
     778,   62,   62,   62, 0x0a,
     809,  106,   62,   62, 0x0a,
     837,   62,   62,   62, 0x0a,
     870,  138,   62,   62, 0x0a,
     922,  900,   62,   62, 0x0a,
     964,   62,   62,   62, 0x0a,
    1003,   62,   62,   62, 0x0a,
    1049, 1038,   62,   62, 0x0a,
    1082,   62,   62,   62, 0x0a,
    1100,  713,   62,   62, 0x0a,
    1144, 1133,   62,   62, 0x0a,
    1182,   62,   62,   62, 0x0a,
    1221,   62,   62,   62, 0x0a,
    1256,   62,   62,   62, 0x0a,
    1281,   62,   62,   62, 0x0a,
    1306,   62,   62,   62, 0x0a,
    1332,   62,   62,   62, 0x0a,
    1365,  138,   62,   62, 0x0a,
    1395,   62,   62,   62, 0x0a,
    1413,  713,   62,   62, 0x0a,
    1446,   62,   62,   62, 0x0a,
    1479,  138,   62,   62, 0x0a,
    1509,  138,   62,   62, 0x0a,
    1578, 1539,   62,   62, 0x0a,
    1636,   62,   62,   62, 0x0a,
    1675,   62,   62,   62, 0x0a,
    1710, 1038,   62,   62, 0x0a,
    1743,   62,   62,   62, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MultimediaService[] = {
    "MultimediaService\0Local.DbusServer.Multimedia\0"
    "D-Bus Interface\0\0type,status\0"
    "onDeviceWatcherStatus(int,int)\0mode\0"
    "onMusicPlayerPlayMode(int)\0status\0"
    "onMusicPlayerPlayStatus(int)\0"
    "elapsedTime,elapsedMillesimal\0"
    "onMusicPlayerElapsedInformation(int,int)\0"
    "type,index,fileName,endTime\0"
    "onMusicPlayerID3TagChange(int,int,QString,int)\0"
    "type,xml\0onMusicPlayerFileNames(int,QString)\0"
    "onImagePlayerFileNames(int,QString)\0"
    "onImagePlayerPlayStatus(int)\0"
    "type,filePath,index,percent,rotate\0"
    "onImagePlayerChange(int,QString,int,int,int)\0"
    "onVideoPlayerShowStatus(int)\0"
    "onVideoPlayerPlayStatus(int)\0"
    "onVideoPlayerFileNames(int,QString)\0"
    "onVideoPlayerInformation(int,int,QString,int)\0"
    "onVideoPlayerElapsedInformation(int,int)\0"
    "synchronize()\0reset()\0type\0"
    "deviceWatcherCheckStatus(int)\0"
    "musicPlayerRequestFileNames()\0"
    "musicPlayerSetPlayModeToggle()\0"
    "musicPlayerSetPlayMode(int)\0"
    "musicPlayerSetPlayStatusToggle()\0"
    "musicPlayerSetPlayStatus(int)\0"
    "type,index,millesimal\0"
    "musicPlayerPlayListViewIndex(int,int,int)\0"
    "musicPlayerPlayPreviousListViewIndex()\0"
    "musicPlayerPlayNextListViewIndex()\0"
    "millesimal\0musicPlayerSeekToMillesimal(int)\0"
    "musicPlayerExit()\0imagePlayerRequestFileNames(int)\0"
    "type,index\0imagePlayerPlayListViewIndex(int,int)\0"
    "imagePlayerPlayPreviousListViewIndex()\0"
    "imagePlayerPlayNextListViewIndex()\0"
    "imagePlayerRotateImage()\0"
    "imagePlayerZoomInImage()\0"
    "imagePlayerZoomOutImage()\0"
    "imagePlayerSetPlayStatusToggle()\0"
    "imagePlayerSetPlayStatus(int)\0"
    "imagePlayerExit()\0videoPlayerRequestFileNames(int)\0"
    "videoPlayerSetPlayStatusToggle()\0"
    "videoPlayerSetShowStatus(int)\0"
    "videoPlayerSetPlayStatus(int)\0"
    "type,index,x,y,width,height,millesimal\0"
    "videoPlayerPlayListViewIndex(int,int,int,int,int,int,int)\0"
    "videoPlayerPlayPreviousListViewIndex()\0"
    "videoPlayerPlayNextListViewIndex()\0"
    "videoPlayerSeekToMillesimal(int)\0"
    "videoPlayerExit()\0"
};

const QMetaObject MultimediaService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MultimediaService,
      qt_meta_data_MultimediaService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultimediaService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultimediaService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultimediaService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaService))
        return static_cast<void*>(const_cast< MultimediaService*>(this));
    return QObject::qt_metacast(_clname);
}

int MultimediaService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onDeviceWatcherStatus((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: onMusicPlayerPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: onMusicPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: onMusicPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: onMusicPlayerID3TagChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 5: onMusicPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: onImagePlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: onImagePlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: onImagePlayerChange((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5]))); break;
        case 9: onVideoPlayerShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 10: onVideoPlayerPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: onVideoPlayerFileNames((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: onVideoPlayerInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 13: onVideoPlayerElapsedInformation((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 14: synchronize(); break;
        case 15: reset(); break;
        case 16: deviceWatcherCheckStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 17: musicPlayerRequestFileNames(); break;
        case 18: musicPlayerSetPlayModeToggle(); break;
        case 19: musicPlayerSetPlayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 20: musicPlayerSetPlayStatusToggle(); break;
        case 21: musicPlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 22: musicPlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 23: musicPlayerPlayPreviousListViewIndex(); break;
        case 24: musicPlayerPlayNextListViewIndex(); break;
        case 25: musicPlayerSeekToMillesimal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 26: musicPlayerExit(); break;
        case 27: imagePlayerRequestFileNames((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 28: imagePlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 29: imagePlayerPlayPreviousListViewIndex(); break;
        case 30: imagePlayerPlayNextListViewIndex(); break;
        case 31: imagePlayerRotateImage(); break;
        case 32: imagePlayerZoomInImage(); break;
        case 33: imagePlayerZoomOutImage(); break;
        case 34: imagePlayerSetPlayStatusToggle(); break;
        case 35: imagePlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 36: imagePlayerExit(); break;
        case 37: videoPlayerRequestFileNames((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 38: videoPlayerSetPlayStatusToggle(); break;
        case 39: videoPlayerSetShowStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 40: videoPlayerSetPlayStatus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 41: videoPlayerPlayListViewIndex((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const int(*)>(_a[5])),(*reinterpret_cast< const int(*)>(_a[6])),(*reinterpret_cast< const int(*)>(_a[7]))); break;
        case 42: videoPlayerPlayPreviousListViewIndex(); break;
        case 43: videoPlayerPlayNextListViewIndex(); break;
        case 44: videoPlayerSeekToMillesimal((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 45: videoPlayerExit(); break;
        default: ;
        }
        _id -= 46;
    }
    return _id;
}

// SIGNAL 0
void MultimediaService::onDeviceWatcherStatus(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MultimediaService::onMusicPlayerPlayMode(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultimediaService::onMusicPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MultimediaService::onMusicPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MultimediaService::onMusicPlayerID3TagChange(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MultimediaService::onMusicPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MultimediaService::onImagePlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MultimediaService::onImagePlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MultimediaService::onImagePlayerChange(const int _t1, const QString & _t2, const int _t3, const int _t4, const int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MultimediaService::onVideoPlayerShowStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MultimediaService::onVideoPlayerPlayStatus(const int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MultimediaService::onVideoPlayerFileNames(const int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MultimediaService::onVideoPlayerInformation(const int _t1, const int _t2, const QString & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MultimediaService::onVideoPlayerElapsedInformation(const int _t1, const int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_END_MOC_NAMESPACE
