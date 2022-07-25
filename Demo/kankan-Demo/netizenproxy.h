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
//   Description: 作为网民的代理，是要实现想起对应的代管者获取网民的相关数据,并更新应发送给对应网民的通知

#ifndef NETIZENPROXY_H
#define NETIZENPROXY_H

#include <memory>
#include <vector>
#include "json.hpp"

class Netizen;

class NetizenProxy
{
public:
    NetizenProxy(std::string id);
    ~NetizenProxy();

    nlohmann::json getInfo(std::string id);
    bool isOnline();
    void updateMessage(std::string messageId);
private:
    std::string m_id;
    std::shared_ptr<Netizen> m_netizen;
};

#endif // NETIZENPROXY_H
