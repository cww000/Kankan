#ifndef NETIZENPROXY_H
#define NETIZENPROXY_H

#include <memory>
#include <vector>
#include "netizeninterface.h"
#include "json.hpp"

class Netizen;

class NetizenProxy : public NetizenInterface
{
public:
    NetizenProxy(long id);
    ~NetizenProxy();

    nlohmann::json getInfo(long id);
    bool isOnline();
    void updateMessage(std::string messageId);
private:
    long m_id;
    std::shared_ptr<Netizen> m_netizen;
};

#endif // NETIZENPROXY_H
