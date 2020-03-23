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

#include "style.h"
#include "glass.h"
#include "elementwidgets.h"
#include "mainwidget.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private:
    Effects::Glass *gls;

protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void closeApplication(void){QApplication::quit();}
    void showGlass(void){gls->startShow();}
    void hideGlass(void){gls->endShow();}

};

namespace Widgets {
class CentralWidget : public BaseWidget{
    Q_OBJECT
public:
    CentralWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr){
        auto layout = new QVBoxLayout(this);
        auto top_panel = new TopPanel(_iface);
        auto main_widget = new MainWidget(_iface);

        top_panel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Maximum);
        main_widget->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

        layout->setMargin(0);
        layout->setSpacing(0);

        layout->addWidget(top_panel);
        layout->addWidget(main_widget);



    }
};

}

#endif
