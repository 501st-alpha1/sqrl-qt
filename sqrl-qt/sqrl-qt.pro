#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T16:42:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqrl-qt
TEMPLATE = app
LIBS += -lqca
CONFIG += crypto

SOURCES += main.cpp\
        mainwindow.cpp \
    identitycreationwindowpage1.cpp \
    identitycreationwindowpage2.cpp

HEADERS  += mainwindow.h \
    identitycreationwindowpage1.h \
    identitycreationwindowpage2.h

FORMS    += mainwindow.ui \
    identitycreationwindowpage1.ui \
    identitycreationwindowpage2.ui
