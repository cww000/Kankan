#include "video.h"
#include "videofileproxy.h"
#include <utility>

Video::Video(std::string id, std::string description, std::string title,
             std::string label, std::string subarea, bool isOriginal,
             std::string cover, std::string date, std::string videoFileId) :
    m_id{id}, m_description{description}, m_title{title},
    m_label{label}, m_subarea{subarea}, m_isOriginal{isOriginal},
    m_cover{cover}, m_date{date}, m_videoFile(std::make_pair(videoFileId, VideoFileProxy(videoFileId)))
{

}

Video::~Video()
{

}

std::vector<std::string> Video::getVideoInfo()
{
    std::vector<std::string> results;
    results.push_back(m_title);
    //封面、稿件时长、发布时间待加

    return results;
}

void Video::init(std::string id)
{
    m_videoFile.second.getVideoFileInfo(id);

    for (auto comment : _comments)
        comment.second.getCommentInfo(comment.first);
}
