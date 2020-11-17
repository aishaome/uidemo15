#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T18:38:15
#
#-------------------------------------------------

QT       += core gui sql network axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = uidemo15
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/bin

CONFIG      += warn_off
HEADERS     += head.h
SOURCES     += main.cpp
RESOURCES   += other/main.qrc
RESOURCES   += other/qss.qrc
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/api
INCLUDEPATH += $$PWD/form
INCLUDEPATH += $$PWD/ffmpeg
include ($$PWD/api/api.pri)
include ($$PWD/form/form.pri)
include ($$PWD/ffmpeg/ffmpeg.pri)

INCLUDEPATH += $$PWD/sdk/include
win32: LIBS += -L$$PWD/sdk/lib/ -lquc

