#include "netizen.h"
#include <string>
#include <iostream>


Netizen::Netizen(long id, std::string key) :
    m_id{id}, m_key{key}
{
        m_nickname = "kk_" + std::to_string(id);     //生成默认用户名
}

Netizen::~Netizen()
{

}

std::string Netizen::insertSql()
{
    return "insert into user values( " + std::to_string(m_id) + ", '" + m_key + "', '" + m_nickname + "');";
}

Netizen::Netizen(long id, std::string nickname, std::string headPortrait, std::vector<std::string> videosId,
                 std::vector<long> fansId, std::vector<long> followersId) :
    m_id{id}, m_headPortrait{headPortrait}, m_key{" "}, m_nickname{nickname}
{
    for (auto vId : videosId) {
        _videos.insert(std::make_pair(vId, VideoProxy(vId)));
        std::cout << "稿件id：" ;
        std::cout << vId << std::endl;
    }

    for (auto fanId : fansId) {
        _fans.insert(std::make_pair(fanId, NetizenProxy(fanId)));
        std::cout << "粉丝id：" ;
        std::cout << fanId << std::endl;
    }

    for (auto followerId : followersId) {
        _followers.insert(std::make_pair(followerId, NetizenProxy(followerId)));
        std::cout << "关注者id：";
        std::cout << followerId << std::endl;
    }
}

void Netizen::init()
{
    //getVideoInfo如何存储返回的数据
    std::cout << "稿件信息：\n";
    for (auto video : _videos){
        video.second.getVideoInfo(video.first);
    }
    std::cout << "粉丝信息：\n";
    for (auto fan : _fans) {
        fan.second.getInfo(fan.first);
    }

    std::cout << "关注者信息：\n";
    for (auto follower : _followers) {
        follower.second.getInfo(follower.first);
    }
}

std::vector<std::string> Netizen::getInfo()
{
    std::vector<std::string> results;
    results.push_back(m_headPortrait);
    results.push_back(m_nickname);

    //测试
    std::cout << "NetizenInfo: " ;
    for (auto g : results)
        std::cout << g << "   ";
    std::cout << "\n";

    return results;
}

const std::string &Netizen::key() const
{
    return m_key;
}

const std::string &Netizen::nickname() const
{
    return m_nickname;
}
