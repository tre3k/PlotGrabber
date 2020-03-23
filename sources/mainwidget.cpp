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
    iface->main_widget = this;

    auto layout = new QVBoxLayout(this);
    //layout->setAlignment(Qt::AlignHCenter);

    auto image_widget = new ImageWidget();
    layout->addWidget(image_widget);
}
