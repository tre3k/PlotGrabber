QT += core gui widgets

CONFIG += c++2a

TEMPLATE = app
TARGET = plotgrabber

SOURCES =   sources/main.cpp \
            sources/mainwindow.cpp \
            sources/basewidget.cpp \
            sources/style.cpp \
            sources/interface.cpp \
            sources/glass.cpp

HEADERS =   sources/mainwindow.h \
            sources/basewidget.h \
            sources/style.h \
            sources/interface.h \
            sources/glass.h

RESOURCES += \
    resources.qrc
