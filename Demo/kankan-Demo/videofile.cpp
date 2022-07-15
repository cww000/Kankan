#include "videofile.h"

VideoFile::VideoFile(std::string id, std::string address, std::string videoId) :
    m_id{id}, m_address{address}, m_videoId{videoId}
{

}

VideoFile::~VideoFile()
{

}

const std::string VideoFile::address() const
{
    return m_address;
}

const std::string VideoFile::videoId() const
{
    return m_videoId;
}
