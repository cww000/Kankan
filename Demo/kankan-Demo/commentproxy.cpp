#include "commentproxy.h"
#include "commentbroker.h"

CommentProxy::CommentProxy(std::string &id) : m_id{id}
{

}

CommentProxy::~CommentProxy()
{

}

std::string CommentProxy::getCommentInfo(std::string id)
{
    if (m_comment == nullptr)
        m_comment = CommentBroker::getInstance()->getComment(id);

    return m_comment->getText();
}
