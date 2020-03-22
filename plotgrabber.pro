QT += core gui widgets

CONFIG += c++2a

TEMPLATE = app
TARGET = plotgrabber

SOURCES =   sources/main.cpp \
            sources/mainwindow.cpp \
            sources/basewidget.cpp \
            sources/style.cpp \
            sources/interface.cpp

HEADERS =   sources/mainwindow.h \
            sources/basewidget.h \
            sources/style.h \
            sources/interface.h

RESOURCES += \
    resources.qrc
