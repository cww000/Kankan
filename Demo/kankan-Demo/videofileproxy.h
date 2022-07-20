#ifndef VIDEOFILEPROXY_H
#define VIDEOFILEPROXY_H

#include <memory>
#include <vector>
#include <string>
#include "videofileinterface.h"
#include "json.hpp"
class VideoFile;

class VideoFileProxy : public VideoFileInterface
{
public:
    VideoFileProxy(std::string& id);
    ~VideoFileProxy();

    nlohmann::json getVideoFileInfo(std::string id);
private:
    std::string m_id;
    std::shared_ptr<VideoFile> m_videoFile;
};

#endif // VIDEOFILEPROXY_H
