#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T11:53:36
#
#-------------------------------------------------

QT       += core gui

TARGET = Utility
TEMPLATE = lib
CONFIG += staticlib

SOURCES += Utility.cpp

HEADERS += Utility.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/Utility/Utility.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
