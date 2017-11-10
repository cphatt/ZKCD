#ifndef DUMP_H
#define DUMP_H

#include <iostream>
#include <memory>

typedef void (*CALLBACKHANDLER) (const std::string &path);

class DumpPrivate;
class Dump
{
public:
    explicit Dump(const std::string &path, CALLBACKHANDLER callback);
    ~Dump();
private:
    explicit Dump(const Dump& dump);
    Dump& operator =(const Dump& dump);
    friend class DumpPrivate;
    std::auto_ptr<DumpPrivate> m_Private;
};
#endif // DUMP_H
