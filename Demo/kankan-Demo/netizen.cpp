#include <string>
#include <iostream>
#include <vector>
#include "netizen.h"
#include "comment.h"
#include "commentbroker.h"
#include "videobroker.h"
#include "publishvideonotification.h"
#include "messagesequence.h"
#include "netizenbroker.h"
#include "videofilebroker.h"

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
//        std::cout << "稿件id：" ;
//        std::cout << vId << std::endl;
    }

    for (auto fanId : fansId) {
        _fans.insert(std::make_pair(fanId, NetizenProxy(fanId)));
//        std::cout << "粉丝id：" ;
//        std::cout << fanId << std::endl;
    }

    for (auto followerId : followersId) {
        _followers.insert(std::make_pair(followerId, NetizenProxy(followerId)));
//        std::cout << "关注者id：";
//        std::cout << followerId << std::endl;
    }

}

void Netizen::init()
{
    nlohmann::json netizenInfo;
    netizenInfo["id"] = m_id;
    netizenInfo["nickname"] = m_nickname;
    netizenInfo["headPortrait"] = m_headPortrait;
    for (auto& video : _videos){
        nlohmann::json v = video.second.getVideoInfo(video.first);
        netizenInfo["videos"].push_back(v);
    }
    if (_videos.size() == 0) netizenInfo["videos"] = "";

    for (auto& fan : _fans) {
        nlohmann::json f = fan.second.getInfo(fan.first);
        netizenInfo["fans"].push_back(f);
    }
    if (_fans.size() == 0) netizenInfo["fans"] = "";

    for (auto& follower : _followers) {
        nlohmann::json f = follower.second.getInfo(follower.first);
        netizenInfo["followers"].push_back(f);
    }
    if (_followers.size() == 0) netizenInfo["followers"] = "";

    std::cout << netizenInfo.dump(4) << std::endl;
}

nlohmann::json Netizen::getInfo()
{
    nlohmann::json netizen;
    netizen["id"] = m_id;
    netizen["nickname"] = m_nickname;
    netizen["headPortrait"] = m_headPortrait;
    return netizen;
}

