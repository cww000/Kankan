#ifndef PUBLISHVIDEONOTIFICATION_H
#define PUBLISHVIDEONOTIFICATION_H

#include <string>
#include <unordered_map>
#include "netizenproxy.h"
class PublishVideoNotification
{
public:
    explicit PublishVideoNotification(std::string id, long senderId, std::unordered_map<long, NetizenProxy> observer, std::string content, std::string time, std::string videoId);
    ~PublishVideoNotification();

    //注册订阅者
    void registerObserver(long observerId);
    //删除订阅者
    void removeObserver(long observerId);
    //通知订阅者
    void notifyObserver();

    bool hasReadAll() {return _observer.empty();}

    const std::string id() {return m_id;}
    long senderId() {return m_senderId;}
    const std::string time() {return m_time;}
    const std::string videoId() {return m_videoId;}

private:
    std::string m_id;
    long m_senderId;
    std::unordered_map<long, NetizenProxy> _observer;
    std::string m_content;
    std::string m_time;
    std::string m_videoId;
};

#endif // PUBLISHVIDEONOTIFICATION_H
