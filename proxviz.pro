#-------------------------------------------------
#
# Project created by QtCreator 2013-07-19T11:13:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proxviz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datareader.cpp \
    ubidatareader.cpp \
    badgedatareader.cpp \
    qvertex.cpp \
    qedge.cpp \
    graph.cpp \
    forceatlas2.cpp \
    graphvizdatareader.cpp \
    modedialog.cpp \
    glwidget.cpp \
    barneshutregion.cpp \

HEADERS  += mainwindow.h \
    graph.h \
    datareader.h \
    ubidatareader.h \
    badgedatareader.h \
    qvertex.h \
    qedge.h \
    forceatlas2.h \
    graphvizdatareader.h \
    modedialog.h \
    glwidget.h \
    barneshutregion.h \

FORMS    += mainwindow.ui \
    modedialog.ui

LIBS += -L/usr/lib -lboost_graph -lboost_regex -lboost_thread -lboost_system
