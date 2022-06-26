#ifndef VIDEOFILEPROXY_H
#define VIDEOFILEPROXY_H

#include <memory>
#include "videofileinterface.h"

class VideoFile;

class VideoFileProxy : public VideoFileInterface
{
public:
    VideoFileProxy();
    ~VideoFileProxy();
private:
    std::shared_ptr<VideoFile> m_videoFile;
};

#endif // VIDEOFILEPROXY_H
