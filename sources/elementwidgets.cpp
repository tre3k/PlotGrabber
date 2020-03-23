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
    //painter.drawEllipse(4,4,42,42);
    constexpr int diameter = 42;
    painter.drawEllipse(width()/2-diameter/2,height()/2-diameter/2,diameter,diameter);
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

/* Color Ring Button */
ColorRingButton::ColorRingButton(If::Interface *_iface, QWidget *parent) : BaseWidget(parent){
    this->installEventFilter(this);
    this->setMinimumSize(diameter+iface->getStyle()->buttonBorder()+1,
                         diameter+iface->getStyle()->buttonBorder()+1);
    _pen.setStyle(Qt::NoPen);
}

void ColorRingButton::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing,true);
    _pen.setWidth(iface->getStyle()->buttonBorder());
    _pen.setColor(iface->getStyle()->buttonBorderColor());
    painter.setPen(_pen);
    painter.setBrush(_brush);
    painter.drawEllipse(width()/2-diameter/2,height()/2-diameter/2,diameter,diameter);

    QWidget::paintEvent(e);
}

bool ColorRingButton::eventFilter(QObject *watched, QEvent *event){
    if(watched==this){
        switch(event->type()){
        case QEvent::MouseButtonPress:
            setChecked(!_state);
            break;
        default:
            // just for minimisate warnings at the moment compilation
            break;
        }
    }
    return QWidget::eventFilter(watched, event);
}


/* Color Ring Buttons! */
ColorRingButtons::ColorRingButtons(If::Interface *_iface, QWidget *parent) : BaseWidget(parent){
    auto layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    for(auto color : iface->getStyle()->secondStylesColors){
        color.setAlpha(0xac);
        buttons.append(new ColorRingButton());
        buttons.last()->setBrush(QColor(color));
        layout->addWidget(buttons.last());
        states.append(buttons.last()->getState());
        connect(buttons.last(),SIGNAL(stateChanged(bool)),this,SLOT(buttonSelected(bool)));
    }

    this->setButtonSelect(iface->getStyle()->seconStyle());
}


/* TOGGLE BUTTON */
ToggleButton::ToggleButton(If::Interface *_iface, QWidget *parent) : BaseWidget(parent){
    this->installEventFilter(this);
    this->setMinimumHeight(backgroud_height+8);
    this->setMinimumWidth(backgroud_width+8);
    p_animation = new QPropertyAnimation(this,"cpos");
    p_animation->setDuration(200);
    setState(_state);

    connect(iface,SIGNAL(updated()),this,SLOT(update()));

    _circle_pen.setWidth(4);
    _back_pen.setStyle(Qt::NoPen);
}

void ToggleButton::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    const int background_pos_x = width()/2-backgroud_width/2;
    const int background_pos_y = height()/2-backgroud_height/2;
    painter.setRenderHint(QPainter::Antialiasing,true);

    if(_state){
        _circle_pen.setColor(iface->getStyle()->buttonBorderColor());
        _circle_brush = QBrush(iface->getStyle()->backColor());
        _back_brush = QBrush(iface->getStyle()->buttonBorderColor());
    }else{
        _circle_pen.setColor(iface->getStyle()->frontColor());
        _circle_brush = QBrush(iface->getStyle()->backColor());
        _back_brush = QBrush(iface->getStyle()->frontColor());
    }


    painter.setBrush(_back_brush);
    painter.setPen(_back_pen);
    painter.drawRoundedRect(background_pos_x,background_pos_y,backgroud_width,backgroud_height,backgroud_height/2,backgroud_height/2);

    painter.setBrush(_circle_brush);
    painter.setPen(_circle_pen);
    painter.drawEllipse(background_pos_x-2+backgroud_width*_circle_position/2,background_pos_y-2,backgroud_height+4,backgroud_height+4);

    QWidget::paintEvent(e);
}

bool ToggleButton::eventFilter(QObject *watched, QEvent *event){
    if(watched==this){
        switch(event->type()){
        case QEvent::MouseButtonPress:
            p_animation->stop();
            setState(!_state);
            emit stateChanged(_state);
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
    connect(open_button,SIGNAL(release()),iface->main_window,SLOT(openImage()));
    sett_button = new RingButton();
    connect(sett_button,SIGNAL(release()),iface->main_window,SLOT(showSettings()));
    updatePixmapsOnButtons();

    layout->addWidget(open_button);
    layout->addWidget(sett_button);
    layout->addWidget(filename_label);
    layout->addStretch();

    connect(iface,SIGNAL(updated()),this,SLOT(updatePixmapsOnButtons()));
    connect(iface->main_window,SIGNAL(fileNameChanged(QString)),this,SLOT(setFileNameLabel(QString)));
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


/* IMAGE WIDGET */
ImageWidget::ImageWidget(If::Interface *_iface, QWidget *parent) : BaseWidget(_iface,parent){
    iface->image_widget = this;
    connect(iface->main_window,SIGNAL(fileNameChanged(QString)),this,SLOT(setImage(QString)));
    this->setMinimumSize(200,100);
    installEventFilter(this);
    setFocusPolicy(Qt::ClickFocus);         // for keys from keyboard

    cursor = Darwings::Cursor(this);
    cursor.setPos(width()/2,height()/2);

    updateDarwingElements();
    connect(iface,SIGNAL(updated()),this,SLOT(updateDarwingElements()));

}

void ImageWidget::setImage(QString filename){
    _pixmap = QPixmap(filename);
    update();
}

void ImageWidget::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.drawPixmap(0,0,width()+100,height()+100,_pixmap);

    cursor.paint(&painter);

    QWidget::paintEvent(e);
}

void ImageWidget::mousePressEvent(QMouseEvent *e){
    cursor.setPos(e->localPos().x(), e->localPos().y());
    update();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *e){
    cursor.setPos(e->localPos().x(), e->localPos().y());
    update();
}

void ImageWidget::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Up:
        cursor.setPos(cursor.getX(),cursor.getY()-1);
        break;
    case Qt::Key_Down:
        cursor.setPos(cursor.getX(),cursor.getY()+1);
        break;
    case Qt::Key_Right:
        cursor.setPos(cursor.getX()+1,cursor.getY());
        break;
    case Qt::Key_Left:
        cursor.setPos(cursor.getX()-1,cursor.getY());
        break;
    }
}

bool ImageWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched==this){
        switch(event->type()){
        case QEvent::Enter:

            break;

        case QEvent::Leave:

            break;

        case QEvent::MouseButtonPress:

            break;

        case QEvent::MouseButtonRelease:

            break;

        case QEvent::MouseMove:

            break;

        default:
            // just for minimisate warnings at the moment compilation
            break;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void ImageWidget::updateDarwingElements(){
    QPen pen_line;
    QPen pen_point;

    pen_point.setWidth(5);
    pen_line.setStyle(Qt::DashLine);

    pen_point.setColor("red");

    cursor.setPenLine(pen_line);
    cursor.setPenPoint(pen_point);
}
