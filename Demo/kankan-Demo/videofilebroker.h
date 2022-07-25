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
//   Description: 主要实现查找数据库，获取数据库中视频文件的相关信息并放入对应缓存，或者添加、删除或更新数据库中该视频文件的信息

#ifndef VIDEOFILEBROKER_H
#define VIDEOFILEBROKER_H

#include "relationalbroker.h"
#include "videofile.h"
#include <mutex>
class VideoFileBroker : public RelationalBroker
{
public:
    virtual ~VideoFileBroker();
    static VideoFileBroker* getInstance();
    static void flush();
    std::shared_ptr<VideoFile> getVideoFile(const std::string& id);
    std::shared_ptr<VideoFile> retrieveVideoFile(const std::string& id);
    void addVideoFile(const std::string& id, const VideoFile& videoFile);
    //删除视频文件
    void deleteVideoFile(const std::string& id, const VideoFile& videoFile);
    void updateVideoFile(const std::string& id, const VideoFile& videoFile);
private:
    VideoFileBroker();
    static VideoFileBroker* m_videoFileBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, VideoFile> _newClean;  //新的净缓存
    static std::unordered_map<std::string, VideoFile> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, VideoFile> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, VideoFile> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, VideoFile> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, VideoFile> _oldDelete; //旧的删除缓存

    static void cacheFlush();    //将数据写入数据库
    static void cacheDel();      //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<VideoFile> inCache(std::string id);   //判断是否在缓存中
    int judgeFrom(const std::string& id); //判断要更新的数据是在哪一个缓存
};

#endif // VIDEOFILEBROKER_H
