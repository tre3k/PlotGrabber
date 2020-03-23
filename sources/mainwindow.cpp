/*
 *  mainwindow.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    interface = new If::Interface();
    Styles::Style *style = new Styles::Style(Styles::STYLE_LIGHT,Styles::STYLE_GREEN);
    style->update();

    interface->setStyle(style);
    interface->main_window = this;

    auto central_widget = new Widgets::CentralWidget(interface);

    this->setCentralWidget(central_widget);

    glass_widget = new Effects::Glass(this);
    glass_widget->setVisible(false);
    glass_widget->setDuration(100);


    settings_dialog = new Dialogs::Settings(interface);
    settings_dialog->setPalette(style->getPalette());
    connect(settings_dialog,SIGNAL(finished(int)),this,SLOT(hideSettings(int)));

    updatePalette();
    connect(interface,SIGNAL(updated()),this,SLOT(updatePalette()));
}



void MainWindow::openImage(){
    QFileDialog fd;
    fd.setPalette(interface->getStyle()->getPalette());
    fd.getOpenFileName();
}
