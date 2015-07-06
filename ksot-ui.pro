#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T11:18:11
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ksot-ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    networkexchange.cpp \
    issueswidget.cpp \
    loginwindow.cpp \
    settingsdialog.cpp \
    nonregisteredawsui.cpp

HEADERS  += mainwindow.h \
    settings.h \
    networkexchange.h \
    issueswidget.h \
    loginwindow.h \
    settingsdialog.h \
    nonregisteredawsui.h

FORMS    += mainwindow.ui \
    issueswidget.ui \
    loginwindow.ui \
    settingsdialog.ui \
    nonregisteredawsui.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    res/myapp.rc \
    icon.ico

#RC_FILE = myapp.rc
RC_ICONS = icon.ico
