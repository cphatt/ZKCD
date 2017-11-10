QT += core gui xml dbus
CONFIG += serialport
TEMPLATE = app

TARGET = Launcher

RESOURCES += \
    Resources.qrc

TRANSLATIONS += \
    ./Resources/Languages/Launcher_EN.ts \
    ./Resources/Languages/Launcher_CN.ts \
    ./Resources/Languages/Launcher_DE.ts \
    ./Resources/Languages/Launcher_FR.ts \
    ./Resources/Languages/Launcher_JP.ts \
    ./Resources/Languages/Launcher_KO.ts \
    ./Resources/Languages/Launcher_PO.ts \
    ./Resources/Languages/Launcher_RU.ts \
    ./Resources/Languages/Launcher_SP.ts

SOURCES += \
    main.cpp \
    MainWidget/HomeWidget/HomeWidget.cpp \
    MainWidget/IdleWidget/IdleWidget.cpp \
    MainWidget/LinkWidget/CarplayLinkWidget/CarplayLinkWidget.cpp \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.cpp \
    MainWidget/LinkWidget/LinkWidget.cpp \
    MainWidget/MessageBoxWidget/MessageBoxWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/ImageStatusWidget/ImageStatusWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/ImageToolBarWidget/ImageToolBarWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/ImageWidget.cpp \
    MainWidget/DiskWidget/MusicWidget/MusicShortCutWidget/MusicShortCutWidget.cpp \
    MainWidget/DiskWidget/MusicWidget/MusicWidget.cpp \
    MainWidget/DiskWidget/VideoWidget/VideoStatusWidget/VideoStatusWidget.cpp \
    MainWidget/DiskWidget/VideoWidget/VideoToolBarWidget/VideoToolBarWidget.cpp \
    MainWidget/DiskWidget/VideoWidget/VideoWidget.cpp \
#    MainWidget/SettingWidget/EffectWidget/EffectWidget.cpp \
#    MainWidget/SettingWidget/FieldWidget/FieldWidget.cpp \
    MainWidget/SettingWidget/GeneralWidget/GeneralWidget.cpp \
    MainWidget/SettingWidget/LanguageWidget/LanguageWidget.cpp \
    MainWidget/SettingWidget/SettingWidget.cpp \
    MainWidget/StatusBarWidget/StatusBarWidget.cpp \
    MainWidget/TabBarWidget/TabBarWidget.cpp \
    MainWidget/MainWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskImageListViewWidget/USBDiskImageListViewWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskListViewWidget.cpp \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskToolWidget/USBDiskToolWidget.cpp \
    MainWidget/AVWidget/AV1Widget/AV1Widget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskWidget.cpp \
    MainWidget/AVWidget/AV2Widget/AV2Widget.cpp \
    MainWidget/DiskWidget/DiskWidget.cpp \
    MainWidget/AVWidget/AVWidget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskImageListViewWidget/SDDiskImageListViewWidget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskMusicListViewWidget/SDDiskMusicListViewWidget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskListViewWidget.cpp \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskToolWidget/SDDiskToolWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/ImageShortCutWidget/ImageShortCutWidget.cpp \
    MainWidget/DiskWidget/VideoWidget/VideoShortCutWidget/VideoShortCutWidget.cpp \
    MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralListView.cpp \
    MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralSlider/GeneralSlider.cpp \
#    MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundSlider/EffectSoundSlider.cpp \
#    MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundWidget.cpp \
#    MainWidget/SettingWidget/EffectWidget/EffectToolBarWidget/EffectToolBarWidget.cpp \
    MainWidget/FMWidget/FMWidget.cpp \
    MainWidget/FMWidget/FMToolWidget/FMToolWidget.cpp \
    MainWidget/CalibrateWidget/CalibrateWidget.cpp \
    MainWidget/VolumeWidget/VolumeWidget.cpp \
    MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.cpp \
    MainWidget/VolumeWidget/VolumeToolWidget/VolumeSliderWidget/VolumeSliderWidget.cpp \
    MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicToolWidget.cpp \
    MainWidget/DiskWidget/MultimediaLoadingWidget.cpp \
    MainWidget/DiskWidget/MusicWidget/MusicLoadingWidget/MusicLoadingWidget.cpp \
    MainWidget/DiskWidget/VideoWidget/VideoLoadingWidget/VideoLoadingWidget.cpp \
    MainWidget/LinkWidget/CarplayLinkWidget/CarplayShortCutWidget/CarplayShortCutWidget.cpp \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorShortCutWidget/MirrorShortCutWidget.cpp \
    MainWidget/DiskWidget/ImageWidget/ImageLoadingWidget/ImageLoadingWidget.cpp \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorToolWidget/MirrorToolWidget.cpp \
    MainWidget/DiskWidget/MultimediaListView.cpp \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorMessageDialog/MirrorMessageDialog.cpp \
    MainWidget/SettingWidget/GeneralWidget/GeneralResetWidget/GeneralResetWidget.cpp \
    MainWidget/IRWidget/IRWidget.cpp \
    MainWidget/IRWidget/IRToolWidget/IRToolWidget.cpp \
    MainWidget/SettingWidget/VersionWidget/VersionWidget.cpp \
    MainWidget/SettingWidget/VersionWidget/VersionListView/VersionListView.cpp

