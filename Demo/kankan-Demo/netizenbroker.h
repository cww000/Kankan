// Copyright (C) Microsoft. All rights reserved. License (BSD/MIT/GPL)
// Project: kankan-Demo
//
// Author: YouZheng Zhu, HaiYan Nie, Wenwen Cheng(WennCheng@163.com)
// Date: 2022-07-24
// Version: 0.1.0
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// History:同评论代管者类似，操纵数据库，读取数据库中的网民信息，实现网民帐号检验、查找、添加等。其中数据的修改读取等也需要利用其中的六个缓存，先将要操纵的数据放到对应的缓存中，并定时刷新写入数据库

#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include <memory>
#include "relationalbroker.h"
#include <vector>
#include <mutex>
class Netizen;

class NetizenBroker : public RelationalBroker
{
public:
    ~NetizenBroker();
    static NetizenBroker* getInstance();
    static void flush();

    //根据用户ID检验用户是否存在
    //id：用户输入id
    bool qualifyNetizenId(std::string id);

    //检验用户的id与key是否匹配
    //id:用户输入id
    //key:用户输入密码key
    bool qualifyNetizenKey(std::string id, std::string key);

    //添加新的用户记录
    //netizen:新用户实体
    void insertNewNetizen(std::shared_ptr<Netizen> netizen);

    //通过用户id查找相关用户数据
    //id:用户id
    std::shared_ptr<Netizen> findNetizenById(std::string id);
    std::shared_ptr<Netizen> retrieveNetizen(std::string id);

    //通过用户id查找所有稿件id
    std::vector<std::string> findNetizenVideos(const std::string id);

    //通过用户id查找所有粉丝id
    std::vector<std::string> findNetizenFans(const std::string id);

    //通过用户id查找所有关注者id
    std::vector<std::string> findNetizenFollowers(const std::string id);

    //添加新的网民到新的净缓存
    void addNetizen(std::string id, const Netizen& netizen);

    //修改网民账号信息
    void updateAcountInfo(std::string id, const Netizen& netizen);

private:
    NetizenBroker();
    static NetizenBroker* m_netizenBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Netizen> _newClean;  //新的净缓存
    static std::unordered_map<std::string, Netizen> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Netizen> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Netizen> _oldClean;  //旧的净缓存
    static std::unordered_map<std::string, Netizen> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Netizen> _oldDelete; //旧的删除缓存

    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
    static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Netizen> inCache(std::string id);   //判断是否在缓存中
    int judgeFrom(std::string id);  //判断要修改的数据是在哪个缓存
};

#endif // NETIZENBROKER_H
