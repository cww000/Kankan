#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "messagesequence.h"
#include "publishvideonotification.h"

MessageSequence* MessageSequence::m_messageSeq = nullptr;

MessageSequence::MessageSequence()
{
    m_messageQueue.clear();
    //1. 读取数据库中的数据，并初始化到消息队列中
    std::string sql = "select * from message";
    std::shared_ptr<sql::ResultSet> res = query(sql);
    std::vector<std::string> parameters;
    long senderId;
    while (res->next()) {
        parameters.push_back(res->getString(1).c_str());
        parameters.push_back(res->getString(2).c_str());
        parameters.push_back(res->getString(3).c_str());
        senderId = res->getLong(4);
        parameters.push_back(res->getString(5).c_str());
        m_messageQueue.insert({parameters[0], PublishVideoNotification(parameters[0], parameters[1], parameters[2], senderId, parameters[3])});
    }

     //2. 将每条消息对应的接收者注册为观察者
    for (auto& message : m_messageQueue) {
        sql = "select fanId from send where messageId='" + message.first + "'";
        res = query(sql);
        while (res->next()) {
            message.second.registerObserver(res->getLong(1));
        }
    }
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
    //1.将发布稿件消息添加到消息队列
    m_messageQueue.insert({notification.id(), notification});

    //2.将消息存入数据库
    std::string sql = "insert into message values('" + notification.id() + "','" + notification.content() + "','" + notification.date() + "'," + std::to_string(notification.senderId()) + ",'" + notification.videoId() + "')";
    std::cout << sql << std::endl;
    insert(sql);

    //3.将消息相关联的粉丝存入数据库
    for (auto& ob : notification.observer()) {
        sql = "insert into send values('" + notification.id() + "'," + std::to_string(ob.first) + ")";
        std::cout << sql << std::endl;
        insert(sql);
    }
}

void MessageSequence::removeNotification(std::string id)
{
    m_messageQueue.erase(id);

    //删除数据库中对应的某条消息
    std::string sql = "delete from message where id='" + id + "'";
    del(sql);
}

PublishVideoNotification* MessageSequence::findById(const std::string& id)
{
    if (m_messageQueue.find(id) != m_messageQueue.end()) {
        return &m_messageQueue.at(id);
    } else {
        return nullptr;
    }
}

void MessageSequence::updateMessageQueue()
{
    //发送消息队列中所有的message
    for(auto& message:m_messageQueue){
        message.second.notifyObserver();
    }

    //遍历消息队列中的每条消息，查找数据库
    std::shared_ptr<sql::ResultSet> res;
    std::string sql;
    for (auto& message : m_messageQueue) {
        sql = "select fanId from send where messageId='" + message.first + "'";
        res = query(sql);
        while (res->next()) {
            long id = res->getLong(1);
            //删除数据库中对应的在消息队列的某条消息中已被删除的观察者
            if (message.second.observer().count(id) == 0) {
                sql = "delete from send where fanId=" + std::to_string(id) + " and messageId='" + message.first + "'";
                del(sql);
            }
        }
    }
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
