#include "commentbroker.h"

CommentBroker* CommentBroker::m_commentBroker = nullptr;

CommentBroker::~CommentBroker()
{

}

CommentBroker *CommentBroker::getInstance()
{
    if (m_commentBroker == nullptr)
        m_commentBroker = new CommentBroker();
    return m_commentBroker;
}

Comment *CommentBroker::getComment(std::string &id)
{
    //判断是否存在缓存中

    //检索数据库，创建对象


    //返回对象
}

CommentBroker::CommentBroker()
{

}
