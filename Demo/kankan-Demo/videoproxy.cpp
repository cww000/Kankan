#include "videoproxy.h"
#include <vector>
#include "videobroker.h"

VideoProxy::VideoProxy(std::string id) :
    m_id{id}, m_video{}
{

}

std::vector<std::string> VideoProxy::getVideoInfo(std::string id)
{
    if (m_video == nullptr)
        m_video = std::make_shared<Video>(VideoBroker::getInstance()->getVideo(id));
        //实例化video对象
    m_video->getVideoInfo();//获取video对象的数据概要
}

VideoProxy::~VideoProxy()
{

}
