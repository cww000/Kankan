#include "videosocialcontrol.h"
#include "netizen.h"
#include "netizenbroker.h"
#include <iostream>
#include <utility>
#include <time.h>
#include "commentbroker.h"
#include "videobroker.h"
#include "videofilebroker.h"
#include "messagesequence.h"

VideoSocialControl::VideoSocialControl()
{
    m_timer.start(2000, flush);
    m_notiifyTimer.start(10000, notificationFlush);
}

VideoSocialControl::~VideoSocialControl()
{

}

//注册
void VideoSocialControl::login(std::string key)
{
    //1. 生成帐号
    time_t result = time(NULL);
    std::string id;
    if (result != (time_t)(-1))
        id = std::to_string(result);    //系统根据时间分配id

    //2. 生成netizen对象，并将netizen对象存入缓存
    Netizen netizen(id, key);
    NetizenBroker::getInstance()->addNetizen(id, netizen);

//    //添加新的用户记录
//    NetizenBroker::getInstance()->insertNewNetizen(std::make_shared<Netizen>(id, key));

    //注册成功后自动登录
    login(id, key);
}

//登录
void VideoSocialControl::login(std::string id, std::string key)
{
    if (NetizenBroker::getInstance()->qualifyNetizenId(id)) {
        std::cout << "用户id存在" << std::endl;
        if (NetizenBroker::getInstance()->qualifyNetizenKey(id, key)) {
            std::cout << "密码正确" << std::endl;

            auto netizen = NetizenBroker::getInstance()->findNetizenById(id);
            netizen->setOnline(true);  //设置网民在线
            netizen->init();//初始化稿件（含视频）、粉丝列表、关注列表初始化

        } else {
            std::cout << "密码错误" << std::endl;
        }
    } else {
        std::cout << "用户id不存在" << std::endl;
    }

}

void VideoSocialControl::getSomeVideos(std::vector<std::string> ids)
{
    std::unordered_map<std::string, VideoProxy> _videos;
    for (auto id : ids)
        _videos.insert(std::make_pair(id, VideoProxy(id)));

    //通过数据库检索找到对应稿件的netizen


    //获取稿件的摘要信息
    for (auto video : _videos)
        video.second.getVideoInfo(video.first);

    //整合网民信息与稿件的摘要信息

}

void VideoSocialControl::checkOneVideo(std::string netizenId, std::string videoId)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->checkOneVideo(videoId);
}

std::string VideoSocialControl::mergeVideoFiles(std::vector<std::string> videoFiles)
{
    //合并视频，保存一个本地的合并后的视频文件地址

    //生成一个新的VideoFile的id

    //返回视频id

}

void VideoSocialControl::createVideo(std::string netizenId, nlohmann::json video)
{
    //如果确认发布稿件
     auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
     netizen->publishVideo(video);
}

void VideoSocialControl::deleteVideo(std::string netizenId, const std::string &videoId)
{
    auto netizen = NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->deleteVideo(videoId);
}

void VideoSocialControl::commentVideo(const std::string &content, std::string netizenId, const std::string videoId)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->comment(content, videoId);
}

void VideoSocialControl::follow(std::string netizenId, std::string followerId)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->follow(followerId);
}

void VideoSocialControl::browseMessage(std::string netizenId)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->browseMessage();
}

void VideoSocialControl::checkOneMessage(std::string netizenId, std::string messageId)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->checkOneMessage(messageId);
}

void VideoSocialControl::updateAcountInfo(std::string netizenId, std::string key, std::string headPortrait, std::string nickname)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->updateAcountInfo(key, headPortrait, nickname);
}

void VideoSocialControl::updateVideoInfo(std::string netizenId, nlohmann::json newVideo)
{
    auto netizen=NetizenBroker::getInstance()->findNetizenById(netizenId);
    netizen->updateVideoInfo(newVideo);
}

void VideoSocialControl::flush()
{
    NetizenBroker::getInstance()->flush();
    VideoBroker::getInstance()->flush();
    VideoFileBroker::getInstance()->flush();
    CommentBroker::getInstance()->flush();
    std::cout << "执行了一次刷新" << std::endl;
}

void VideoSocialControl::notificationFlush()
{
    std::cout << "发布稿件的消息推送：\n";
    MessageSequence::getInstance()->updateMessageQueue();
}


