#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T13:29:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        main_window.cpp \
    map_area.cpp \
    dialog/map_background.cpp \
    dialog/dialog.cpp

HEADERS  += main_window.hpp \
    map_area.hpp \
    dialog/map_background.hpp \
    dialog/dialog.hpp
