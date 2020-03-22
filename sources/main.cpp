/*
 *  main.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"

int main(int argc,char **argv){
    try{
        QApplication q_application(argc, argv);

        MainWindow *main_window = new MainWindow(nullptr);
        main_window->show();

        return q_application.exec();
    }
    catch(...){
        QMessageBox::critical(nullptr,"Interruption","Unknown interruption!");
        return -1;
    }
}
