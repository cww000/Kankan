#include "videofilebroker.h"

VideoFileBroker* VideoFileBroker::m_videoFileBroker = nullptr;

VideoFileBroker::~VideoFileBroker()
{

}

VideoFileBroker *VideoFileBroker::getInstance()
{
    if (m_videoFileBroker == nullptr)
        m_videoFileBroker = new VideoFileBroker();
    return m_videoFileBroker;
}

VideoFile *VideoFileBroker::getVideoFile()
{
    //检查是否存在缓存中

    //检索数据库，创建videofile对象

    //返回videofile对象
}

VideoFileBroker::VideoFileBroker()
{

}
