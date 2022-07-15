#ifndef VIDEOFILEPROXY_H
#define VIDEOFILEPROXY_H

#include <memory>
#include "videofileinterface.h"
#include <vector>

class VideoFile;

class VideoFileProxy : public VideoFileInterface
{
public:
    VideoFileProxy(std::string& id);
    ~VideoFileProxy();

    std::string getVideoFileInfo(std::string id);
private:
    std::string m_id;
    std::shared_ptr<VideoFile> m_videoFile;
};

#endif // VIDEOFILEPROXY_H
