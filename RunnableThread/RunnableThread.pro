#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T14:11:00
#
#-------------------------------------------------

QT       += core gui

TARGET = RunnableThread
TEMPLATE = lib
CONFIG += staticlib

SOURCES += RunnableThread.cpp
HEADERS += RunnableThread.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/RunnableThread/RunnableThread.h $$SDKPATH/Package/$$TARGET && rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
system($$QMAKE_POST_LINK)
