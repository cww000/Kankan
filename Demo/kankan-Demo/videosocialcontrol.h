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
//   Description: 主要实现控制层的相关的操作，网民登陆、注册、观看视频、评论、发布视频等都需要该控制器对象来将具体实现向下提交，减少业务逻辑和数据访问逻辑之间的耦合

#ifndef VIDEOSOCIALCONTROL_H
#define VIDEOSOCIALCONTROL_H

#include <string>
#include <memory>
#include <vector>
#include "mytimer.h"
#include "json.hpp"
class Netizen;

class VideoSocialControl
{
public:
    VideoSocialControl();
    ~VideoSocialControl();
    //注册
    //key:用户设置的密码
    void login(std::string key);

    //登录
    //id:用户输入的帐号
    //key:用户输入的密码
    void login(std::string id, std::string key);

    //假设服务器记录每次上传视频的id，保存为一个列表，首页总是显示最新的一批视频
    void getSomeVideos(std::vector<std::string> ids);

    //选择查看某个稿件
    void checkOneVideo(std::string netizenId, std::string videoId);

    //合并视频
    std::string mergeVideoFiles(std::vector<std::string> videoFiles);

    //生成稿件
    void createVideo(std::string netizenId, nlohmann::json video);

    //删除稿件
    void deleteVideo(std::string netizenId, const std::string& videoId);

    //发表评论
    void commentVideo(const std::string& content,std::string netizenId, const std::string videoId);

    //关注
    void follow(std::string netizenId, std::string followerId);

    //浏览未读消息列表
    void browseMessage(std::string netizenId);
    //查看某条未读消息
    void checkOneMessage(std::string netizenId, std::string messageId);

    //修改个人信息
    void updateAcountInfo(std::string netizenId, std::string key, std::string headPortrait, std::string nickname);

    //修改网民自己的已发布稿件信息
    void updateVideoInfo(std::string netizenId, nlohmann::json newVideo);

private:
    static void flush();
    static void notificationFlush();
    MyTimer m_timer;
    MyTimer m_notiifyTimer;
};

#endif // VIDEOSOCIALCONTROL_H
