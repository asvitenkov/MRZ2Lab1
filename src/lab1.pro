#-------------------------------------------------
#
# Project created by QtCreator 2013-10-26T13:12:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app

DESTDIR = ../bin
OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    neuralnetwork.cpp \
    worker.cpp \
    thirdreport.cpp \
    secondreport.cpp \
    fourthreport.cpp \
    firstreport.cpp \
    defines.cpp

HEADERS  += mainwindow.h \
    image.h \
    neuralnetwork.h \
    worker.h \
    thirdreport.h \
    secondreport.h \
    fourthreport.h \
    firstreport.h \
    defines.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += armadillo
DEPENDPATH += armadillo


QMAKE_LFLAGS += -O3

QMAKE_CXXFLAGS_DEBUG += -DARMA_NO_DEBUG
QMAKE_CFLAGS_RELEASE += -DARMA_NO_DEBUG