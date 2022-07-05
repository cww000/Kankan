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

Netizen::Netizen(long id, std::string nickname, std::vector<std::string> videosId,
                 std::vector<long> fansId, std::vector<long> followersId) :
    m_id{id}, m_nickname{nickname}
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
    for (auto video : _videos)
        video.second.getVideoInfo(video.first);

    for (auto fan : _fans)
        fan.second.getInfo(fan.first);

    for (auto follower : _followers)
        follower.second.getInfo(follower.first);
}

std::vector<std::string> Netizen::getInfo()
{
    std::vector<std::string> results;
    results.push_back(m_headPortrait);
    results.push_back(m_nickname);

    return results;
}
