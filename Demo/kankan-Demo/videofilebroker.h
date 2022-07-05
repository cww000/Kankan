#ifndef VIDEOFILEBROKER_H
#define VIDEOFILEBROKER_H

#include "relationalbroker.h"
#include "videofile.h"

class VideoFileBroker : public RelationalBroker
{
public:
    virtual ~VideoFileBroker();
    static VideoFileBroker* getInstance();

    std::shared_ptr<VideoFile> getVideoFile(std::string& id);
private:
    VideoFileBroker();

    static VideoFileBroker* m_videoFileBroker;
};

#endif // VIDEOFILEBROKER_H
