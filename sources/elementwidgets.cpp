/*
 *  elementwidgets.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "elementwidgets.h"

using namespace Widgets;

/* RING BUTTON */
RingButton::RingButton(If::Interface *_iface, QWidget *parent) : BaseWidget(parent){
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


/* TOP PANEL WIDGET */
TopPanel::TopPanel(If::Interface *_iface, QWidget *parent) : BaseWidget(_iface, parent){
    this->setMinimumHeight(50);
    auto layout = new QHBoxLayout(this);

    filename_label = new QLabel();

    layout->setMargin(0);
    layout->setSpacing(0);

    iface->top_widget = this;

    open_button = new RingButton();
    sett_button = new RingButton();
    updatePixmapsOnButtons();

    connect(sett_button,SIGNAL(release()),iface->main_window,SLOT(showSettings()));

    layout->addWidget(open_button);
    layout->addWidget(sett_button);
    layout->addWidget(filename_label);
    layout->addStretch();

    connect(iface,SIGNAL(updated()),this,SLOT(updatePixmapsOnButtons()));

    setFileNameLabel("Filename.123");
}

void TopPanel::updatePixmapsOnButtons(){
    open_button->setPixmap(iface->getStyle()->buttonOpenPixmap());
    sett_button->setPixmap(iface->getStyle()->buttonSettingPixmap());
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

