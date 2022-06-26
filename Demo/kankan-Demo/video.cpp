#include "video.h"

Video::Video(std::string id, std::string description, std::string title,
             std::string label, std::string subarea, bool isOriginal) :
    m_id{id}, m_description{description}, m_title{title},
    m_label{label}, m_subarea{subarea}, m_isOriginal{isOriginal}
{

}
