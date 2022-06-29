#include "videosocialcontrol.h"
#include "netizen.h"
#include "netizenbroker.h"
#include <iostream>

VideoSocialControl::VideoSocialControl()
{

}

//注册
void VideoSocialControl::login(std::string key)
{
    //id等待系统分配
    long id = 20220630;
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
        std::cout << "用户存在" << std::endl;
        //密码正确
        if (NetizenBroker::getInstance()->qualifyNetizenKey(id, key)) {
            std::cout << "密码正确" << std::endl;
        } else {//密码错误
            std::cout << "密码错误" << std::endl;
        }
    } else {//id不存在
        std::cout << "用户不存在" << std::endl;
    }

    auto nitizen = NetizenBroker::getInstance()->findNetizenById(id);
}


