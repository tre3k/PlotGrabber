/*
 *  mainwindow.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    If::Interface *interface = new If::Interface();
    Styles::Style *style = new Styles::Style(Styles::STYLE_LIGHT,Styles::STYLE_ORANGE);
    style->update();

    interface->setStyle(style);
    interface->main_window = this;

    auto central_widget = new Widgets::CentralWidget(interface);

    this->setCentralWidget(central_widget);

}

MainWindow::~MainWindow(){

}
