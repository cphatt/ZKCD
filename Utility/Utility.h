#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QString>
#include <string>

bool acquireApplication(const std::string &key = std::string("ArkMicro"), const bool block = true);
bool releaseApplication(const std::string &key = std::string("ArkMicro"));
bool initializeArkVideoResources();
bool hideArkStartupLogo();

const QString compilerDate();
const QString osVersion();

void startCalibratre();

typedef void (*HANDLER) (void*);
HANDLER acquirePreemptiveResource(HANDLER callback, void *parameter);
void clearOwner();

#endif // SINGLEAPPLICATION_H
