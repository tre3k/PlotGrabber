/*
 *  interface.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

#include "style.h"

#include <QDebug>

namespace If {

class Interface : public QObject{
    Q_OBJECT
private:
    Styles::Style *style;

public:
    Interface(QObject *parent = nullptr) : QObject(parent){}
    void setStyle(Styles::Style *_style){
        style = _style;
    }
    Styles::Style *getStyle(void){return style;}

    QWidget *main_window = nullptr;
    QWidget *top_widget = nullptr;
    QWidget *main_widget = nullptr;
    QWidget *image_widget = nullptr;

    struct s_settings{
        bool light_dark {false};
        Styles::SecondStyle second_style {Styles::STYLE_BLUE};
    } settings;

public slots:
    void update(){
        qDebug() << "Iface update!\n";
        style->update();
        emit updated();
    }

signals:
    void updated();

};

}


#endif
