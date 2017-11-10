QT      += core gui

CONFIG += C++11

TARGET = BTService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += BTService.cpp \
    BTService.cpp \
    BTServiceProxy.cpp
HEADERS += BTService.h \
    BTService.h \
    BTServiceProxy.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/BTService/BTService.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BTService/BTServiceProxy.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
