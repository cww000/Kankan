#include "publishvideonotification.h"


PublishVideoNotification::PublishVideoNotification(std::string id, std::string senderId, std::unordered_map<std::string, NetizenProxy> observer, std::string content, std::string date, std::string videoId) :
    m_id{id}, m_senderId{senderId}, _observer{observer},
    m_content{content}, m_date{date}, m_videoId{videoId}
{

}

PublishVideoNotification::PublishVideoNotification(std::string id, std::string content, std::string date, std::string senderId, std::string videoId) : m_id{id}, m_senderId{senderId}, m_content{content}, m_date{date},  m_videoId{videoId}
{

}

PublishVideoNotification::~PublishVideoNotification()
{

}

void PublishVideoNotification::registerObserver(std::string observerId)
{
    _observer.insert({observerId, NetizenProxy(observerId)});
}

void PublishVideoNotification::removeObserver(std::string observerId)
{
    _observer.erase(observerId);
}

void PublishVideoNotification::notifyObserver()
{
    for(auto& observer:_observer){
        if(observer.second.isOnline()){
            observer.second.updateMessage(id());
        }
    }
}
