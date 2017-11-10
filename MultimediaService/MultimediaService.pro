QT      += core gui xml dbus

TARGET = MultimediaService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += MultimediaService.cpp \
    DeviceWatcher/DiskScanner/DiskScanner.cpp \
    DeviceWatcher/DeviceWatcher.cpp \
    ImagePlayer/ImagePlayer.cpp \
    MusicPlayer/MusicPlayer.cpp \
    VideoPlayer/VideoPlayer.cpp \
    MultimediaServiceProxy.cpp \
    MultimediaPersistent.cpp \
    DeviceWatcher/DiskDetach/DiskDetach.cpp
HEADERS += MultimediaService.h \
    DeviceWatcher/DiskScanner/DiskScanner.h \
    DeviceWatcher/DeviceWatcher.h \
    ImagePlayer/ImagePlayer.h \
    MusicPlayer/MusicPlayer.h \
    VideoPlayer/VideoPlayer.h \
    MultimediaServiceProxy.h \
    MultimediaPersistent.h \
    DeviceWatcher/DiskDetach/DiskDetach.h

include(../ArkSdk.pri)

QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/MultimediaService/MultimediaService.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/MultimediaService/MultimediaServiceProxy.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/MultimediaService/MultimediaPersistent.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher && \
                  $$PWD/Script.sh $$PWD/MultimediaService $$PWD/MultimediaServiceProxy
system($$QMAKE_POST_LINK)