HEADERS += \
    MainWidget/HomeWidget/HomeWidget.h \
    MainWidget/IdleWidget/IdleWidget.h \
    MainWidget/LinkWidget/CarplayLinkWidget/CarplayLinkWidget.h \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.h \
    MainWidget/LinkWidget/LinkWidget.h \
    MainWidget/MessageBoxWidget/MessageBoxWidget.h \
    MainWidget/DiskWidget/ImageWidget/ImageStatusWidget/ImageStatusWidget.h \
    MainWidget/DiskWidget/ImageWidget/ImageToolBarWidget/ImageToolBarWidget.h \
    MainWidget/DiskWidget/ImageWidget/ImageWidget.h \
    MainWidget/DiskWidget/MusicWidget/MusicShortCutWidget/MusicShortCutWidget.h \
    MainWidget/DiskWidget/MusicWidget/MusicWidget.h \
    MainWidget/DiskWidget/VideoWidget/VideoStatusWidget/VideoStatusWidget.h \
    MainWidget/DiskWidget/VideoWidget/VideoToolBarWidget/VideoToolBarWidget.h \
    MainWidget/DiskWidget/VideoWidget/VideoWidget.h \
#    MainWidget/SettingWidget/EffectWidget/EffectWidget.h \
#    MainWidget/SettingWidget/FieldWidget/FieldWidget.h \
    MainWidget/SettingWidget/GeneralWidget/GeneralWidget.h \
    MainWidget/SettingWidget/LanguageWidget/LanguageWidget.h \
    MainWidget/SettingWidget/SettingWidget.h \
    MainWidget/StatusBarWidget/StatusBarWidget.h \
    MainWidget/TabBarWidget/TabBarWidget.h \
    MainWidget/MainWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskImageListViewWidget/USBDiskImageListViewWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskListViewWidget.h \
    MainWidget/DiskWidget/USBDiskWidget/USBDiskToolWidget/USBDiskToolWidget.h \
    MainWidget/AVWidget/AV1Widget/AV1Widget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskWidget.h \
    MainWidget/AVWidget/AV2Widget/AV2Widget.h \
    MainWidget/DiskWidget/DiskWidget.h \
    MainWidget/AVWidget/AVWidget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskImageListViewWidget/SDDiskImageListViewWidget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskMusicListViewWidget/SDDiskMusicListViewWidget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskListViewWidget.h \
    MainWidget/DiskWidget/SDDiskWidget/SDDiskToolWidget/SDDiskToolWidget.h \
    MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.h \
    MainWidget/DiskWidget/ImageWidget/ImageShortCutWidget/ImageShortCutWidget.h \
    MainWidget/DiskWidget/VideoWidget/VideoShortCutWidget/VideoShortCutWidget.h \
    MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralListView.h \
    MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralSlider/GeneralSlider.h \
#    MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundSlider/EffectSoundSlider.h \
#    MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundWidget.h \
#    MainWidget/SettingWidget/EffectWidget/EffectToolBarWidget/EffectToolBarWidget.h \
    MainWidget/FMWidget/FMWidget.h \
    MainWidget/FMWidget/FMToolWidget/FMToolWidget.h \
    MainWidget/CalibrateWidget/CalibrateWidget.h \
    MainWidget/VolumeWidget/VolumeWidget.h \
    MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.h \
    MainWidget/VolumeWidget/VolumeToolWidget/VolumeSliderWidget/VolumeSliderWidget.h \
    MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicToolWidget.h \
    MainWidget/DiskWidget/MultimediaLoadingWidget.h \
    MainWidget/DiskWidget/MusicWidget/MusicLoadingWidget/MusicLoadingWidget.h \
    MainWidget/DiskWidget/VideoWidget/VideoLoadingWidget/VideoLoadingWidget.h \
    MainWidget/LinkWidget/CarplayLinkWidget/CarplayShortCutWidget/CarplayShortCutWidget.h \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorShortCutWidget/MirrorShortCutWidget.h \
    MainWidget/DiskWidget/ImageWidget/ImageLoadingWidget/ImageLoadingWidget.h \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorToolWidget/MirrorToolWidget.h \
    MainWidget/DiskWidget/MultimediaListView.h \
    MainWidget/LinkWidget/MirrorLinkWidget/MirrorMessageDialog/MirrorMessageDialog.h \
    MainWidget/SettingWidget/GeneralWidget/GeneralResetWidget/GeneralResetWidget.h \
    MainWidget/IRWidget/IRWidget.h \
    MainWidget/IRWidget/IRToolWidget/IRToolWidget.h \
    MainWidget/SettingWidget/VersionWidget/VersionWidget.h \
    MainWidget/SettingWidget/VersionWidget/VersionListView/VersionListView.h

