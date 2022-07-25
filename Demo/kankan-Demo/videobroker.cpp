#include "videobroker.h"
#include <vector>
#include <iostream>

VideoBroker* VideoBroker::m_videoBroker = nullptr;
std::mutex VideoBroker::m_mutex = {};
std::unordered_map<std::string, Video> VideoBroker::_newClean = {};
std::unordered_map<std::string, Video> VideoBroker::_newDirty = {};
std::unordered_map<std::string, Video> VideoBroker::_newDelete = {};
std::unordered_map<std::string, Video> VideoBroker::_oldClean = {};
std::unordered_map<std::string, Video> VideoBroker::_oldDirty = {};
std::unordered_map<std::string, Video> VideoBroker::_oldDelete = {};

VideoBroker::~VideoBroker()
{
    flush();
}

VideoBroker *VideoBroker::getInstance()
{
    if (m_videoBroker == nullptr)
        m_videoBroker = new VideoBroker();
    return m_videoBroker;
}

std::shared_ptr<Video> VideoBroker::getVideo(const std::string& id)
{
    //检查对象是否存在于缓存中
    std::shared_ptr<Video> video = inCache(id);
    if (video == nullptr) {
        return retrieveVideo(id);
    }

  //  video->init();      //实例化Video中的Comment和VideoFile对象
    //返回video对象
    return video;
}

std::shared_ptr<Video> VideoBroker::retrieveVideo(const std::string &id)
{
    //检索数据库，创建video对象
    std::string sql = "select * from video where id = '" + id + "'";

    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    bool isOriginal = false;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());    //稿件id
        parameters.push_back(res->getString(2).c_str());    //稿件描述
        parameters.push_back(res->getString(3).c_str());    //稿件标题
        parameters.push_back(res->getString(4).c_str());    //标签
        parameters.push_back(res->getString(5).c_str());    //分区
        isOriginal = res->getBoolean(6);                    //是否为原创
        parameters.push_back(res->getString(7).c_str());    //封面
        parameters.push_back(res->getString(8).c_str());    //发布日期
        parameters.push_back(res->getString(9).c_str());    //发布者id
    }


    std::vector<std::string> commentIds;
    sql = "select id from comment where videoId = '" + id + "'";

    res = query(sql);
    while (res->next())
        commentIds.push_back(res->getString(1).c_str());

    sql = "select id from videoFile where videoId = '" + id + "'";

    res = query(sql);
    std::string result;
    while (res->next())
        result = res->getString(1).c_str();

    Video v(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], isOriginal, parameters[5], parameters[6], parameters[7], commentIds, result);

  //  std::cout << "Video对象实例化成功" << std::endl;

    //将从数据库中读出来的数据添加到旧的净缓存
    _oldClean.insert({id, v});
    return std::make_shared<Video>(_oldClean.at(id));
}

void VideoBroker::addVideo(const std::string &id, const Video &video)
{
    _newClean.insert({id, video});
}

void VideoBroker::deleteVideo(const std::string &id, const Video &video)
{
    int n = judgeFrom(id);     //判断稿件是在哪一个缓存
    if (n == 0) {
        //如果该对象是在新的净缓存中
        //将该对象从新的净缓存移动到新的删除缓存
        _newClean.erase(id);
        _newDelete.insert({id, video});
    } else if (n == 1){
        //如果该对象是在新的脏缓存中
        //将该对象从新的脏缓存移动到新的删除缓存
        _newDirty.erase(id);
        _newDelete.insert({id, video});
    } else if (n == 2) {
        //如果该对象是在旧的脏缓存中
        //将该对象从旧的脏缓存移动到旧的删除缓存
        _oldDirty.erase(id);
        _oldDelete.insert({id, video});
    } else {
        //如果该对象是在旧的净缓存中
        //将该对象从旧的净缓存移动到旧的删除缓存
        _oldClean.erase(id);
        _oldDelete.insert({id, video});
    }
}

