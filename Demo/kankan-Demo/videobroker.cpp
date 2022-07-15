#include "videobroker.h"
#include <vector>
#include <iostream>

VideoBroker* VideoBroker::m_videoBroker = nullptr;

VideoBroker::~VideoBroker()
{

}

VideoBroker *VideoBroker::getInstance()
{
    if (m_videoBroker == nullptr)
        m_videoBroker = new VideoBroker();
    return m_videoBroker;
}

std::shared_ptr<Video> VideoBroker::getVideo(const std::string& id)
{
    //检查对象是否存在于缓存中

    //检索数据库，创建video对象
    std::string sql = "select * from video where id = '" + id + "'";

    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    bool isOriginal;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());    //稿件id
        parameters.push_back(res->getString(2).c_str());    //稿件描述
        parameters.push_back(res->getString(3).c_str());    //稿件标题
        parameters.push_back(res->getString(4).c_str());    //标签
        parameters.push_back(res->getString(5).c_str());    //分区
        isOriginal = res->getBoolean(6);                    //是否为原创
        parameters.push_back(res->getString(7).c_str());    //封面
        parameters.push_back(res->getString(8).c_str());    //发布日期
        long i = res->getLong(9);
    }


    std::vector<std::string> commentIds;
    sql = "select id from comment where videoId = '" + id + "'";

    res = query(sql);
    while (res->next())
        commentIds.push_back(res->getString(1).c_str());

    std::shared_ptr<Video> video = std::make_shared<Video>(parameters[0], parameters[1], parameters[2],parameters[3],
                                                           parameters[4], isOriginal, parameters[5], parameters[6],
                                                            commentIds, parameters[7]);
    std::cout << "Video对象实例化成功" << std::endl;

    //返回对象之前实例化videofile对象，实例化评论对象
    sql = "select id from videoFile where videoId = '" + id + "'";

    res = query(sql);
    std::string result;
    while (res->next())
        result = res->getString(1).c_str();
    video->init(result);

    //返回video对象
    return video;
}



VideoBroker::VideoBroker()
{

}
