QT += core gui dbus

TARGET = DbusService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    DbusService.cpp

HEADERS += \
    DbusService.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/DbusService/DbusService.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
