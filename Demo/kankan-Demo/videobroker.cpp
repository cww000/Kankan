#include "videobroker.h"

VideoBroker* VideoBroker::m_videoBroker = nullptr;

VideoBroker::~VideoBroker()
{

}

VideoBroker *VideoBroker::getInstance()
{
    if (m_videoBroker == nullptr)
        m_videoBroker = new VideoBroker();
    return m_videoBroker;
}

std::shared_ptr<Video> VideoBroker::getVideo(std::string &id)
{
    //检查对象是否存在于缓存中

    //检索数据库，创建video对象


    //返回对象之前实例化videofile对象，实例化评论对象

    //返回video对象

}



VideoBroker::VideoBroker()
{

}
