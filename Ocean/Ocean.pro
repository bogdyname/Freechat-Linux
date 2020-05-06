QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    imports/importmanager.cpp \
    main.cpp \
    player/player.cpp \
    playlists/playlist.cpp \
    ui/ocean.cpp

HEADERS += \
    imports/importmanager.h \
    player/player.h \
    playlists/playlist.h \
    ui/ocean.h

FORMS += \
    ui/ocean.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
