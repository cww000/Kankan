#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <string>
#include <vector>
#include "videofileinterface.h"

class VideoFile : public VideoFileInterface
{
public:
    VideoFile();
    ~VideoFile();
private:
    std::string m_id;
    std::string m_address;
};

#endif // VIDEOFILE_H
