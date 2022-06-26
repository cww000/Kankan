#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include <memory>
#include "relationalbroker.h"
#include <vector>

class Netizen;

class NetizenBroker : public RelationalBroker
{
public:
    ~NetizenBroker();
    static NetizenBroker* getInstance();

    //根据用户ID检验用户是否存在
    //id：用户输入id
    bool qualifyNetizenId(long id);

    //检验用户的id与key是否匹配
    //id:用户输入id
    //key:用户输入密码key
    bool qualifyNetizenKey(long id, std::string key);

    //添加新的用户记录
    //netizen:新用户实体
    void insertNewNetizen(std::shared_ptr<Netizen> netizen);

    //通过用户id查找相关用户数据
    //id:用户id
    std::shared_ptr<Netizen> findNetizenById(const long id);

    //通过用户id查找所有稿件id
    std::vector<std::string> findNetizenVideos(const long id);

    //通过用户id查找所有粉丝id
    std::vector<long> findNetizenFans(const long id);

    //通过用户id查找所有关注者id
    std::vector<long> findNetizenFollowers(const long id);

    //判断当前用户是否在缓存中
    std::shared_ptr<Netizen> inCache(long id);
private:
    NetizenBroker();
    static NetizenBroker* m_netizenBroker;
};

#endif // NETIZENBROKER_H
