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

    RingButton *open_button = new RingButton();
    open_button->setPixmap(iface->getStyle()->buttonOpenPixmap());
    RingButton *sett_button = new RingButton();
    sett_button->setPixmap(iface->getStyle()->buttonSettingPixmap());
    RingButton *close_button = new RingButton();
    close_button->setPixmap(iface->getStyle()->buttonColosePixmap());

    connect(close_button,SIGNAL(release()),iface->main_window,SLOT(closeApplication()));

    layout->addWidget(open_button);
    layout->addWidget(sett_button);
    layout->addStretch();
    layout->addWidget(close_button);

}

void TopPanel::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,false);
    QPen pen;
    pen.setColor(iface->getStyle()->topPanelBorderColor());
    painter.setPen(pen);
    QBrush brush(iface->getStyle()->topPanelBackgroud());
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

    layout->setAlignment(Qt::AlignVCenter);
    label = new QLabel("+");
    label->setAlignment(Qt::AlignHCenter);
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
    painter.drawEllipse(4,4,42,42);
    //painter.drawRect(QRect(4,4,42,42));

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
            emit release();
            break;

        default:
            // just for minimisate warnings at the moment compilation
            break;
        }
    }

    return QWidget::eventFilter(watched, event);
}
