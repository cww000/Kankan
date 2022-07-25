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
//   Description: 作为视频文件的代理，主要实现了从对应代管者中获取视频文件相关数据，以此并实例化视频文件对象

#ifndef VIDEOFILEPROXY_H
#define VIDEOFILEPROXY_H

#include <memory>
#include <vector>
#include <string>
#include "json.hpp"
class VideoFile;

class VideoFileProxy
{
public:
    VideoFileProxy(std::string& id);
    ~VideoFileProxy();

    nlohmann::json getVideoFileInfo(std::string id);
private:
    std::string m_id;
    std::shared_ptr<VideoFile> m_videoFile;
};

#endif // VIDEOFILEPROXY_H
