#include "netizenproxy.h"
#include "netizenbroker.h"
#include "netizen.h"
#include <iostream>

NetizenProxy::NetizenProxy(std::string id) :
    m_id{id}, m_netizen{}
{

}

NetizenProxy::~NetizenProxy()
{

}

nlohmann::json NetizenProxy::getInfo(std::string id)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(id);
    return m_netizen->getInfo();
}

bool NetizenProxy::isOnline()
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);
    return m_netizen->online();
}

void NetizenProxy::updateMessage(std::string messageId)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(m_id);
    return m_netizen->updateMessage(messageId);
}