void Netizen::comment(const std::string &content, const std::string &videoId)
{
    //1. 生成comment id
    std::string id = "0003";

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

void Netizen::publishVideo(nlohmann::json video)
{
    //1. 生成Video的id
    std::string id ="0628_video";
    //新创建的稿件没有评论
    std::vector<std::string> comments;
    //2. 获取json中的数据
    std::string description = video["description"].get<std::string>();
    std::string title = video["title"].get<std::string>();
    std::string label = video["label"].get<std::string>();
    std::string subarea = video["subarea"].get<std::string>();
    std::string isOri = video["isOriginal"].get<std::string>();
    bool isOriginal;
    std::istringstream(isOri) >> std::boolalpha >> isOriginal;
    std::string cover = video["cover"].get<std::string>();
    std::string date = video["date"].get<std::string>();
    std::string videoFileId = video["videoFile"]["id"].get<std::string>();
    
    //3. 构造Video对象
    Video v(id, description, title, label, subarea, isOriginal, cover, date, m_id, comments, videoFileId);

    //4. 将video存入净缓存
    VideoBroker::getInstance()->addVideo(id, v);

    //5. 将videoFile对象存入净缓存
    //在这之前，还是需要一个VideoFile对象
    VideoFile videoFile(videoFileId, "www.Youchengzhu.com", id);
    VideoFileBroker::getInstance()->addVideoFile(videoFileId, videoFile);

    //6. 建立稿件与网民的连接
    addNewVideo(id);

    //6. 通知网民的所有的关注者
    std::string content="你关注的人有发布了新的稿件";
    std::string notiId = "2";
    std::string date1 = "23314";

    //7. 创建通知对象，并将对象添加到消息队列
    MessageSequence::getInstance()->pushNotification(PublishVideoNotification(notiId, m_id, _fans, content, date1, id));

}

void Netizen::follow(long followerId)
{
    //实例化被关注者
    auto follower = NetizenBroker::getInstance()->findNetizenById(followerId);

    //在网民和他想要关注的人之间建立联系（网民与关注者）
    _followers.insert({followerId, NetizenProxy(followerId)});
    std::string sql = "insert into follower values(" + std::to_string(m_id) + ",'" + m_nickname + "'," + std::to_string(followerId) + ",'" + follower->nickname() + "')";
    std::cout << sql << std::endl;
    NetizenBroker::getInstance()->insert(sql);

    std::cout << "关注成功\n";

    //在被关注的人和该网民之间建立联系（网民与粉丝)
    follower->addFan(m_id, this);

}

void Netizen::addFan(long fanId, const Netizen* fan)
{
    _fans.insert({fanId, NetizenProxy(fanId)});
    std::string sql = "insert into fan values(" + std::to_string(m_id) + ",'" + m_nickname + "'," + std::to_string(fanId) + ",'" + fan->nickname() + "')";
    std::cout << sql << std::endl;
    NetizenBroker::getInstance()->insert(sql);
}

void Netizen::deleteVideo(const std::string &videoId)
{
    //1.删除网民与这个已发布的稿件的联系
    _videos.erase(videoId);

    //2.实例化想要删除的稿件
    auto video = VideoBroker::getInstance()->getVideo(videoId);

    //3.获取稿件中的视频文件和评论
    auto videoFile =VideoFileBroker::getInstance()->getVideoFile(video->videoFile().first);
    auto comments = video->comments();

    //4.将要删除的评论加入到新的或者旧的删除缓存
    for (const auto& com : comments) {
        auto temp = CommentBroker::getInstance()->getComment(com.first);
        CommentBroker::getInstance()->deleteComment(com.first, *temp);
    }

    //5.将稿件和视频文件加入对应新的或者旧的删除缓存
    VideoFileBroker::getInstance()->deleteVideoFile(video->videoFile().first , *videoFile);
    VideoBroker::getInstance()->deleteVideo(videoId, *video);

}

void Netizen::addNewVideo(std::string &id)
{
    _videos.insert({id, VideoProxy(id)});
}

const std::string Netizen::key() const
{
    return m_key;
}

const std::string Netizen::nickname() const
{
    return m_nickname;
}

void Netizen::updateMessage(const std::string &messageId)
{
    _message.insert(messageId);
}

void Netizen::browseMessage()
{
    if (!_message.empty()) {
        nlohmann::json messages;
        for (auto& mess : _message) {
            nlohmann::json m;
            auto notification = MessageSequence::getInstance()->findById(mess);
            m["id"] = notification->id();
            m["sendername"] = NetizenBroker::getInstance()->findNetizenById(notification->senderId())->nickname();
            m["conetnt"] = notification->content();
            m["date"] = notification->date();
            messages.push_back(m);
        }

        std::cout << messages.dump(4) << std::endl;
    } else {
        std::cout << "什么消息也没有！！！！" << std::endl;
    }
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

void Netizen::updateAcountInfo(std::string key, std::string headPortrait, std::string nickname)
{
    //1. 首先修改网民当前当前账户信息
    m_key = key;
    m_headPortrait = headPortrait;
    m_nickname = nickname;

    //2. 修改数据库中的网民信息
    NetizenBroker::getInstance()->updateAcountInfo(m_id, *this);
}

void Netizen::updateVideoInfo(nlohmann::json newVideo)
{
    //1.获取要修改的 videoId 和 videoFileId
    std::string videoId = newVideo["id"].get<std::string>();
    std::string videoFileId = newVideo["videoFile"]["id"].get<std::string>();

    //2. 获取原video对象和 VideoFile对象
    auto video = VideoBroker::getInstance()->getVideo(videoId);
    auto videoFile = VideoFileBroker::getInstance()->getVideoFile(videoFileId);
    //获取原video对象中评论的id
    std::vector<std::string> comments;
    for (auto& com : video->comments()) {
        comments.push_back(com.first);
    }

    //3. 获取json中的数据
    std::string description = newVideo["description"].get<std::string>();
    std::string title = newVideo["title"].get<std::string>();
    std::string label = newVideo["label"].get<std::string>();
    std::string subarea = newVideo["subarea"].get<std::string>();
    std::string isOri = newVideo["isOriginal"].get<std::string>();
    bool isOriginal;
    std::istringstream(isOri) >> std::boolalpha >> isOriginal;
    std::string cover = newVideo["cover"].get<std::string>();
    std::string date = newVideo["date"].get<std::string>();

    //4. 构造新的Video对象
    Video v(videoId, description, title, label, subarea, isOriginal, cover, date, m_id, comments, videoFileId);
    //构造 VideoFile 对象
    VideoFile vf(videoFileId, "www.taobao.com", videoId);

    //5. 修改数据库中对应的稿件信息
    VideoBroker::getInstance()->updateVideo(videoId, v);
    // 修改数据库中对应的视频文件信息
    VideoFileBroker::getInstance()->updateVideoFile(videoFileId, vf);
}


void Netizen::checkOneVideo(const std::string& videoId)
{
    auto video = VideoBroker::getInstance()->getVideo(videoId);
    std::cout << video->getVideoInfo().dump(4) << std::endl;
}

