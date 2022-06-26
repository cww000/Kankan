#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <memory>
#include "videointerface.h"

class VideoFile;
class Image;

class Video : public VideoInterface
{
public:
    Video(std::string id, std::string description, std::string title,
          std::string label, std::string subarea, bool isOriginal);
    ~Video();
private:
    std::string m_id;           //稿件id
    std::string m_description;  //简介
    std::string m_title;        //标题
    std::string m_label;        //标签
    std::string m_subarea;      //分区
    bool m_isOriginal;          //是否是转载
                                //封面
    std::shared_ptr<VideoFile> m_videoFile;
};

#endif // VIDEO_H
