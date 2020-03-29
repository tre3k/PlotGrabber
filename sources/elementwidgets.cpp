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

    about = new QLabel();
    about->setAlignment(Qt::AlignCenter);
    about->setTextInteractionFlags(Qt::TextBrowserInteraction);
    about->setOpenExternalLinks(true);

    layout->addWidget(open_button);
    layout->addWidget(sett_button);
    layout->addWidget(filename_label);
    layout->addStretch();
    layout->addWidget(about);


    connect(iface,SIGNAL(updated()),this,SLOT(updatePixmapsOnButtons()));
    connect(iface->main_window,SIGNAL(fileNameChanged(QString)),this,SLOT(setFileNameLabel(QString)));
}

void TopPanel::updatePixmapsOnButtons(){
    open_button->setPixmap(iface->getStyle()->buttonOpenPixmap());
    sett_button->setPixmap(iface->getStyle()->buttonSettingPixmap());
}

void TopPanel::paintEvent(QPaintEvent *e){
    about->setText("<b>PlotGrabber v1.0</b>"
                       "<br>GNU GPLv3 <a "
                       "href=\"https://github.com/tre3k/PlotGrabber\""
                       "style=\"color: "+iface->getStyle()->buttonBorderColor().name()+";\">GitHub</a>");

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

    /* darws cursor and borders */
    cursor = Darwings::Cursor(this);
    cursor.setPos(width()/2,height()/2);            // default
    top_right_border = Darwings::TopRightBorder(this);
    top_right_border.setPos(this->width()-10,10);
    bottom_left_border = Darwings::BottomLeftBorder(this);
    bottom_left_border.setPos(10,this->height()-10);

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

    //painter.drawPixmap(0,0,width()+100,height()+100,_pixmap);
    painter.drawPixmap(0,0,width(),height(),_pixmap);


    top_right_border.paint(&painter);
    bottom_left_border.paint(&painter);
    cursor.paint(&painter);

    QWidget::paintEvent(e);
}

void ImageWidget::mousePressEvent(QMouseEvent *e){
    w_mode = CURSOR_MODE;
    if(e->pos().x() >= top_right_border.getX() ||
       e->pos().y() <= top_right_border.getY()){
        w_mode = BORDER_RT_MODE;
    }
    if(e->pos().x() <= bottom_left_border.getX() ||
       e->pos().y() >= bottom_left_border.getY()){
        w_mode = BORDER_LB_MODE;
    }

    switch(w_mode){
    case CURSOR_MODE:
        cursor.setPos(e->localPos().x(), e->localPos().y());
        break;
    case BORDER_RT_MODE:
        top_right_border.setPos(e->localPos().x(), e->localPos().y());
        break;
    case BORDER_LB_MODE:
        bottom_left_border.setPos(e->localPos().x(), e->localPos().y());
        break;

    }
    update();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *e){
    switch(w_mode){
    case CURSOR_MODE:
        cursor.setPos(e->localPos().x(), e->localPos().y());
        break;
    case BORDER_RT_MODE:
        top_right_border.setPos(e->localPos().x(), e->localPos().y());
        break;
    case BORDER_LB_MODE:
        bottom_left_border.setPos(e->localPos().x(), e->localPos().y());
        break;
    }
    update();
}

void ImageWidget::keyPressEvent(QKeyEvent *event){  
    Darwings::Abstract *dw_a = nullptr;
    switch(w_mode){
    case CURSOR_MODE:
        dw_a = &cursor;
        break;
    case BORDER_RT_MODE:
        dw_a = &top_right_border;
        break;
    case BORDER_LB_MODE:
        dw_a = &bottom_left_border;
        break;
    default:
        return;
    }

    switch(event->key()){
    case Qt::Key_Up:
        dw_a->setPos(dw_a->getX(),dw_a->getY()-1);
        break;
    case Qt::Key_Down:
        dw_a->setPos(dw_a->getX(),dw_a->getY()+1);
        break;
    case Qt::Key_Right:
        dw_a->setPos(dw_a->getX()+1,dw_a->getY());
        break;
    case Qt::Key_Left:
        dw_a->setPos(dw_a->getX()-1,dw_a->getY());
        break;
    }
    update();
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
    /* for cursor */
    QPen cursor_pen_line;
    QPen cursor_pen_point;
    QPen cursor_pen_text;
    cursor_pen_point.setWidth(5);
    cursor_pen_line.setStyle(Qt::DashLine);
    cursor_pen_point.setColor("red");
    cursor.setPenLine(cursor_pen_line);
    cursor.setPenPoint(cursor_pen_point);
    cursor_pen_text.setColor("red");
    cursor.setPenText(cursor_pen_text);


    /* top_right */
    QPen border_pen;
    QBrush border_brush = QBrush(QColor("#80000000"));
    border_pen.setColor("black");
    border_pen.setWidth(1);
    top_right_border.setPenLine(border_pen);
    top_right_border.setBrush(border_brush);
    bottom_left_border.setPenLine(border_pen);
    bottom_left_border.setBrush(border_brush);


}
