#include "netizenproxy.h"
#include "netizenbroker.h"
#include "netizen.h"
#include <iostream>

NetizenProxy::NetizenProxy(long id) :
    m_id{id}, m_netizen{}
{

}

NetizenProxy::~NetizenProxy()
{

}

std::vector<std::string> NetizenProxy::getInfo(long id)
{
    if (m_netizen == nullptr)
        m_netizen = NetizenBroker::getInstance()->findNetizenById(id);
    return m_netizen->getInfo();
}
