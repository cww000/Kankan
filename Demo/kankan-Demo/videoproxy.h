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
//   Description: 主要实现向视频的代管者获取数据，并实例化视频对象

#ifndef VIDEOPROXY_H
#define VIDEOPROXY_H

#include <memory>
#include <vector>
#include <string>
#include "json.hpp"

class Video;

class VideoProxy
{
public:
    VideoProxy(std::string id);
    nlohmann::json getVideoInfo(const std::string& id);
    //获取稿件的相关信息(发布时间、封面、视频时长、标题)
    //id：稿件id

    ~VideoProxy();
private:
    std::string m_id;
    std::shared_ptr<Video> m_video;
};

#endif // VIDEOPROXY_H
