#ifndef VIDEOFILEBROKER_H
#define VIDEOFILEBROKER_H

#include "relationalbroker.h"

class VideoFileBroker : public RelationalBroker
{
public:
    virtual ~VideoFileBroker();
private:
    VideoFileBroker();

    static VideoFileBroker* m_videoFileBroker;
};

#endif // VIDEOFILEBROKER_H
