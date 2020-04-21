QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    database/postgresql.cpp \
    main.cpp \
    math/math.cpp \
    network/network.cpp \
    ui/favorite.cpp \
    ui/worldcash.cpp

HEADERS += \
    database/postgresql.h \
    math/math.h \
    network/network.h \
    ui/favorite.h \
    ui/worldcash.h

FORMS += \
    ui/favorite.ui \
    ui/worldcash.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
