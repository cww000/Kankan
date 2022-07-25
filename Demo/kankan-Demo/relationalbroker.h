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
//   Description: 建立数据库连接，添加数据库的增删查改操作
#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H

#include <unordered_map>
#include <mariadb/conncpp.hpp>

class RelationalBroker
{
public:
    RelationalBroker();
    virtual ~RelationalBroker();

    //执行数据库查询操作，返回数据集
    //sql:SQL语句
    std::shared_ptr<sql::ResultSet> query(std::string sql);

    //执行数据库插入操作
    //sql:SQL语句
    static void insert(std::string sql);
    static void del(std::string sql);
    static void update(std::string sql);

private:
//    std::unordered_map<std::string, Cache> _caches;
    static std::unique_ptr<sql::Connection> conn;
};

#endif // RELATIONALBROKER_H
