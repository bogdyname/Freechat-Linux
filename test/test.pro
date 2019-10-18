

QT       += gui
QT       += svg
QT       += network
QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = test
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17
CONFIG += qt

SOURCES += \
        Bin/bin.cpp \
        Network/connectionf2f.cpp \
        Network/peerin.cpp \
        Network/peerout.cpp \
        main.cpp \
        Bin/freechat.cpp

HEADERS += \
        Bin/bin.h \
        Network/connectionf2f.h \
        Bin/freechat.h \
        Network/peerin.h \
        Network/peerout.h

FORMS += \
        freechat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
