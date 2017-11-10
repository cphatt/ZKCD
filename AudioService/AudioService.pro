QT += core gui dbus

TARGET = AudioService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    AudioService.cpp \
    AudioServiceProxy.cpp

HEADERS += \
    AudioService.h \
    AudioServiceProxy.h

include(../ArkSdk.pri)

QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/AudioService/AudioService.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/AudioService/AudioServiceProxy.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
