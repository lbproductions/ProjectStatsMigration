#-------------------------------------------------
#
# Project created by QtCreator 2012-06-06T19:03:23
#
#-------------------------------------------------

QT       += core

TARGET = lbdatabaseexporter
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../include/

LIBS += -L$$OUT_PWD/../ProjectStats-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Debug/lib/LBDatabase/
LIBS += -llbdatabase


SOURCES += main.cpp \
    graphvizexporter.cpp \
    cppexporter.cpp \
    storagewriter.cpp \
    writer.cpp \
    contextwriter.cpp \
    entitytypewriter.cpp \
    calculatorwriter.cpp

HEADERS += \
    graphvizexporter.h \
    cppexporter.h \
    storagewriter.h \
    writer.h \
    contextwriter.h \
    entitytypewriter.h \
    calculatorwriter.h
