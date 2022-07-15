#ifndef MESSAGESEQUENCE_H
#define MESSAGESEQUENCE_H

#include "relationalbroker.h"
class PublishVideoNotification;
class MessageSequence : public RelationalBroker
{
public:

    ~MessageSequence();
    static MessageSequence* getInstance();

    //加入指定message
    void pushNotification(PublishVideoNotification notification);
    //删除指定message
    void removeNotification(std::string id);
    //获取指定message
    PublishVideoNotification* findById(const std::string& id);

    //更新消息队列
    void updateMessageQueue();
    //移除指定message的某个观察者
    void removeMessageObserver(std::string messageId,long observerId);

private:
    static MessageSequence* m_messageSeq;
    MessageSequence();
    std::unordered_map<std::string, PublishVideoNotification> m_messageQueue;
};

#endif // MESSAGESEQUENCE_H