void VideoBroker::updateVideo(const std::string &videoId, const Video &video)
{
    int n = judgeFrom(videoId);
    if (n == 0) {
        _newClean.erase(videoId);    //删除新的净缓存中对应的网数据
        _newDirty.insert({videoId, video});   //添加新的数据到新的脏缓存中
    } else if (n == 1) {
        _newDirty.erase(videoId);    //替换新的脏缓存中原有对应的数据
        _newDirty.insert({videoId, video});
    } else if (n == 2) {
        _oldDirty.erase(videoId);
        _oldDirty.insert({videoId, video});   //替换旧的脏缓存中原有对应的数据
    } else {
        _oldClean.erase(videoId);
        _oldDirty.insert({videoId, video});
    }
}

std::shared_ptr<Video> VideoBroker::inCache(std::string id)
{
    //判断是否在缓存中

    if (_newClean.count(id)) {
        return std::make_shared<Video>(_newClean.at(id));
    }

    if (_newDirty.count(id)) {
        return std::make_shared<Video>(_newDirty.at(id));
    }

//    if (_newDelete.count(id)) {
//        return std::make_shared<Video>(_newDelete.at(id));
//    }

    if (_oldClean.count(id)) {
        return std::make_shared<Video>(_oldClean.at(id));
    }

    if (_oldDirty.count(id)) {
        return std::make_shared<Video>(_oldDirty.at(id));
    }

//    if (_oldDelete.count(id)) {
//        return std::make_shared<Video>(_oldDelete.at(id));
//    }

    return nullptr;
}

int VideoBroker::judgeFrom(const std::string &videoId)
{
    if (_newClean.count(videoId)) return 0;  //如果在新的净缓存中
    if (_newDirty.count(videoId)) return 1;
    if (_oldDirty.count(videoId)) return 2;

    return 3;  //在旧的净缓存中(包括刚从数据库读出来的数据）
}

VideoBroker::VideoBroker()
{

}

void VideoBroker::flush()
{
    cacheFlush();
    cacheDel();
    cacheUpdate();
}

void VideoBroker::cacheFlush()
{
    if (!_newClean.empty() || !_newDirty.empty()) {
        std::string sql = "insert into video values";
        for(auto iter = _newClean.begin(); iter != _newClean.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('"+ iter->first+ "','"+ iter->second.description()+ "','"+ iter->second.title() + "','" + iter->second.label() + "','" + iter->second.subarea() + "','" + std::to_string(iter->second.isOriginal()) + "','" + iter->second.cover() + "','" + iter->second.date() + "','" + iter->second.user_id() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(iter++);
        }

        for(auto it = _newDirty.begin(); it != _newDirty.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('"+ it->first+ "','"+ it->second.description()+ "','"+ it->second.title() + "','" + it->second.label() + "','" + it->second.subarea() + "','" + std::to_string(it->second.isOriginal()) + "','" + it->second.cover() + "','" + it->second.date() + "','" + it->second.user_id() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newDirty.erase(it++);
        }

        if (!sql.empty()) sql.pop_back();
        std::cout << sql << std::endl;
        insert(sql);   //执行批量插入，插入新的净缓存和新的脏缓存中的数据
    }
}

void VideoBroker::cacheDel()
{
    for(auto iter = _newDelete.begin(); iter != _newDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _newDelete.erase(iter++);
    }

    for(auto it = _oldDelete.begin(); it != _oldDelete.end();){

        //应该保证当进行插入时，数据是不可以被其他线程所更改的
        std::lock_guard<std::mutex> lk(m_mutex);

        std::string sql = "delete from video where id='" + it->first + "'";
        std::cout << sql << std::endl;
        del(sql);
        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _oldDelete.erase(it++);
    }
}

void VideoBroker::cacheUpdate()
{
    if (!_oldDirty.empty()) {
        for (auto iter = _oldDirty.begin(); iter != _oldDirty.end();) {
            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            std::string sql = "update video set description='"+ iter->second.description()+ "', title='"+ iter->second.title() + "', label='" + iter->second.label() + "', subarea='" + iter->second.subarea() + "', isOriginal='" + std::to_string(iter->second.isOriginal()) + "', cover='" + iter->second.cover() + "', date='" + iter->second.date()+ "', user_id='" + iter->second.user_id() + "' where id='" + iter->first + "'";

            std::cout << sql << std::endl;
            update(sql);
            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _oldDirty.erase(iter++);
        }
    }
}
