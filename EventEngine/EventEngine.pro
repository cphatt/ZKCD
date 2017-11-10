#-------------------------------------------------
#
# Project created by QtCreator 2017-01-14T08:23:55
#
#-------------------------------------------------

QT       += core gui

TARGET = EventEngine
TEMPLATE = lib
CONFIG += staticlib

SOURCES += EventEngine.cpp
HEADERS += EventEngine.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/EventEngine/EventEngine.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
