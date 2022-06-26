#ifndef VIDEOSOCIALCONTROL_H
#define VIDEOSOCIALCONTROL_H

#include <string>
#include <memory>

class Netizen;

class VideoSocialControl
{
public:
    VideoSocialControl();

    //注册
    //key:用户设置的密码
    void login(std::string key);

    //登录
    //id:用户输入的帐号
    //key:用户输入的密码
    void login(long id, std::string key);
};

#endif // VIDEOSOCIALCONTROL_H