include(../ArkSdk.pri)

unix:!macx: LIBS += -L$$SDKPATH/Package/BusinessLogic/$$ARCHITECTURE -lBusinessLogic
unix:!macx: LIBS += -L$$SDKPATH/Package/UserInterface/$$ARCHITECTURE -lUserInterface
unix:!macx: LIBS += -L$$SDKPATH/Package/ArkApplication/$$ARCHITECTURE -lArkApplication
unix:!macx: LIBS += -L$$SDKPATH/Package/AutoConnect/$$ARCHITECTURE -lAutoConnect
unix:!macx: LIBS += -L$$SDKPATH/Package/EventEngine/$$ARCHITECTURE -lEventEngine
unix:!macx: LIBS += -L$$SDKPATH/Package/DbusService/$$ARCHITECTURE -lDbusService
unix:!macx: LIBS += -L$$SDKPATH/Package/AudioService/$$ARCHITECTURE -lAudioService
unix:!macx: LIBS += -L$$SDKPATH/Package/AudioConfig/$$ARCHITECTURE -lAudioConfig
unix:!macx: LIBS += -L$$SDKPATH/Package/BTService/$$ARCHITECTURE -lBTService
unix:!macx: LIBS += -L$$SDKPATH/Package/SettingService/$$ARCHITECTURE -lSettingService
unix:!macx: LIBS += -L$$SDKPATH/Package/MultimediaService/$$ARCHITECTURE -lMultimediaService
unix:!macx: LIBS += -L$$SDKPATH/Package/Utility/$$ARCHITECTURE -lUtility
unix:!macx: LIBS += -L$$SDKPATH/Package/RunnableThread/$$ARCHITECTURE -lRunnableThread
unix:!macx: LIBS += -L$$SDKPATH/Package/DiskDeviceWatcher/$$ARCHITECTURE -lDiskDeviceWatcher

unix:!macx: LIBS += -ldl
unix:!macx: LIBS += -L$$SDKPATH/AVService -larkcmn

BUSINESSLOGIC = $$SDKPATH/Package/BusinessLogic
INCLUDEPATH += $$BUSINESSLOGIC
DEPENDPATH += $$BUSINESSLOGIC

USERINTERFACE = $$SDKPATH/Package/UserInterface
INCLUDEPATH += $$USERINTERFACE
DEPENDPATH += $$USERINTERFACE

AUDIOCONFIG = $$SDKPATH/Package/AudioConfig
INCLUDEPATH += $$AUDIOCONFIG
DEPENDPATH += $$AUDIOCONFIG

DISKDEVICEWATCHER = $$SDKPATH/Package/DiskDeviceWatcher
INCLUDEPATH += $$DISKDEVICEWATCHER
DEPENDPATH += $$DISKDEVICEWATCHER

UTILITY = $$SDKPATH/Package/Utility
INCLUDEPATH += $$UTILITY
DEPENDPATH += $$UTILITY

DUMP = $$SDKPATH/Package/Dump
INCLUDEPATH += $$DUMP
DEPENDPATH += $$DUMP

ARKAPPLICATION = $$SDKPATH/Package/ArkApplication
INCLUDEPATH += $$ARKAPPLICATION
DEPENDPATH += $$ARKAPPLICATION

EVENENGINE = $$SDKPATH/Package/EventEngine
INCLUDEPATH += $$EVENENGINE
DEPENDPATH += $$EVENENGINE

DBUSSERVICE = $$SDKPATH/Package/DbusService
INCLUDEPATH += $$DBUSSERVICE
DEPENDPATH += $$DBUSSERVICE

AUTOCONNECT = $$SDKPATH/Package/AutoConnect
INCLUDEPATH += $$AUTOCONNECT
DEPENDPATH += $$AUTOCONNECT

RUNNABLETHREAD = $$SDKPATH/Package/RunnableThread
INCLUDEPATH += $$RUNNABLETHREAD
DEPENDPATH += $$RUNNABLETHREAD

BTSERVICE = $$SDKPATH/Package/BTService
INCLUDEPATH += $$BTSERVICE
DEPENDPATH += $$BTSERVICE

SETTINGSERVICE = $$SDKPATH/Package/SettingService
INCLUDEPATH += $$SETTINGSERVICE
DEPENDPATH += $$SETTINGSERVICE

MULTIMEDIASERVICE = $$SDKPATH/Package/MultimediaService
INCLUDEPATH += $$MULTIMEDIASERVICE
DEPENDPATH += $$MULTIMEDIASERVICE

AUDIOSERVICE = $$SDKPATH/Package/AudioService
INCLUDEPATH += $$AUDIOSERVICE
DEPENDPATH += $$AUDIOSERVICE
