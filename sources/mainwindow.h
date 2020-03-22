/*
 *  mainwindow.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include "basewidget.h"
#include "style.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private:

public slots:
    void closeApplication(void){QApplication::quit();}

};


namespace Widgets {
class CentralWidget : public BaseWidget{
    Q_OBJECT
public:
    CentralWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr){
        auto layout = new QVBoxLayout(this);
        auto top_panel = new TopPanel(_iface);
        auto image_widget = new ImageWidget(_iface);

        top_panel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Maximum);
        image_widget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);



        layout->setMargin(0);
        layout->setSpacing(0);

        layout->addWidget(top_panel);
        layout->addWidget(image_widget);
    }
};

}

#endif
