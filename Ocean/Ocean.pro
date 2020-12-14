QT       += core gui
QT       += network
QT       += multimedia
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    customWidgets/button.cpp \
    customWidgets/customlistwidget.cpp \
    customWidgets/slider.cpp \
    imports/importmanager.cpp \
    main.cpp \
    player/player.cpp \
    playlists/playlist.cpp \
    ui/addmusicwidget.cpp \
    ui/getstringwidget.cpp \
    ui/ocean.cpp \
    ui/selectplaylist.cpp

HEADERS += \
    customWidgets/button.h \
    customWidgets/customlistwidget.h \
    customWidgets/slider.h \
    imports/importmanager.h \
    player/player.h \
    playlists/playlist.h \
    ui/addmusicwidget.h \
    ui/getstringwidget.h \
    ui/ocean.h \
    ui/selectplaylist.h

FORMS += \
    ui/addmusicwidget.ui \
    ui/getstring.ui \
    ui/ocean.ui \
    ui/selectplaylist.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc
