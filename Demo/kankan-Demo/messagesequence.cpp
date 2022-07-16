#include <iostream>
#include "messagesequence.h"
#include "publishvideonotification.h"

MessageSequence* MessageSequence::m_messageSeq = nullptr;

MessageSequence::MessageSequence()
{

}

MessageSequence::~MessageSequence()
{

}

MessageSequence* MessageSequence::getInstance()
{
    if (m_messageSeq == nullptr) {
        m_messageSeq = new MessageSequence();
    }

    return m_messageSeq;
}

void MessageSequence::pushNotification(PublishVideoNotification notification)
{
    //将发布稿件消息添加到消息队列
    m_messageQueue.insert({notification.id(), notification});

    //将消息存入数据库
}

void MessageSequence::removeNotification(std::string id)
{
    m_messageQueue.erase(id);

    //删除数据库中对应的某条消息
}

PublishVideoNotification* MessageSequence::findById(const std::string& id)
{
    return &m_messageQueue.at(id);
}

void MessageSequence::updateMessageQueue()
{
    //发送消息队列中所有的message
    for(auto& message:m_messageQueue){
        message.second.notifyObserver();
    }

    //遍历消息队列中的每条消息，查找数据库，

}

void MessageSequence::removeMessageObserver(std::string messageId, long observerId)
{
    //删除消息队列中指定message的某个观察者（即已查阅了该message的netizen）
    m_messageQueue.at(messageId).removeObserver(observerId);

    //判断该消息是否全部订阅者查阅完毕
    if(m_messageQueue.at(messageId).hasReadAll()){
        std::cout<<"is empty"<<std::endl;
        //若全部查阅完毕，则删除该消息
        removeNotification(messageId);
    }
}
