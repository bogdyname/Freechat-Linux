/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef FIREWALL_H
#define FIREWALL_H

#include "Network/connectionf2f.h"

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
