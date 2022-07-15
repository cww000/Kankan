#include "videoproxy.h"
#include <vector>
#include "videobroker.h"
#include <iostream>

VideoProxy::VideoProxy(std::string id) :
    m_id{id}, m_video{}
{

}

std::vector<std::string> VideoProxy::getVideoInfo(const std::string& id)
{

    if (m_video == nullptr)
        m_video = VideoBroker::getInstance()->getVideo(id); //实例化video对象

    return m_video->getVideoInfo();//获取video对象的数据概要
}

VideoProxy::~VideoProxy()
{

}
