#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T16:42:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqrl-qt
TEMPLATE = app
LIBS += -lqca2 -lsodium
CONFIG += crypto

SOURCES += main.cpp\
        mainwindow.cpp \
    identitycreationwindowpage1.cpp \
    identitycreationwindowpage2.cpp \
    sqrlidentity.cpp

HEADERS  += mainwindow.h \
    identitycreationwindowpage1.h \
    identitycreationwindowpage2.h \
    sqrlidentity.h

FORMS    += mainwindow.ui \
    identitycreationwindowpage1.ui \
    identitycreationwindowpage2.ui
