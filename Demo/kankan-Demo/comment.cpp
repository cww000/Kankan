#include "comment.h"

Comment::Comment(std::string id, std::string text, std::string videoId, std::string user_id) :
    m_id{id}, m_text{text}, m_videoId{videoId}, m_user_id{user_id}
{

}

Comment::~Comment()
{

}

const std::string Comment::videoId() const
{
    return m_videoId;
}

std::string Comment::user_id() const
{
    return m_user_id;
}

nlohmann::json Comment::getCommentInfo()
{
    nlohmann::json comment;
    comment["id"] = m_id;
    comment["conetnt"] = m_text;
    comment["user_id"] = m_user_id;
    return comment;
}
