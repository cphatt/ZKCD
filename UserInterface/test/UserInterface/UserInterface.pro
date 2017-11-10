#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T11:53:36
#
#-------------------------------------------------

QT       += core gui svg

TARGET = UserInterface
TEMPLATE = lib
CONFIG += staticlib

include(../ArkSdk.pri)
QMAKE_POST_LINK = $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/BmpButton.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/BmpWidget.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/CustomItemDelegate.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/CustomListView.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/CustomScrollBar.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/ListView.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/MessageBox.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/Scroll.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/ScrollBar.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/Slider.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/TextWidget.h $$SDKPATH/Package/$$TARGET && \
                  $$SDKPATH/mycp.sh $$SDKPATH/UserInterface/UserInterfaceUtility.h $$SDKPATH/Package/$$TARGET && \
                  rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher

HEADERS += \
    BmpButton.h \
    BmpWidget.h \
    CustomItemDelegate.h \
    CustomListView.h \
    CustomScrollBar.h \
    ListView.h \
    MessageBox.h \
    Scroll.h \
    ScrollBar.h \
    Slider.h \
    TextWidget.h \
    UserInterfaceUtility.h

SOURCES += \
    BmpButton.cpp \
    BmpWidget.cpp \
    CustomItemDelegate.cpp \
    CustomListView.cpp \
    CustomScrollBar.cpp \
    ListView.cpp \
    MessageBox.cpp \
    Scroll.cpp \
    ScrollBar.cpp \
    Slider.cpp \
    TextWidget.cpp \
    UserInterfaceUtility.cpp
