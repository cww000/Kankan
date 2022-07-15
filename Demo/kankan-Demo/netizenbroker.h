#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include <memory>
#include "relationalbroker.h"
#include <vector>
#include <mutex>
class Netizen;

class NetizenBroker : public RelationalBroker
{
public:
    ~NetizenBroker();
    static NetizenBroker* getInstance();
    static void flush();

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
    std::shared_ptr<Netizen> retrieveNetizen(const long id);

    //通过用户id查找所有稿件id
    std::vector<std::string> findNetizenVideos(const long id);

    //通过用户id查找所有粉丝id
    std::vector<long> findNetizenFans(const long id);

    //通过用户id查找所有关注者id
    std::vector<long> findNetizenFollowers(const long id);

private:
    NetizenBroker();
    static NetizenBroker* m_netizenBroker;
    static std::mutex m_mutex;
    static std::unordered_map<long, Netizen> _newClean;  //新的净缓存
    static std::unordered_map<long, Netizen> _newDirty;  //新的脏缓存
    static std::unordered_map<long, Netizen> _newDelete; //新的删除缓存
    static std::unordered_map<long, Netizen> _oldClean;  //旧的净缓存
    static std::unordered_map<long, Netizen> _oldDirty;  //旧的脏缓存
    static std::unordered_map<long, Netizen> _oldDelete; //旧的删除缓存

    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Netizen> inCache(long id);   //判断是否在缓存中

};

#endif // NETIZENBROKER_H
