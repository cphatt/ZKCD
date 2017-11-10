#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T11:53:36
#
#-------------------------------------------------

QT       += core gui dbus

TARGET = BusinessLogic
TEMPLATE = lib
CONFIG += staticlib

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/Audio.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/AV.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/BusinessLogicUtility.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/CarplayLinkProxy.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/Link.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/MirrorLinkProxy.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/Multimedia.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/BT.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/Setting.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/SettingServiceProxy.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/BusinessLogic/Widget.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
HEADERS += \
    Audio.h \
    AV.h \
    BusinessLogicUtility.h \
    CarplayLinkProxy.h \
    Link.h \
    MirrorLinkProxy.h \
    Multimedia.h \
    Setting.h \
    Widget.h \
    BT.h

SOURCES += \
    Audio.cpp \
    AV.cpp \
    BusinessLogicUtility.cpp \
    CarplayLinkProxy.cpp \
    Link.cpp \
    MirrorLinkProxy.cpp \
    Multimedia.cpp \
    Setting.cpp \
    Widget.cpp \
    BT.cpp

