#include "publishvideonotification.h"


PublishVideoNotification::PublishVideoNotification(std::string id, long senderId, std::unordered_map<long, NetizenProxy> observer, std::string content, std::string time, std::string videoId) :
    m_id{id}, m_senderId{senderId}, _observer{observer},
    m_content{content}, m_time{time}, m_videoId{videoId}
{

}

PublishVideoNotification::~PublishVideoNotification()
{

}

void PublishVideoNotification::registerObserver(long observerId)
{
    _observer.insert({observerId, NetizenProxy(observerId)});
}

void PublishVideoNotification::removeObserver(long observerId)
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
