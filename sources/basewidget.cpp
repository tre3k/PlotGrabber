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


/* TOP PANEL WIDGET */
TopPanel::TopPanel(If::Interface *_iface, QWidget *parent) : BaseWidget(_iface, parent){
    this->setMinimumHeight(50);
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    iface->top_widget = this;

    RingButton *rb1 = new RingButton();
    RingButton *rb2 = new RingButton();
    RingButton *closeButton = new RingButton();

    layout->addWidget(rb1);
    layout->addWidget(rb2);
    layout->addStretch();
    layout->addWidget(closeButton);

}

void TopPanel::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,false);
    //painter.setPen(style.getPen());
    QPen pen;
    pen.setColor("#525252");
    painter.setPen(pen);
    QBrush brush(QColor("#fcfcfc"));
    painter.setBrush(brush);

    painter.drawRect(-1,-1,width()+1,height()-1);

    QWidget::paintEvent(e);
}


/* IMAGE WIDGET */
ImageWidget::ImageWidget(If::Interface *_iface, QWidget *parent) : BaseWidget(_iface, parent){

}


/* RING BUTTON */
RingButton::RingButton(If::Interface *_iface, QWidget *parent){
    auto layout = new QVBoxLayout(this);
    p_animation = new QPropertyAnimation(this,"color");
    p_animation->setDuration(300);

    layout->setAlignment(Qt::AlignHCenter);
    label = new QLabel("b");
    layout->addWidget(label);

    this->setMinimumHeight(50);
    this->setMinimumWidth(50);

    this->installEventFilter(this);

    _pen.setStyle(Qt::NoPen);
}

void RingButton::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(_pen);
    painter.setBrush(_brush);
    painter.drawEllipse(2,2,44,44);

    QWidget::paintEvent(e);
}


bool RingButton::eventFilter(QObject *watched, QEvent *event){
    if(watched==this){
        switch(event->type()){
        case QEvent::Enter:
            mouseEnter(iface->getStyle()->buttonColorAlpha(),iface->getStyle()->buttonColor());
            break;

        case QEvent::Leave:
            p_animation->stop();
            setColor(iface->getStyle()->buttonColorAlpha());
            break;

        case QEvent::MouseButtonPress:
            _pen.setStyle(Qt::SolidLine);
            _pen.setColor(iface->getStyle()->buttonBorderColor());
            _pen.setWidth(iface->getStyle()->buttonBorder());
            repaint();
            emit clicked();
            break;

        case QEvent::MouseButtonRelease:
            _pen.setStyle(Qt::NoPen);
            repaint();
            break;
        }
    }

    return QWidget::eventFilter(watched, event);
}
