QT += core gui widgets

CONFIG += c++2a
QTPLUGIN += qsvg

TEMPLATE = app
TARGET = plotgrabber

SOURCES  =   sources/main.cpp \
             sources/mainwindow.cpp \
             sources/basewidget.cpp \
             sources/style.cpp \
             sources/interface.cpp \
             sources/glass.cpp \
             sources/mainwidget.cpp \
             sources/elementwidgets.cpp \
             sources/settingdialog.cpp \
             sources/darwingelements.cpp \
             sources/calculation.cpp

HEADERS  =   sources/mainwindow.h \
             sources/basewidget.h \
             sources/style.h \
             sources/interface.h \
             sources/glass.h \
             sources/mainwidget.h \
             sources/elementwidgets.h \
             sources/settingdialog.h \
             sources/darwingelements.h \
             sources/calculation.h

RESOURCES += resources.qrc
