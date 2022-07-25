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
//   Description: 利用观察者模式，实现向实例化的通知中注册、删除、通知观察者，并可以返回该通知的相关数据

#ifndef PUBLISHVIDEONOTIFICATION_H
#define PUBLISHVIDEONOTIFICATION_H

#include <string>
#include <unordered_map>
#include "netizenproxy.h"
class PublishVideoNotification
{
public:
    explicit PublishVideoNotification(std::string id, std::string senderId, std::unordered_map<std::string, NetizenProxy> observer, std::string content, std::string date, std::string videoId);
    explicit PublishVideoNotification(std::string id, std::string content, std::string date, std::string senderId, std::string videoId);
    ~PublishVideoNotification();

    //注册订阅者
    void registerObserver(std::string observerId);
    //删除订阅者
    void removeObserver(std::string observerId);
    //通知订阅者
    void notifyObserver();

    bool hasReadAll() {return _observer.empty();}

    const std::string id() {return m_id;}
    std::string senderId() {return m_senderId;}
    const std::string date() {return m_date;}
    const std::string videoId() {return m_videoId;}
    const std::string content() {return m_content;}
    const std::unordered_map<std::string, NetizenProxy> observer() {return _observer;}

private:
    std::string m_id;
    std::string m_senderId;
    std::unordered_map<std::string, NetizenProxy> _observer;
    std::string m_content;
    std::string m_date;
    std::string m_videoId;
};

#endif // PUBLISHVIDEONOTIFICATION_H
