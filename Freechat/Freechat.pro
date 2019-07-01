#---------------------------------
#Freechat (decentralized chat)
#Freechat via C++ & Qt, Debugger(Qt 5.12.1 GCC 64bit)
#Copyleft (C) 2019 Softwater, Inc.
#---------------------------------

QT       += core gui
QT       += widgets
QT       += network
QT       += gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 5.4): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17
CONFIG += console
CONFIG += app_bundle
CONFIG += qt

SOURCES += \
        Bin/bin.cpp \
        Network/connectionf2f.cpp \
        Network/cryptography.cpp \
        Network/cryptography.cpp \
        Network/firewall.cpp \
        Network/firewall.cpp \
        main.cpp \
        Bin/freechat.cpp \
        Data/datasave.cpp

HEADERS += \
        Bin/bin.h \
        Network/connectionf2f.h \
        Bin/freechat.h \
        Data/datasave.h \
        Network/cryptography.h \
        Network/cryptography.h \
        Network/firewall.h \
        Network/firewall.h

FORMS += \
        Designer/freechat.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
