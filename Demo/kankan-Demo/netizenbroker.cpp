#include <iostream>
#include "netizen.h"
#include "netizenbroker.h"

NetizenBroker* NetizenBroker::m_netizenBroker = nullptr;
std::mutex NetizenBroker::m_mutex = {};
std::unordered_map<long, Netizen> NetizenBroker::_newClean = {};
std::unordered_map<long, Netizen> NetizenBroker::_newDirty = {};
std::unordered_map<long, Netizen> NetizenBroker::_newDelete = {};
std::unordered_map<long, Netizen> NetizenBroker::_oldClean = {};
std::unordered_map<long, Netizen> NetizenBroker::_oldDirty = {};
std::unordered_map<long, Netizen> NetizenBroker::_oldDelete = {};

NetizenBroker::NetizenBroker()
{

}

NetizenBroker::~NetizenBroker()
{
    flush();
}

NetizenBroker *NetizenBroker::getInstance()
{
    if (m_netizenBroker == nullptr)
        m_netizenBroker = new NetizenBroker();
    return m_netizenBroker;
}

bool NetizenBroker::qualifyNetizenId(long id)
{
    //根据id查找,如果找到返回true,否则返回false
    std::string sql = "select user_id from user";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        if (id == res->getInt(1))
            return true;
    }

    return false;
}

std::shared_ptr<Netizen> NetizenBroker::inCache(long id)
{
    //判断是否在缓存中

    if (_newClean.count(id)) {
        return std::make_shared<Netizen>(_newClean.at(id));
    }

    if (_newDirty.count(id)) {
        return std::make_shared<Netizen>(_newDirty.at(id));
    }

//    if (_newDelete.count(id)) {
//        return std::make_shared<Netizen>(_newDelete.at(id));
//    }

    if (_oldClean.count(id)) {
        return std::make_shared<Netizen>(_oldClean.at(id));
    }

    if (_oldDirty.count(id)) {
        return std::make_shared<Netizen>(_oldDirty.at(id));
    }

//    if (_oldDelete.count(id)) {
//        return std::make_shared<Netizen>(_oldDelete.at(id));
//    }

    return nullptr;
}

int NetizenBroker::judgeFromForUpdate(long id)
{
    if (_newClean.count(id)) return 0;  //如果在新的净缓存中
    if (_newDirty.count(id)) return 1;
    if (_oldDirty.count(id)) return 2;

    return 3;  //在旧的净缓存中
}


void NetizenBroker::cacheFlush()
{
    if (!_newClean.empty() || !_newDirty.empty()) {
        std::string sql = "insert into user values";
        for(auto iter = _newClean.begin(); iter != _newClean.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "(" + std::to_string(iter->first) + ",'"+ iter->second.key()+ "','"+ iter->second.nickname()+ "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newClean.erase(iter++);
        }

        for(auto it = _newDirty.begin(); it != _newDirty.end();){

            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            sql += "("+ std::to_string(it->first) + ",'" + it->second.key() + "','" + it->second.nickname() + "'),";

            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _newDirty.erase(it++);
        }

        if (!sql.empty()) sql.pop_back();
        std::cout << sql << std::endl;
        insert(sql);   //执行批量插入，插入新的净缓存和新的脏缓存中的数据
    }
}
void NetizenBroker::cacheDel()
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

        std::string sql = "delete from user where id=" + std::to_string(it->first);
        std::cout << sql << std::endl;
        del(sql);
        //从对应缓存中删除相关数据
        //erase的返回值是一个迭代器，指向删除元素下一个元素。
        _oldDelete.erase(it++);
    }
}
void NetizenBroker::cacheUpdate()
{
    if (!_oldDirty.empty()) {
        for (auto iter = _oldDirty.begin(); iter != _oldDirty.end();) {
            //应该保证当进行插入时，数据是不可以被其他线程所更改的
            std::lock_guard<std::mutex> lk(m_mutex);

            std::string sql = "update user set user_key='"+ iter->second.key()+ "', user_nickname='"+ iter->second.nickname()+ "' where user_id=" + std::to_string(iter->first);

            std::cout << sql << std::endl;
            update(sql);
            //从对应缓存中删除相关数据
            //erase的返回值是一个迭代器，指向删除元素下一个元素。
            _oldDirty.erase(iter++);
        }
    }
}

