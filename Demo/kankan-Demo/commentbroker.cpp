#include "commentbroker.h"
#include <iostream>

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

std::shared_ptr<Comment> CommentBroker::getComment(std::string &id)
{
    //判断是否存在缓存中

    //检索数据库，创建对象
    std::string sql = "select id, text from comment where id = '" + id + "'";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
    }

    std::shared_ptr<Comment> comment = std::make_shared<Comment>(parameters[0], parameters[1]);

    //返回对象
    std::cout << "Comment对象实例化成功" << std::endl;
    return comment;
}

CommentBroker::CommentBroker()
{

}
