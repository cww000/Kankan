// Copyright (C) Microsoft. All rights reserved. License (BSD/MIT/GPL)
// Project: kankan-Demo
//
// Author: Wenwen Cheng WennCheng@163.com)
// Date: 2022-07-25
// Version: 0.1.0
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Project description: kankan is a multimedia social platform based on video, and it is mainly for those who want to create and share, or spend their free time. It mainly provides people with the opportunity to disseminate videos and watch videos.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This file is part of kankan-Demo.
// History:
// 1.Modified by Wenwen Cheng (WennCheng@163.com) 2022-07-25
//   Description: 主要实现网民的相关操作，如：发布视频，发布视频，发布评论，删除评论，修改账户信息，修改视频信息，以及获取自身相关数据（关注者信息，粉丝信息，评论，已发布视频，头像，昵称等）。

#ifndef NETIZEN_H
#define NETIZEN_H

#include <string>
#include <unordered_map>
#include <utility>
#include "videoproxy.h"
#include "netizenproxy.h"
#include "json.hpp"
#include <vector>
#include <set>
class Netizen
{
public:
    Netizen(std::string id, std::string key);
    ~Netizen();

    //创造insert的sql语句
    std::string insertSql();

    //获取用户id,昵称，所有的稿件id，粉丝的id，关注者的id
    //id:用户id
    //nickname:用户昵称
    //videosId:稿件的id
    //fansId:粉丝的id
    //followersId:关注者的id
    Netizen(std::string id, std::string nickname, std::string headPortrait, std::vector<std::string> videosId,
            std::vector<std::string> fansId, std::vector<std::string> followersId);

    //登录后进行信息初始化
    void init();

    //返回网民的昵称和头像
    nlohmann::json getInfo();

    //评论
    void comment(const std::string& content, const std::string& videoId);

    //发布稿件
    void publishVideo(nlohmann::json video);
    //关注
    void follow(std::string followerId);

    //添加粉丝
    void addFan(std::string fanId, const Netizen* fan);

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

    //浏览未读消息列表
    void browseMessage();
    //选择查看某条消息
    void checkOneMessage(const std::string& messageId);

    //修改个人信息
    void updateAcountInfo(std::string key, std::string headPortrait, std::string nickname);
    //修改已发布稿件信息
    void updateVideoInfo(nlohmann::json newVideo);

    //选择查看某个稿件
    void checkOneVideo(const std::string& videoId);


private:
    std::string m_id;                                                      //用户id
    std::string m_headPortrait;                                     //用户头像
    std::string m_key;                                              //用户密码
    std::string m_nickname;                                         //用户昵称
    std::unordered_map<std::string, VideoProxy> _videos;            //稿件(稿件id，代理)
    std::unordered_map<std::string, NetizenProxy> _fans;                   //粉丝(粉丝id，代理)
    std::unordered_map<std::string, NetizenProxy> _followers;              //关注者(关注者id, 代理)

    bool m_online;
    std::set<std::string> _message;
};

#endif // NETIZEN_H
