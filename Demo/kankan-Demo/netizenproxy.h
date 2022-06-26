#ifndef NETIZENPROXY_H
#define NETIZENPROXY_H

#include <memory>
#include "netizeninterface.h"

class Netizen;

class NetizenProxy : public NetizenInterface
{
public:
    NetizenProxy(long id);
    ~NetizenProxy();
private:
    long m_id;
    std::shared_ptr<Netizen> m_netizen;
};

#endif // NETIZENPROXY_H
