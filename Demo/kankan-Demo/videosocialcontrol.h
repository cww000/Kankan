#ifndef VIDEOSOCIALCONTROL_H
#define VIDEOSOCIALCONTROL_H

#include <string>
#include <memory>
#include <vector>
#include "mytimer.h"

class Netizen;

class VideoSocialControl
{
public:
    VideoSocialControl();
    ~VideoSocialControl();
    //注册
    //key:用户设置的密码
    void login(std::string key);

    //登录
    //id:用户输入的帐号
    //key:用户输入的密码
    void login(long id, std::string key);

    //假设服务器记录每次上传视频的id，保存为一个列表，首页总是显示最新的一批视频
    void getSomeVideos(std::vector<std::string> ids);

    //加载稿件的完整信息
    void loadVideo(std::string id);

    //合并视频
    std::string mergeVideoFiles(std::vector<std::string> videoFiles);

    //生成稿件
    void createVideo(std::string description, std::string title, std::string label, std::string subarea, bool isOriginal, std::string cover, std::string date, long user_id, std::string videoFileId);

    //删除稿件
    void deleteVideo(long netizenId, const std::string& videoId);

    //发表评论
    void commentVideo(const std::string& content,long netizenId, const std::string videoId);

    //关注
    void follow(long netizenId, long followerId);

    //查看某条未读消息
    void checkOneMessage(long netizenId, std::string messageId);

    //修改个人信息
    void updateAcountInfo(long netizenId, std::string key, std::string headPortrait, std::string nickname);

private:
    static void flush();
    static void notificationFlush();
    MyTimer m_timer;
    MyTimer m_notiifyTimer;
};

#endif // VIDEOSOCIALCONTROL_H
