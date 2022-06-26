#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "commentinterface.h"

class Comment : public CommentInterface
{
public:
    Comment();
    ~Comment();
private:
    std::string m_id;       //评论id,利用时间生成
    std::string m_text;     //评论正文
};

#endif // COMMENT_H
