#include "video.h"
#include <utility>
#include <iostream>
#include "videofileproxy.h"
#include "commentproxy.h"


using json = nlohmann::json;

Video::Video(std::string id, std::string description, std::string title, std::string label,
             std::string subarea, bool isOriginal, std::string cover, std::string date, long user_id, std::vector<std::string> commentIds, std::string videoFileId) :
    m_id{id}, m_description{description}, m_title{title},
    m_label{label}, m_subarea{subarea}, m_isOriginal{isOriginal},
    m_cover{cover}, m_date{date}, m_user_id{user_id}, m_videoFile(std::make_pair(videoFileId, VideoFileProxy(videoFileId)))
{
    for (auto commentId : commentIds)
        _comments.insert(std::make_pair(commentId, CommentProxy(commentId)));
}

Video::~Video()
{

}

nlohmann::json Video::getVideoInfo()
{
    json video;
    video["id"] = m_id;
    video["description"] = m_description;
    video["title"] = m_title;
    video["label"] = m_label;
    video["subarea"] = m_subarea;
    video["isOriginal"] = std::to_string(m_isOriginal);
    video["cover"] = m_cover;
    video["date"] = m_date;
    video["user_id"] = m_user_id;
    video["videoFile"] = m_videoFile.second.getVideoFileInfo(m_videoFile.first);
   // json comment;
    int i = 0;
    for (auto& com : _comments) {
        video["comment"][i] = com.second.getCommentInfo(com.first);
        ++i;
    }
    return video;

//    std::vector<std::string> results;
//    results.push_back(m_title);
//    results.push_back(m_cover);
//    results.push_back(m_date);
//    results.push_back(m_videoFile.second.getVideoFileInfo(m_videoFile.first));

//    //测试
//    std::cout << "VideoInfo";
//    for (auto g : results)
//        std::cout << g << "   ";
//    std::cout << "\n";

//    return results;
}



void Video::addNewComment(std::string &id)
{
    _comments.insert({id, CommentProxy(id)});
}

void Video::init()
{
    std::cout << "视频文件：" << m_videoFile.second.getVideoFileInfo(m_videoFile.first).dump(4) << std::endl;

    for (auto& comment : _comments)
        std::cout << "评论： " << comment.second.getCommentInfo(comment.first).dump(4) << std::endl;
}

const std::string Video::description() const
{
    return m_description;
}

const std::string Video::title() const
{
    return m_title;
}

const std::string Video::label() const
{
    return m_label;
}

const std::string Video::subarea() const
{
    return m_subarea;
}

bool Video::isOriginal() const
{
    return m_isOriginal;
}

const std::string Video::cover() const
{
    return m_cover;
}

const std::string Video::date() const
{
    return m_date;
}

const std::unordered_map<std::string, CommentProxy> Video::comments() const
{
    return _comments;
}

const std::pair<std::string, VideoFileProxy> Video::videoFile() const
{
    return m_videoFile;
}

long Video::user_id() const
{
    return m_user_id;
}

