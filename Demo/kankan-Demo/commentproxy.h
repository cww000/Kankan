#ifndef COMMENTPROXY_H
#define COMMENTPROXY_H

#include <memory>
#include "commentinterface.h"

class Comment;

class CommentProxy : public CommentInterface
{
public:
    CommentProxy(std::string& id);
    ~CommentProxy();

    //返回评论的内容
    std::string getCommentInfo(std::string id);
private:
    std::string m_id;
    std::shared_ptr<Comment> m_comment;
};

#endif // COMMENTPROXY_H
