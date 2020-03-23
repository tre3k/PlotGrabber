/*
 *  mainwidget.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "elementwidgets.h"

namespace Widgets {

/* MAIN WIDGET */
class MainWidget : public BaseWidget{
    Q_OBJECT
private:

public:
    MainWidget(If::Interface *_iface = nullptr,QWidget *parent = nullptr);
public slots:

};


}

#endif
