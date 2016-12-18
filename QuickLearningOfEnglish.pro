#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T14:04:26
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuickLearningOfEnglish
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    dbmanager.h

FORMS    += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    images.qrc
