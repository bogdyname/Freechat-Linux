#---------------------------------
#Freechat (decentralized chat)
#Freechat via C++ & Qt, Debugger(Qt 5.12.1 GCC 64bit)
#Copyleft (C) 2019 Softwater, Inc.
#---------------------------------

QT       += core gui
QT       += network
QT       += gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 5.4): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += console
CONFIG += app_bundle
CONFIG += qt

SOURCES += \
        connectionf2f.cpp \
        main.cpp \
        freechat.cpp \
        datasave.cpp \
        usernametable.cpp \
        username.cpp

HEADERS += \
        connectionf2f.h \
        freechat.h \
        datasave.h \
        usernametable.h \
        username.h \

FORMS += \
        freechat.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
