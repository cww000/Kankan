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
//   Description: 充当评论对象的代理，主要是去向评论的代管者获取到评论的相关数据
#ifndef COMMENTPROXY_H
#define COMMENTPROXY_H

#include <memory>
#include "json.hpp"
#include <string>

class Comment;

class CommentProxy
{
public:
    CommentProxy(std::string& id);
    ~CommentProxy();

    //返回评论的内容
    nlohmann::json getCommentInfo(std::string id);
private:
    std::string m_id;
    std::shared_ptr<Comment> m_comment;
};

#endif // COMMENTPROXY_H
