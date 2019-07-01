/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"

#ifndef FIREWALL_H
#define FIREWALL_H
class Firewall : public ConnectionF2F
{
    Q_OBJECT

public:
    Firewall();
    ~Firewall();

    void CheckAllPortsByPeer();
    void CheckWANAddrFromPeer();

private:
    friend class ConnectionF2F;
};
#endif
