#include "netizenbroker.h"
#include "netizen.h"

NetizenBroker* NetizenBroker::m_netizenBroker = nullptr;

NetizenBroker *NetizenBroker::getInstance()
{
    if (m_netizenBroker == nullptr)
        m_netizenBroker = new NetizenBroker();
    return m_netizenBroker;
}

bool NetizenBroker::qualifyNetizenId(long id)
{
    //根据id查找,如果找到返回true,否则返回false
    return true;


    return false;
}

bool NetizenBroker::qualifyNetizenKey(long id, std::string key)
{
    //验证对应id的密码，正确返回true,错误返回false
    return true;

    return false;
}

void NetizenBroker::insertNewNetizen(std::shared_ptr<Netizen> netizen)
{

}

std::shared_ptr<Netizen> NetizenBroker::findNetizenById(long id)
{
    //检查用户是否在缓存中

    //查找数据库，找出用户的id,nickname

    std::string nickname;
    //调用Netizen(id, nickname, videosId, fansId, followersId);
    std::shared_ptr<Netizen> netizen = std::make_shared<Netizen>(id, nickname, findNetizenVideos(id),
                                                        findNetizenFans(id), findNetizenFollowers(id));

    return netizen;
}

std::vector<std::string> NetizenBroker::findNetizenVideos(const long id)
{

}

std::vector<long> NetizenBroker::findNetizenFans(const long id)
{

}

std::vector<long> NetizenBroker::findNetizenFollowers(const long id)
{

}

NetizenBroker::NetizenBroker()
{

}
