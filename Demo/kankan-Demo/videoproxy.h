#ifndef VIDEOPROXY_H
#define VIDEOPROXY_H

#include <memory>
#include "videointerface.h"

class Video;

class VideoProxy : public VideoInterface
{
public:
    VideoProxy(std::string id);
    void getVideoInfo();

    ~VideoProxy();
private:
    std::string m_id;
    std::shared_ptr<Video> m_video;
};

#endif // VIDEOPROXY_H
