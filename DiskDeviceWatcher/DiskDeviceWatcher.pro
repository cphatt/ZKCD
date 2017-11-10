#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T21:48:48
#
#-------------------------------------------------

QT       += core gui

TARGET = DiskDeviceWatcher
TEMPLATE = lib
CONFIG += staticlib

SOURCES += DiskDeviceWatcher.cpp
HEADERS += DiskDeviceWatcher.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/DiskDeviceWatcher/DiskDeviceWatcher.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
