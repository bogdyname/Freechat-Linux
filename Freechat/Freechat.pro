#---------------------------------
#Copyright (C) 2019 Softwater Inc
#Contact: bogdyname@gmail.com
#---------------------------------

QT       += core gui
QT       += network
QT       += gui
QT       += multimedia
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Freechat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += console
CONFIG += app_bundle
CONFIG += qt

SOURCES += \
        main.cpp \
        freechat.cpp \
        connection.cpp \
        userserver.cpp \
        userclient.cpp \
        datasave.cpp \
        multimedia.cpp \
        usernametable.cpp \
        username.cpp \
        peermanager.cpp

HEADERS += \
        freechat.h \
        connection.h \
        userserver.h \
        userclient.h \
        datasave.h \
        multimedia.h \
        usernametable.h \
        username.h \
        peermanager.h

FORMS += \
        freechat.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
