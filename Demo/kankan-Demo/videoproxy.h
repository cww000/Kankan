#ifndef VIDEOPROXY_H
#define VIDEOPROXY_H

#include <memory>
#include "videointerface.h"
#include <vector>
#include <string>

class Video;

class VideoProxy : public VideoInterface
{
public:
    VideoProxy(std::string id);
    std::vector<std::string> getVideoInfo(const std::string& id);
    //获取稿件的相关信息(发布时间、封面、视频时长、标题)
    //id：稿件id

    ~VideoProxy();
private:
    std::string m_id;
    std::shared_ptr<Video> m_video;
};

#endif // VIDEOPROXY_H
