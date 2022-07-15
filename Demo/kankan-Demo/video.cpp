#include "video.h"
#include "videofileproxy.h"
#include <utility>
#include <iostream>

Video::Video(std::string id, std::string description, std::string title, std::string label,
             std::string subarea, bool isOriginal, std::string cover, std::string date,
             std::vector<std::string> commentIds, std::string videoFileId) :
    m_id{id}, m_description{description}, m_title{title},
    m_label{label}, m_subarea{subarea}, m_isOriginal{isOriginal},
    m_cover{cover}, m_date{date}, m_videoFile(std::make_pair(videoFileId, VideoFileProxy(videoFileId)))
{
    for (auto commentId : commentIds)
        _comments.insert(std::make_pair(commentId, CommentProxy(commentId)));
}

Video::~Video()
{

}

std::vector<std::string> Video::getVideoInfo()
{
    std::vector<std::string> results;
    results.push_back(m_title);
    results.push_back(m_cover);
    results.push_back(m_date);
    results.push_back(m_videoFile.second.getVideoFileInfo(m_videoFile.first));

    //测试
    std::cout << "VideoInfo";
    for (auto g : results)
        std::cout << g << "   ";
    std::cout << "\n";



    return results;
}

void Video::init(std::string id)
{
    std::cout << "视频时长" << m_videoFile.second.getVideoFileInfo(id) << std::endl;

    for (auto comment : _comments)
        std::cout << "评论正文： " << comment.second.getCommentInfo(comment.first) << std::endl;
}
