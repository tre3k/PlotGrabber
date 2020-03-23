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

namespace If {

class Interface{
private:
    Styles::Style *style;

public:
    Interface(){}
    void setStyle(Styles::Style *_style){
        style = _style;
    }
    Styles::Style *getStyle(void){return style;}

    QWidget *main_window = nullptr;
    QWidget *top_widget = nullptr;
    QWidget *main_widget = nullptr;

};

}


#endif
