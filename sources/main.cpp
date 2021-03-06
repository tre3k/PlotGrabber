/*
 *  main.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"

/* static variable */
If::Interface* Widgets::BaseWidget::iface = nullptr;

/* Entry point */
int main(int argc,char **argv){
    try{
        QApplication q_application(argc, argv);

        MainWindow *main_window = new MainWindow(nullptr);
        //main_window->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        main_window->setGeometry(0,0,600,400);
        main_window->setWindowTitle("PlotGrabber");
        main_window->show();

        return q_application.exec();
    }
    catch(...){
        QMessageBox::critical(nullptr,"Interruption","Unknown interruption!");
        return -1;
    }
}
