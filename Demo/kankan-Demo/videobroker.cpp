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

    video->init();      //实例化Video中的Comment和VideoFile对象
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
    long user_id = 0;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());    //稿件id
        parameters.push_back(res->getString(2).c_str());    //稿件描述
        parameters.push_back(res->getString(3).c_str());    //稿件标题
        parameters.push_back(res->getString(4).c_str());    //标签
        parameters.push_back(res->getString(5).c_str());    //分区
        isOriginal = res->getBoolean(6);                    //是否为原创
        parameters.push_back(res->getString(7).c_str());    //封面
        parameters.push_back(res->getString(8).c_str());    //发布日期
        user_id = res->getLong(9);
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

    Video v(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], isOriginal, parameters[5], parameters[6], user_id, commentIds, result);

    std::cout << "Video对象实例化成功" << std::endl;
    _oldClean.insert({id, v});
    return std::make_shared<Video>(_oldClean.at(id));
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

    if (_newDelete.count(id)) {
        return std::make_shared<Video>(_newDelete.at(id));
    }

    if (_oldClean.count(id)) {
        return std::make_shared<Video>(_oldClean.at(id));
    }

    if (_oldDirty.count(id)) {
        return std::make_shared<Video>(_oldDirty.at(id));
    }

    if (_oldDelete.count(id)) {
        return std::make_shared<Video>(_oldDelete.at(id));
    }

    return nullptr;
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
    if (!_newClean.empty() || !_newClean.empty()) {
        std::string sql = "insert into user values ";
        for(auto iter = _newClean.begin(); iter != _newClean.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('"+ iter->first+ "','"+ iter->second.description()+ "','"+ iter->second.title() + "','" + iter->second.label() + "','" + iter->second.subarea() + "','" + std::to_string(iter->second.isOriginal()) + "','" + iter->second.cover() + "','" + iter->second.date() + "'," + std::to_string(iter->second.user_id()) + "),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(iter++);
        }

        for(auto it = _newDirty.begin(); it != _newDirty.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "('"+ it->first+ "','"+ it->second.description()+ "','"+ it->second.title() + "','" + it->second.label() + "','" + it->second.subarea() + "','" + std::to_string(it->second.isOriginal()) + "','" + it->second.cover() + "','" + it->second.date() + "'," + std::to_string(it->second.user_id()) + "),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(it++);
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
        del(sql);
        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _oldDelete.erase(it++);
    }
}

void VideoBroker::cacheUpdate()
{

}
