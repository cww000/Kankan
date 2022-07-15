#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <string>
#include <vector>
#include "videofileinterface.h"

class VideoFile : public VideoFileInterface
{
public:
    VideoFile(std::string id, std::string address, std::string videoId);
    ~VideoFile();
    std::string getDuration(){ return m_duration; };
    //返回视频的时长
    const std::string address() const;
    const std::string videoId() const;

private:
    std::string m_id;           //
    std::string m_duration;     //视频时长
    std::string m_address;
    std::string m_videoId;
};

#endif // VIDEOFILE_H
