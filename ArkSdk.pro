include(./ArkSdk.pri)
CONFIG +=  ordered

TEMPLATE = subdirs

SUBDIRS += \
    ArkApplication \
    AutoConnect \
    RunnableThread \
    EventEngine \
    DbusService \
    Utility \
    AudioConfig \
    AudioService \
    BTService \
    SettingService \
    DiskDeviceWatcher \
    MultimediaService \
    BusinessLogic \
    UserInterface \
    Launcher
