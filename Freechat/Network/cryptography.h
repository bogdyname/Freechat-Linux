/*
***Copyleft (C) 2019 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Network/connectionf2f.h"

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

using namespace QSsl;
using namespace QPasswordDigestor;

class Cryptography
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
