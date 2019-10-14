/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "Network/connectionf2f.h"

using namespace QSsl;
using namespace QPasswordDigestor;

class Cryptography : private ConnectionF2F
{
    Q_OBJECT

public:
    Cryptography();
    ~Cryptography();

    void DigitalSignature();

private:
    friend class ConnectionF2F;
};
#endif
