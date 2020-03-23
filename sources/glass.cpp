/*
 *  glass.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "glass.h"

using namespace Effects;


Glass::Glass(QWidget *parent) : QWidget(parent){
    _parent = parent;

    p_animation = new QPropertyAnimation(this,"opacity");
    p_animation->setDuration(700);
}


void Glass::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    this->setGeometry(0,0,_parent->width(),_parent->height());

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(QBrush("#000000"));
    painter.setOpacity(_opacity);
    painter.drawRect(-1,-1,width()+2,height()+2);

    QWidget::paintEvent(e);
}

void Glass::startShow(){
    this->setVisible(true);
    p_animation->setStartValue(0.0);
    p_animation->setEndValue(0.74);
    p_animation->start();
}

void Glass::endShow(){
    connect(p_animation,SIGNAL(finished()),this,SLOT(theEnd()));
    p_animation->setStartValue(0.74);
    p_animation->setEndValue(0.0);
    p_animation->start();
}
