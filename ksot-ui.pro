#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T11:18:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ksot-ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    networkexchange.cpp \
    issueswidget.cpp \
    loginwindow.cpp \
    userwidget.cpp

HEADERS  += mainwindow.h \
    settings.h \
    networkexchange.h \
    issueswidget.h \
    loginwindow.h \
    userwidget.h

FORMS    += mainwindow.ui \
    issueswidget.ui \
    loginwindow.ui \
    userwidget.ui
