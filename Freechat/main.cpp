/*
***Copyright (C) 2019 Softwater Inc
***Contact: bogdyname@gmail.com
*/

#include "freechat.h"
#include <QApplication>
#include <QtCore/QSettings>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QNetworkConfigurationManager manager;

    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);

        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }
        else
        {
            /*CLEAR CODE*/
        }

        QNetworkSession *networkSession = new QNetworkSession(config, &app);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen())
        {
            QNetworkConfiguration config = networkSession->configuration();
            QString id;

            if (config.type() == QNetworkConfiguration::UserChoice)
            {
                id = networkSession->sessionProperty(
                QLatin1String("UserChoiceConfiguration")).toString();
            }
            else
            {
                id = config.identifier();
            }

            QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
            settings.beginGroup(QLatin1String("QtNetwork"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
        else
        {
            /*CLEAR CODE*/
        }
    }
    else
    {
        /*CLEAR CODE*/
    }

    Freechat freechat;
    freechat.show();
    return app.exec();
}
