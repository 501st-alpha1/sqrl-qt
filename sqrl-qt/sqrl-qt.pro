#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T16:42:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqrl-qt
TEMPLATE = app
LIBS += -lsodium
CONFIG += crypto

SOURCES += main.cpp\
        mainwindow.cpp \
    identitycreationwindowpage1.cpp \
    identitycreationwindowpage2.cpp \
    sodiumwrap.cpp \
    sqrlauthenticator.cpp \
    sqrlidentity.cpp \
    sqrlsettings.cpp \
    authenticationconfirmation.cpp

HEADERS  += mainwindow.h \
    identitycreationwindowpage1.h \
    identitycreationwindowpage2.h \
    sodiumwrap.h \
    sqrlauthenticator.h \
    sqrlidentity.h \
    sqrlsettings.h \
    authenticationconfirmation.h

FORMS    += mainwindow.ui \
    identitycreationwindowpage1.ui \
    identitycreationwindowpage2.ui \
    authenticationconfirmation.ui
