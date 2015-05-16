#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T11:31:29
#
#-------------------------------------------------

QT       += core network 

QT       -= gui

TARGET = joystick_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    joystick.cpp \
    udppacketsender.cpp \
    heartbeat.cpp

HEADERS += \
    joystick.h \
    udppacketsender.h \
    heartbeat.h
