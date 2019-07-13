#include "peerin.h"

Peerin::Peerin()
{
    connect(&showNetworkInfo, SIGNAL(ShowWANIpForUser()), this, SLOT(PassOnMyIpAddress()));
}

void Peerin::PassOnMyIpAddress()
{
    PassOnWANIp(strPassOnWANip);

    QMessageBox::information(this, tr("WAN IP"),
                    tr("Do not show this IP to anyone!"), tr(strPassOnWANip));

    return;
}
