#include "videofilebroker.h"
#include <iostream>

VideoFileBroker* VideoFileBroker::m_videoFileBroker = nullptr;
std::mutex VideoFileBroker::m_mutex = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_newClean = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_newDirty = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_newDelete = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_oldClean = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_oldDirty = {};
std::unordered_map<std::string, VideoFile> VideoFileBroker::_oldDelete = {};

VideoFileBroker::~VideoFileBroker()
{
    flush();
}

VideoFileBroker *VideoFileBroker::getInstance()
{
    if (m_videoFileBroker == nullptr)
        m_videoFileBroker = new VideoFileBroker();
    return m_videoFileBroker;
}

std::shared_ptr<VideoFile> VideoFileBroker::getVideoFile(const std::string &id)
{
    //检查是否存在缓存中
    std::shared_ptr<VideoFile> videoFile = inCache(id);
    if (videoFile == nullptr) {
        return retrieveVideoFile(id);  //若没有在缓存中找到，就去查找数据库
    }
    return videoFile;
}

std::shared_ptr<VideoFile> VideoFileBroker::retrieveVideoFile(const std::string &id)
{
    //检索数据库，创建videofile对象
    std::vector<std::string> parameters;
    std::string sql = "select * from videoFile where id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
        parameters.push_back(res->getString(3).c_str());
    }

    VideoFile vf(parameters[0], parameters[1], parameters[2]);
    //返回videofile对象
    std::cout << "VideoFile对象实例化成功" << std::endl;
    _oldClean.insert({id, vf});
    return std::make_shared<VideoFile>(_oldClean.at(id));
}

void VideoFileBroker::addVideoFile(const std::string &id, const VideoFile &videoFile)
{
    _newClean.insert({id, videoFile});
}


std::shared_ptr<VideoFile> VideoFileBroker::inCache(std::string id)
{
    //判断是否在缓存中

    if (_newClean.count(id)) {
        return std::make_shared<VideoFile>(_newClean.at(id));
    }

    if (_newDirty.count(id)) {
        return std::make_shared<VideoFile>(_newDirty.at(id));
    }

    if (_newDelete.count(id)) {
        return std::make_shared<VideoFile>(_newDelete.at(id));
    }

    if (_oldClean.count(id)) {
        return std::make_shared<VideoFile>(_oldClean.at(id));
    }

    if (_oldDirty.count(id)) {
        return std::make_shared<VideoFile>(_oldDirty.at(id));
    }

    if (_oldDelete.count(id)) {
        return std::make_shared<VideoFile>(_oldDelete.at(id));
    }

    return nullptr;
}

VideoFileBroker::VideoFileBroker()
{

}

void VideoFileBroker::cacheFlush()
{
    if (!_newClean.empty() || !_newClean.empty()) {
        std::string sql = "insert into comment values ";
        for(auto iter = _newClean.begin(); iter != _newClean.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('" + iter->first+ "','" + iter->second.address() + "','" + iter->second.videoId() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(iter++);
        }

        for(auto it = _newDirty.begin(); it != _newDirty.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('" + it->first+ "','" + it->second.address() + "','" + it->second.videoId() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(it++);
        }

        if (!sql.empty()) sql.pop_back(); //去掉最后一个逗号
        std::cout << sql << std::endl;
        insert(sql);   //执行批量插入，插入新的净缓存和新的脏缓存中的数据
    }
}

void VideoFileBroker::cacheUpdate()
{

}

void VideoFileBroker::cacheDel()
{
    for(auto iter = _newDelete.begin(); iter != _newDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _newDelete.erase(iter++);  //删除新的 删除缓存
    }

    for(auto it = _oldDelete.begin(); it != _oldDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        std::string sql = "delete from videofile where id=" + it->first;
        del(sql);
        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _oldDelete.erase(it++);    //删除旧的 删除缓存
    }
}

void VideoFileBroker::flush()
{
    cacheFlush();
    cacheDel();
//    cacheUpdate();
}
