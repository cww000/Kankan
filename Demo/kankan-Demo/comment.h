#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "commentinterface.h"
#include "json.hpp"

class Comment : public CommentInterface
{
public:
    Comment(std::string id, std::string text, std::string videoId, long user_id);

    ~Comment();

    std::string getText(){ return m_text; };

    const std::string videoId() const;
    long user_id() const;
    nlohmann::json getCommentInfo();

private:
    std::string m_id;        //评论id,利用时间生成
    std::string m_text;      //评论正文
    std::string m_videoId;   //稿件id
    long m_user_id; //它所属的网民id
};

#endif // COMMENT_H
