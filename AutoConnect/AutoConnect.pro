QT      += core gui

CONFIG += C++11

TARGET = AutoConnect
TEMPLATE = lib
CONFIG += staticlib

SOURCES += AutoConnect.cpp
HEADERS += AutoConnect.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/AutoConnect/AutoConnect.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
