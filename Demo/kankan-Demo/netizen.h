#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <unordered_map>
#include <utility>
#include "videoproxy.h"
#include "netizenproxy.h"
#include "netizeninterface.h"
#include <vector>

class Netizen
{
public:
    Netizen(long id, std::string key);

    //创造insert的sql语句
    std::string insertSql();


    //获取用户id,昵称，所有的稿件id，粉丝的id，关注者的id
    //id:用户id
    //nickname:用户昵称
    //videosId:稿件的id
    //fansId:粉丝的id
    //followersId:关注者的id
    Netizen(long id, std::string nickname, std::vector<std::string> videosId, std::vector<long> fansId, std::vector<long> followersId);
private:
    long m_id;                                                      //用户id
    std::string m_key;                                              //用户密码
    std::string m_nickname;                                         //用户昵称
    std::unordered_map<std::string, VideoProxy> _videos;        //稿件(稿件id，代理)
    std::unordered_map<long, NetizenProxy> _fans;                   //粉丝(粉丝id，代理)
    std::unordered_map<long, NetizenProxy> _followers;              //关注者(关注者id, 代理)
};

#endif // NETIZEN_H
