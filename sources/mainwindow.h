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
#include <QFileDialog>

#include "style.h"
#include "glass.h"
#include "elementwidgets.h"
#include "mainwidget.h"
#include "settingdialog.h"

#include <QDebug>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){}

private:
    Effects::Glass *glass_widget;
    Dialogs::Settings *settings_dialog;
    If::Interface *interface;

protected:


public slots:
    void closeApplication(void){QApplication::quit();}
    void showGlass(void){glass_widget->startShow();}
    void hideGlass(void){glass_widget->endShow();}
    void showSettings(void){
        showGlass();
        settings_dialog->setGeometry(x(),y(),300,400);
        settings_dialog->show();
    }
    void hideSettings(int result){
        hideGlass();
    }
    void updatePalette(void){
        this->setPalette(interface->getStyle()->getPalette());
        settings_dialog->setPalette(interface->getStyle()->getPalette());
        this->update();
    }

    void openImage(void);

signals:
    void fileNameChanged(QString filename);
};


namespace Widgets {

/* CENTRAL WIDGET */
class CentralWidget : public BaseWidget{
    Q_OBJECT
public:
    CentralWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr) : BaseWidget(_iface,parent){
        auto layout = new QVBoxLayout(this);
        auto top_panel = new TopPanel(_iface);
        auto main_widget = new MainWidget(_iface);

        /* place top panel and main widget */
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
