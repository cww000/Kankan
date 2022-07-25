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
//   Description: 查找数据库，获取数据库中相关的视频数据，实例化并返回给代理对象。再或者利用六个缓存来实现视频的更新、添加和删除，将要操作的视频对象添加到缓存，并定时刷新，写入数据库

#ifndef VIDEOBROKER_H
#define VIDEOBROKER_H

#include "relationalbroker.h"
#include "video.h"
#include <mutex>
class VideoBroker : public RelationalBroker
{
public:
    ~VideoBroker();
    static VideoBroker* getInstance();
    static void flush();
    std::shared_ptr<Video> getVideo(const std::string& id);
    std::shared_ptr<Video> retrieveVideo(const std::string& id);
    //添加新的到净缓存
    void addVideo(const std::string& id, const Video& video);
    //添加到删除缓存
    void deleteVideo(const std::string& id, const Video& video);

    void updateVideo(const std::string& videoId, const Video& video);
    //检索缓存以及数据库，返回video对象
    //id：稿件id

private:
    static VideoBroker* m_videoBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Video> _newClean;  //新的净缓存
    static std::unordered_map<std::string, Video> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Video> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Video> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, Video> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Video> _oldDelete; //旧的删除缓存

    VideoBroker();
    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Video> inCache(std::string id);   //判断是否在缓存中
    int judgeFrom(const std::string& videoId); //判断要更新的数据是在哪一个缓存
};

#endif // VIDEOBROKER_H
