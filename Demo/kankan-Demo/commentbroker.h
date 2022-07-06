#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"
#include "comment.h"

class CommentBroker : public RelationalBroker
{
public:
    ~CommentBroker();
    static CommentBroker* getInstance();
    std::shared_ptr<Comment> getComment(std::string& id);
private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
};

#endif // COMMENTBROKER_H
