#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "relationalbroker.h"

class CommentBroker
{
public:
    ~CommentBroker();
private:
    CommentBroker();
    static CommentBroker* m_commentBroker;
};

#endif // COMMENTBROKER_H
