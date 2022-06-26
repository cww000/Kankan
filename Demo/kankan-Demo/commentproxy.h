#ifndef COMMENTPROXY_H
#define COMMENTPROXY_H

#include <memory>
#include "commentinterface.h"

class Comment;

class CommentProxy : public CommentInterface
{
public:
    CommentProxy();
    ~CommentProxy();
private:
    std::shared_ptr<Comment> m_Comment;
};

#endif // COMMENTPROXY_H