void NetizenBroker::flush()
{
    cacheFlush();
    cacheDel();
    cacheUpdate();
}

bool NetizenBroker::qualifyNetizenKey(long id, std::string key)
{
    //验证对应id的密码，正确返回true,错误返回false
    std::string sql = "select user_id, user_key from user";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next()) {
        if (id == res->getInt(1) && key == res->getString(2))
            return true;
    }

    return false;
}

void NetizenBroker::insertNewNetizen(std::shared_ptr<Netizen> netizen)
{
    std::string sql = netizen->insertSql();
    std::cout << sql << std::endl;
    insert(sql);
}

std::shared_ptr<Netizen> NetizenBroker::findNetizenById(long id)
{
    //检查用户是否在缓存中
    std::shared_ptr<Netizen> netizen = inCache(id);
    if (netizen == nullptr) {
        return retrieveNetizen(id);
    }

    return netizen;
}

std::shared_ptr<Netizen> NetizenBroker::retrieveNetizen(const long id)
{
    //查找数据库，找出用户的nickname
    std::string nickname;

    std::string sql = "select user_nickname from user where user_id = " + std::to_string(id);
    std::shared_ptr<sql::ResultSet> res = query(sql);
    while (res->next())
        nickname = res->getString(1).c_str();
    std::cout << "用户名：" << nickname << std::endl;

    //调用Netizen(id, nickname, videosId, fansId, followersId);
    Netizen net(id,nickname, "www.cv", findNetizenVideos(id), findNetizenFans(id), findNetizenFollowers(id));
    std::cout << "Netizen对象实例化成功" << std::endl;

     _oldClean.insert({id,  net});   //将从数据库中获取的对象添加到缓存
    return std::make_shared<Netizen>(_oldClean.at(id));
}

std::vector<std::string> NetizenBroker::findNetizenVideos(const long id)
{
    std::string sql = "select id from video where user_id = " + std::to_string(id);
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> videoIds;
    while (res->next()) {
        videoIds.push_back(res->getString(1).c_str());
    }

    return videoIds;
}

std::vector<long> NetizenBroker::findNetizenFans(const long id)
{
    std::string sql = "select fan_id from fan where user_id = " + std::to_string(id);
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<long> fanIds;
    while (res->next()) {
        fanIds.push_back(res->getLong(1));
    }

    return fanIds;
}

std::vector<long> NetizenBroker::findNetizenFollowers(const long id)
{
    std::string sql = "select follower_id from follower where user_id = " + std::to_string(id);
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<long> followerIds;
    while (res->next()) {
        followerIds.push_back(res->getLong(1));
    }

    return followerIds;
}

void NetizenBroker::addNetizen(long id, const Netizen &netizen)
{
    _newClean.insert({id, netizen});
}

void NetizenBroker::updateAcountInfo(long id, const Netizen &netizen)
{
    int n = judgeFromForUpdate(id);
    if (n == 0) {
        _newClean.erase(id);    //删除新的净缓存中对应的网民数据
        _newDirty.insert({id, netizen});   //添加新的网民数据到新的脏缓存中
    } else if (n == 1) {
        _newDirty.erase(id);    //替换新的脏缓存中原有对应网民的数据
        _newDirty.insert({id, netizen});
    } else if (n == 2) {
        _oldDirty.erase(id);
        _oldDirty.insert({id, netizen});   //替换旧的脏缓存中原有对应网民的数据
    } else {
        _oldClean.erase(id);
        _oldDirty.insert({id, netizen});
    }
}


