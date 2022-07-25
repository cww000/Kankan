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
//   Description: 主要实现返回已实例化的视频文件的相关数据

#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <string>
#include <vector>
#include "json.hpp"
class VideoFile
{
public:
    VideoFile(std::string id, std::string address, std::string videoId);
    ~VideoFile();
    std::string getDuration(){ return m_duration; };   //返回视频的时长
    const std::string address() const;
    const std::string videoId() const;
    nlohmann::json getVideoFileInfo();


private:
    std::string m_id;           //
    std::string m_duration;     //视频时长
    std::string m_address;
    std::string m_videoId;
};

#endif // VIDEOFILE_H
