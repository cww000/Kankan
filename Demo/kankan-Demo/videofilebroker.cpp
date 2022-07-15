#include "videofilebroker.h"
#include <iostream>

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

std::shared_ptr<VideoFile> VideoFileBroker::getVideoFile(std::string &id)
{
    //检查是否存在缓存中

    //检索数据库，创建videofile对象
    std::vector<std::string> parameters;
    std::string sql = "select * from videoFile where id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
        parameters.push_back(res->getString(3).c_str());
    }

    std::shared_ptr<VideoFile> videoFile = std::make_shared<VideoFile>(parameters[0], parameters[1], parameters[2]);

    //返回videofile对象
    std::cout << "VideoFile对象实例化成功" ;
    return videoFile;
}

VideoFileBroker::VideoFileBroker()
{

}
