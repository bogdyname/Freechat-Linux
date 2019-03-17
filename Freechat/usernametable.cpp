/*
***Copyright (C) 2019 Freechat Inc
***Contact: bogdyname@gmail.com
*/

#include "usernametable.h"

#include <iostream>

using namespace std;

usernametable::usernametable()
{
    cout << getMacAddress().toAscii().constData() << endl; // CHECK THIS OUT
    exit(1); // CHECK THIS OUT

    QList< QHostAddress > addresses = QHostInfo::fromName( QHostInfo::localHostName() ).addresses();
          foreach ( const QHostAddress & a, addresses )
          {
              QString protocol = "???";
              switch ( a.protocol() )
              {
                  case QAbstractSocket::IPv4Protocol:
                      protocol = "IPv4";
                  break;
                  case QAbstractSocket::IPv6Protocol:
                      protocol = "IPv6";
                  break;
              }
              qDebug() << a.toString() << "(" << protocol << ")";

          }
}

tabletranslation::tabletranslation()
{

}

