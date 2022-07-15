#include "comment.h"

Comment::Comment(std::string id, std::string text, std::string videoId, long user_id) :
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

long Comment::user_id() const
{
    return m_user_id;
}
