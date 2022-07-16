#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <unordered_map>
#include <utility>
#include "videoproxy.h"
#include "netizenproxy.h"
#include "netizeninterface.h"
#include <vector>
#include <set>
class Netizen
{
public:
    Netizen(long id, std::string key);
    ~Netizen();

    //创造insert的sql语句
    std::string insertSql();



    //获取用户id,昵称，所有的稿件id，粉丝的id，关注者的id
    //id:用户id
    //nickname:用户昵称
    //videosId:稿件的id
    //fansId:粉丝的id
    //followersId:关注者的id
    Netizen(long id, std::string nickname, std::string headPortrait, std::vector<std::string> videosId,
            std::vector<long> fansId, std::vector<long> followersId);

    //登录后进行信息初始化
    void init();

    //返回网民的昵称和头像
    std::vector<std::string> getInfo();

    //评论
    void comment(const std::string& content, const std::string& videoId);
    //发布稿件
    void publishVideo(std::string description, std::string title, std::string label, std::string subarea, bool isOriginal, std::string cover, std::string date, std::string videoFileId);
    //关注
    void follow(long followerId);

    //添加粉丝
    void addFan(long fanId, const Netizen* fan);

    //删除稿件
    void deleteVideo(const std::string& videoId);

    //添加新的稿件给网民
    void addNewVideo(std::string& id);

    const std::string key() const;
    const std::string nickname() const;

    bool online() {return m_online;}
    void setOnline(bool online) {m_online = online;}  //设置网民在线或离线

    //添加一条未查看消息
    void updateMessage(const std::string& messageId);
    //选择查看某条消息
    void checkOneMessage(const std::string& messageId);


private:

    void checkOneVideo(const std::string& videoId);
    long m_id;                                                      //用户id
    std::string m_headPortrait;                                     //用户头像
    std::string m_key;                                              //用户密码
    std::string m_nickname;                                         //用户昵称
    std::unordered_map<std::string, VideoProxy> _videos;            //稿件(稿件id，代理)
    std::unordered_map<long, NetizenProxy> _fans;                   //粉丝(粉丝id，代理)
    std::unordered_map<long, NetizenProxy> _followers;              //关注者(关注者id, 代理)

    bool m_online;
    std::set<std::string> _message;
};

#endif // NETIZEN_H
