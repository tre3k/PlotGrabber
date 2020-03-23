/*
 *  basewidget.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "basewidget.h"

using namespace Widgets;

/* BASE WIDGET */
BaseWidget::BaseWidget(If::Interface *_iface, QWidget *parent) : QWidget(parent){
    if(_iface!=nullptr) setInterface(_iface);
}

BaseWidget::~BaseWidget(){

}

