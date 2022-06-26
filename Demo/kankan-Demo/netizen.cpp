#include "netizen.h"
#include <string>

Netizen::Netizen(long id, std::string key) :
    m_id{id}, m_key{key}
{
    //生成默认用户名
    m_nickname = "kk_" + std::to_string(id);
}

Netizen::Netizen(long id, std::string nickname, std::vector<std::string> videosId,
                 std::vector<long> fansId, std::vector<long> followersId) :
    m_id{id}, m_nickname{nickname}
{
    for (auto vId : videosId)
        _videos.insert(std::make_pair(vId, VideoProxy(vId)));
    for (auto fanId : fansId)
        _fans.insert(std::make_pair(fanId, NetizenProxy(fanId)));
    for (auto followerId : followersId)
        _followers.insert(std::make_pair(followerId, NetizenProxy(followerId)));
}
