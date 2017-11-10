#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T14:39:38
#
#-------------------------------------------------

QT      += core gui
CONFIG += C++11

TARGET = ArkApplication
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ArkApplication.cpp
HEADERS += ArkApplication.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/ArkApplication/ArkApplication.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)

