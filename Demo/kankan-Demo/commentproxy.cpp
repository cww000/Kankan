#include "commentproxy.h"
#include "commentbroker.h"

CommentProxy::CommentProxy()
{

}

CommentProxy::~CommentProxy()
{

}

std::string CommentProxy::getCommentInfo(std::string id)
{
    if (m_comment == nullptr)
        m_comment = std::make_shared<Comment>(CommentBroker::getInstance()->getComment(id));

    return m_comment->getText();
}
