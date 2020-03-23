/*
 *  mainwidget.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "mainwidget.h"

using namespace Widgets;


/* MAIN WIDGET */
MainWidget::MainWidget(If::Interface *_iface, QWidget *parent) : BaseWidget(_iface, parent){
    auto label = new QLabel("test");
    label->setAlignment(Qt::AlignVCenter);
    auto layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label);
}
