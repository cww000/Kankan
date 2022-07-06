#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <memory>
#include "videointerface.h"
#include <vector>
#include <unordered_map>
#include "videofileproxy.h"
#include "commentproxy.h"

class VideoFile;
class Image;

class Video : public VideoInterface
{
public:
    Video() = delete;
    Video(std::string id, std::string description, std::string title, std::string label,
          std::string subarea, bool isOriginal, std::string cover, std::string date,
          std::vector<std::string> commentIds, std::string videoFileId);
    ~Video();

    std::vector<std::string> getVideoInfo();
    //获取稿件的数据（标题、发布时间、稿件时长[通过m_videoFile对象去获取时长]、封面）
    //后续可考虑替换为json传输

    void init(std::string id);
    //通过代理实例化videofile对象
private:
    std::string m_id;           //稿件id
    std::string m_description;  //简介
    std::string m_title;        //标题
    std::string m_label;        //标签
    std::string m_subarea;      //分区
    bool m_isOriginal;          //是否是转载
    std::string m_cover;        //封面（存文件路径）
    std::string m_date;         //发布时间(后期需考虑是否使用date)

    std::unordered_map<std::string, CommentProxy> _comments;
    std::pair<std::string, VideoFileProxy> m_videoFile;
};

#endif // VIDEO_H
