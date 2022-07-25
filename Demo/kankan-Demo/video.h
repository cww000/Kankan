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
//   Description: 主要实现视频对象的构造和相关视频信息的返回，也可以添加评论到该视频对象中

#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "videofileproxy.h"
#include "commentproxy.h"
#include "json.hpp"
class VideoFile;
class Image;

class Video
{
public:
    Video() = delete;
    Video(std::string id, std::string description, std::string title, std::string label, std::string subarea, bool isOriginal, std::string cover, std::string date, std::string user_id, std::vector<std::string> commentIds, std::string videoFileId);
    ~Video();

    nlohmann::json getVideoInfo();
    //获取稿件的数据（标题、发布时间、视频时长[通过m_videoFile对象去获取时长]、封面）
    //后续可考虑替换为json传输

    //将新生成的评论添加到稿件中
    void addNewComment(std::string& id);

    //通过代理实例化videofile对象
    const std::string description() const;
    const std::string title() const;
    const std::string label() const;
    const std::string subarea() const;
    bool isOriginal() const;
    const std::string cover() const;
    const std::string date() const;
    const std::unordered_map<std::string, CommentProxy> comments() const;
    const std::pair<std::string, VideoFileProxy> videoFile() const;
    std::string user_id() const;

private:
    std::string m_id;           //稿件id
    std::string m_description;  //简介
    std::string m_title;        //标题
    std::string m_label;        //标签
    std::string m_subarea;      //分区
    bool m_isOriginal;          //是否是转载
    std::string m_cover;        //封面（存文件路径）
    std::string m_date;         //发布时间(后期需考虑是否使用date)
    std::string m_user_id;

    std::unordered_map<std::string, CommentProxy> _comments;
    std::pair<std::string, VideoFileProxy> m_videoFile;
};

#endif // VIDEO_H
