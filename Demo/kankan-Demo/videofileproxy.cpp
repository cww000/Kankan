#include "videofileproxy.h"
#include "videofilebroker.h"
#include <iostream>
VideoFileProxy::VideoFileProxy(std::string &id) : m_id{id}
{

}

VideoFileProxy::~VideoFileProxy()
{

}

nlohmann::json VideoFileProxy::getVideoFileInfo(std::string id)
{
    if (m_videoFile == nullptr)
        m_videoFile = VideoFileBroker::getInstance()->getVideoFile(id);
    return m_videoFile->getVideoFileInfo();

}
