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
//   Description: 利用评论的代管者（只有单例），去操纵数据库，从数据库中获取评论的相关数据，生成评论对象，并放到缓存中或者返回给评论的代理。当添加评论到数据库或者需要删除数据库中的某条评论时，也需要利用到其中的六个缓存，将对应的数据加到缓存中。但由于评论不需要修改，因此新的脏缓存和旧的脏缓存应该不需要。并且控制器对象定时刷新每个代管者中的几个缓存，利用缓存中的数据写数据库。

#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"
#include "comment.h"
#include <mutex>
#include <string>
class CommentBroker : public RelationalBroker
{
public:
    ~CommentBroker();
    static CommentBroker* getInstance();
    static void flush();
    std::shared_ptr<Comment> getComment(const std::string& id);
    std::shared_ptr<Comment> retrieveComment(const std::string& id);
    //将新增的评论添加到新的净缓存
    void addComment(const std::string& id, const Comment& comment);

    //删除评论
    void deleteComment(const std::string& id, const Comment& comment);

private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
    static std::mutex m_mutex;
    static std::unordered_map<std::string, Comment> _newClean;  //新的净缓存
//    static std::unordered_map<std::string, Comment> _newDirty;  //新的脏缓存
    static std::unordered_map<std::string, Comment> _newDelete; //新的删除缓存
    static std::unordered_map<std::string, Comment> _oldClean;  //旧的净缓存
//    static std::unordered_map<std::string, Comment> _oldDirty;  //旧的脏缓存
    static std::unordered_map<std::string, Comment> _oldDelete; //旧的删除缓存

    static void cacheFlush();   //将数据写入数据库
    static void cacheDel();  //删除数据库中的数据
  //  static void cacheUpdate();   //修改数据库中的数据
    static std::shared_ptr<Comment> inCache(std::string id);   //判断是否在缓存中
    int judgeFromForDel(const std::string& id);  //判断要删除的数据是在哪一个缓存
};

#endif // COMMENTBROKER_H
