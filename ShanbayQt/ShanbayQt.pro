#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T17:35:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network
QT += webkit
QT += webkitwidgets

TARGET = ShanbayQt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    shanbay.cpp \
    json.cpp

HEADERS  += widget.h \
    shanbay.h \
    json.h

FORMS    += widget.ui
