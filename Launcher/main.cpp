#include "MainWidget/MainWidget.h"
#include "BusinessLogicUtility.h"
#include "Utility.h"
#include "Widget.h"
#include "Setting.h"
#include "Multimedia.h"
#include "ArkApplication.h"
#include "SettingService.h"
#include "MultimediaService.h"
#include "AudioService.h"
#include "UserInterfaceUtility.h"
#include <QTextCodec>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


//volume
//kmem 0xe4000008 0x7878
//kernel message
//echo 8 > /proc/sys/kernel/printk
//bandwidth
//kmem 0xe4900054 0xb94095
void setTextCodec();
void customMessageOutput(QtMsgType type, const char* msg);

int main(int argc, char *argv[])
{
    UserInterfaceUtility::startTime();
    if ((1 == argc) || (2 == argc)) {
#ifdef APPS
        int tempArgc(4);
        char* tempArgv[4] = {argv[0], "-t", "-qws", "-apps"};
#else
        int tempArgc(3);
        char* tempArgv[3] = {argv[0], "-t", "-qws"};
#endif
        argc = tempArgc;
        argv = tempArgv;
    }
    int result(-1);
    while(-1 != (result = getopt(argc, argv, "t:"))) {
//        qWarning("option = t, optopt = %c, optarg = % s\n", optopt, optarg);
        QString argument(optarg);
        qDebug() << "argument" << argument;
        switch(result) {
        case 't': {
            if (QString("-qws") == argument) {
                nice(-20);
                qInstallMsgHandler(customMessageOutput);
                ArkApplication app(argc, argv);
                setTextCodec();
                app.setApplicationName(ArkMicroLauncherService);
                MainWidget mainWindow;
                Q_UNUSED(mainWindow);
                return app.exec();
            } else if (SettingApplication == argument) {
                QCoreApplication app(argc, argv);
                app.setApplicationName(ArkMicroSettingService);
                SettingService settingService;
                Q_UNUSED(settingService)
                qCritical("SettingApplicationiiiiiiiiiiiiii");
                return app.exec();
            } else if (MultimediaApplication == argument) {
                qInstallMsgHandler(customMessageOutput);
                QCoreApplication app(argc, argv);
                setTextCodec();
                app.setApplicationName(ArkMicroMultimediaService);
                MultimediaService multimediaService;
                Q_UNUSED(multimediaService)
                return app.exec();
            }
            break;
        }
        default: {
//            qWarning("default, result=%c\n",result);
            break;
        }
        }
    }
    return EXIT_FAILURE;
}

void customMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg: {
//        fprintf(stderr, "Debug: %s\n", msg);   //那绝对是在这里吧打印消除了
        break;
    }
    case QtWarningMsg: {
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    }
    case QtCriticalMsg: {
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    }
    case QtFatalMsg: {
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
        break;
    }
    default: {
        break;
    }
    }
}

void setTextCodec()
{
    QTextCodec* textCodec = QTextCodec::codecForName("UTF-8");
    if (NULL != textCodec) {
        QTextCodec::setCodecForCStrings(textCodec);
        QTextCodec::setCodecForTr(textCodec);
        QTextCodec::setCodecForLocale(textCodec);
    } else {
        qDebug() << "get codecForName UTF-8 failed!";
    }
}
