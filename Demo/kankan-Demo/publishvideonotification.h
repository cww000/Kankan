#ifndef PUBLISHVIDEONOTIFICATION_H
#define PUBLISHVIDEONOTIFICATION_H

#include <string>
#include <unordered_map>
#include "netizenproxy.h"
class PublishVideoNotification
{
public:
    explicit PublishVideoNotification(std::string id, long senderId, std::unordered_map<long, NetizenProxy> observer, std::string content, std::string date, std::string videoId);
    explicit PublishVideoNotification(std::string id, std::string content, std::string date, long senderId, std::string videoId);
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
    const std::string date() {return m_date;}
    const std::string videoId() {return m_videoId;}
    const std::string content() {return m_content;}
    const std::unordered_map<long, NetizenProxy> observer() {return _observer;}

private:
    std::string m_id;
    long m_senderId;
    std::unordered_map<long, NetizenProxy> _observer;
    std::string m_content;
    std::string m_date;
    std::string m_videoId;
};

#endif // PUBLISHVIDEONOTIFICATION_H
