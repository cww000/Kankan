// Copyright (C) Microsoft. All rights reserved. License (BSD/MIT/GPL)
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
//   Description: 主要实现了获取评论的相关信息。例如：评论id,评论内容，用户id等

#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "json.hpp"

class Comment
{
public:
    Comment(std::string id, std::string text, std::string videoId, std::string user_id);

    ~Comment();

    std::string getText(){ return m_text; };

    const std::string videoId() const;
    std::string user_id() const;
    nlohmann::json getCommentInfo();

private:
    std::string m_id;        //评论id,利用时间生成
    std::string m_text;      //评论正文
    std::string m_videoId;   //稿件id
    std::string m_user_id; //它所属的网民id
};

#endif // COMMENT_H
