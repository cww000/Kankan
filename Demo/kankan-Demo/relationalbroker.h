#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H

#include <unordered_map>
#include "cache.h"

class RelationalBroker
{
public:
    RelationalBroker();
    virtual ~RelationalBroker();
private:
    std::unordered_map<std::string, Cache> _caches;
};

#endif // RELATIONALBROKER_H
