#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T16:09:58
#
#-------------------------------------------------
QT       += core gui

TARGET = AudioConfig
TEMPLATE = lib
CONFIG += staticlib

SOURCES += AudioConfig.cpp

HEADERS += AudioConfig.h

SDKPATH = $$PWD/..
COMPILER = arm-none-linux-gnueabi-gcc
PROJECT = Project
DEFINES += $$TARGET$$PROJECT

ARCHITECTURE = arm
message($$QMAKE_CC)

system(mkdir -p $$SDKPATH/Package/$$TARGET/$$ARCHITECTURE)
MOC_DIR += $$SDKPATH/Package/$$TARGET/$$ARCHITECTURE
OBJECTS_DIR += $$SDKPATH/Package/$$TARGET/$$ARCHITECTURE
RCC_DIR += $$SDKPATH/Package/$$TARGET/$$ARCHITECTURE
DESTDIR += $$SDKPATH/Package/$$TARGET/$$ARCHITECTURE

QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/AudioConfig/AudioConfig.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
