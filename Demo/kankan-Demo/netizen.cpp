#include <string>
#include <iostream>
#include "netizen.h"
#include "comment.h"
#include "commentbroker.h"
#include "videobroker.h"
#include "publishvideonotification.h"
#include "messagesequence.h"

Netizen::Netizen(long id, std::string key) :
    m_id{id}, m_key{key}
{
        m_nickname = "kk_" + std::to_string(id);     //生成默认用户名
}

Netizen::~Netizen()
{

}

std::string Netizen::insertSql()
{
    return "insert into user values( " + std::to_string(m_id) + ", '" + m_key + "', '" + m_nickname + "');";
}

Netizen::Netizen(long id, std::string nickname, std::string headPortrait, std::vector<std::string> videosId,
                 std::vector<long> fansId, std::vector<long> followersId) :
    m_id{id}, m_headPortrait{headPortrait}, m_key{" "}, m_nickname{nickname}
{
    for (auto vId : videosId) {
        _videos.insert(std::make_pair(vId, VideoProxy(vId)));
        std::cout << "稿件id：" ;
        std::cout << vId << std::endl;
    }

    for (auto fanId : fansId) {
        _fans.insert(std::make_pair(fanId, NetizenProxy(fanId)));
        std::cout << "粉丝id：" ;
        std::cout << fanId << std::endl;
    }

    for (auto followerId : followersId) {
        _followers.insert(std::make_pair(followerId, NetizenProxy(followerId)));
        std::cout << "关注者id：";
        std::cout << followerId << std::endl;
    }
}

void Netizen::init()
{
    //getVideoInfo如何存储返回的数据
    std::cout << "稿件信息：\n";
    for (auto video : _videos){
        video.second.getVideoInfo(video.first);
    }
    std::cout << "粉丝信息：\n";
    for (auto fan : _fans) {
        fan.second.getInfo(fan.first);
    }

    std::cout << "关注者信息：\n";
    for (auto follower : _followers) {
        follower.second.getInfo(follower.first);
    }
}

std::vector<std::string> Netizen::getInfo()
{
    std::vector<std::string> results;
    results.push_back(m_headPortrait);
    results.push_back(m_nickname);

    //测试
    std::cout << "NetizenInfo: " ;
    for (auto g : results)
        std::cout << g << "   ";
    std::cout << "\n";

    return results;
}

void Netizen::comment(const std::string &content, const std::string &videoId)
{
    //1. 生成comment id
    std::string id = "";

    //2. 生成Comment对象
    Comment comment(id, content,videoId, m_id);

    //3. 将Comment对象存入缓存
    CommentBroker::getInstance()->addComment(id, comment);

    //4. 建立comment和video的联系
    auto video = VideoBroker::getInstance()->getVideo(videoId);
    video->addNewComment(id);

    //关于是否建立网民与评论的连接：评论表中含有对应的网民id,因此似乎通过网民的id也
    //是可以找到它所对应的所有的评论

}

void Netizen::publishVideo(std::string description, std::string title, std::string label, std::string subarea, bool isOriginal, std::string cover, std::string date, std::string videoFileId)
{
    //1. 生成Video的id
    std::string id ="1";
    //新创建的稿件没有评论
    std::vector<std::string> comments;
    //2. 构造Video对象
    Video video(id, description, title, label, subarea, isOriginal, cover,
                date, m_id, comments, videoFileId);

    //3. 将video存入缓存
    VideoBroker::getInstance()->addVideo(id, video);

    //4. 将videoFile对象存入缓存
    //在这之前，还是需要一个VideoFile对象
   // VideoFileBroker::getInstance()->addVideoFile(videoFileId, videoFile)

    //5. 建立稿件与网民的连接
    addNewVideo(id);

    //6. 通知网民的所有的关注者
    std::string content="你关注的人有发布了新的稿件";
    std::string notiId = "2";
    std::string time = "23314";
    //创建通知对象，并将对象添加到消息队列
    MessageSequence::getInstance()->pushNotification(PublishVideoNotification(notiId, m_id, _fans, content, time, id));

}

void Netizen::follow(long followerId)
{

}

void Netizen::addNewVideo(std::string &id)
{
    _videos.insert({id, VideoProxy(id)});
}

const std::string &Netizen::key() const
{
    return m_key;
}

const std::string &Netizen::nickname() const
{
    return m_nickname;
}

void Netizen::updateMessage(const std::string &messageId)
{
    _message.insert(messageId);
}

void Netizen::checkOneMessage(const std::string &messageId)
{
    //将消息从网民的未读消息列表中删除
    _message.erase(messageId);

    //查找该条消息所对应的通知中的稿件的id
    auto notification = MessageSequence::getInstance()->findById(messageId);
    std::string videoId = notification->videoId();

    //删除消息列表中对应的某个消息中的这个观察者，下次将不再将消息发送给该网民
    MessageSequence::getInstance()->removeMessageObserver(messageId, m_id);

    checkOneVideo(videoId);
}


void Netizen::checkOneVideo(const std::string& videoId)
{
    auto video = VideoBroker::getInstance()->getVideo(videoId);
    video->getVideoInfo();
}

