#include "videosocialcontrol.h"
#include "netizen.h"
#include "netizenbroker.h"

VideoSocialControl::VideoSocialControl()
{

}

//注册
void VideoSocialControl::login(std::string key)
{
    //id等待系统分配
    long id = 0;
    //添加新的用户记录
    NetizenBroker::getInstance()->insertNewNetizen(std::make_shared<Netizen>(id, key));

    //注册成功后自动登录
    login(id, key);
}

//登录
void VideoSocialControl::login(long id, std::string key)
{
    //id存在
    if (NetizenBroker::getInstance()->qualifyNetizenId(id)) {
        //密码正确
        if (NetizenBroker::getInstance()->qualifyNetizenKey(id, key)) {

        } else {//密码错误

        }
    } else {//id不存在

    }
}


