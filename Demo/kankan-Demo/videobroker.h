#ifndef VIDEOBROKER_H
#define VIDEOBROKER_H

#include "relationalbroker.h"

class VideoBroker : public RelationalBroker
{
public:
    ~VideoBroker();
private:
    VideoBroker();
    static VideoBroker* m_videoBroker;
};

#endif // VIDEOBROKER_H
