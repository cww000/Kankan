#include "videofileproxy.h"
#include "videofilebroker.h"

VideoFileProxy::VideoFileProxy(std::string &id) : m_id{id}
{

}

VideoFileProxy::~VideoFileProxy()
{

}

std::string VideoFileProxy::getVideoFileInfo(std::string id)
{
    if (m_videoFile == nullptr)
        m_videoFile = VideoFileBroker::getInstance()->getVideoFile(id);
    return m_videoFile->getDuration();
}
