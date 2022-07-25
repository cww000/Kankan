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
//   Description: 主要实现了添加发送稿件的通知到消息队列，消息队列只有单例，或者删除某条已经发送给所有粉丝的通知，查找某条通知，并利用观察者模式，移除某个观察者或者更新消息队列

#ifndef MESSAGESEQUENCE_H
#define MESSAGESEQUENCE_H

#include "relationalbroker.h"
class PublishVideoNotification;
class MessageSequence : public RelationalBroker
{
public:

    ~MessageSequence();
    static MessageSequence* getInstance();

    //加入指定message
    void pushNotification(PublishVideoNotification notification);
    //删除指定message
    void removeNotification(std::string id);
    //获取指定message
    PublishVideoNotification* findById(const std::string& id);

    //更新消息队列
    void updateMessageQueue();
    //移除指定message的某个观察者
    void removeMessageObserver(std::string messageId,std::string observerId);

private:
    static MessageSequence* m_messageSeq;
    MessageSequence();
    std::unordered_map<std::string, PublishVideoNotification> m_messageQueue;
};

#endif // MESSAGESEQUENCE_H
