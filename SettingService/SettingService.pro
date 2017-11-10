QT += core  dbus

TARGET = SettingService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    SettingService.cpp \
    SettingServiceProxy.cpp \
    SettingPersistent.cpp

HEADERS += \
    SettingService.h \
    SettingServiceProxy.h \
    SettingPersistent.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/SettingService/SettingService.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/SettingService/SettingServiceProxy.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/SettingService/SettingPersistent.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher && \
                  $$PWD/Script.sh $$PWD/SettingService $$PWD/SettingServiceProxy
system($$QMAKE_POST_LINK)
