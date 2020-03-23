/*
 *  darwingelements.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "basewidget.h"

namespace Darwings {
/* elements darwing for Image Widget */

class Abstract{
protected:
    qreal _x,_y;
    Widgets::BaseWidget *_wd;

public:
    Abstract(Widgets::BaseWidget *wd = nullptr){_wd = wd;}
    void setPos(qreal x,qreal y){
        _x = x;
        _y = y;
        _wd->update();
    }
    // only for paintEvent
    virtual void paint(QPainter *p) = 0;
    qreal getX(void){return _x;}
    qreal getY(void){return _y;}
};

class Cursor : public Abstract{
private:
    QPen pen_line;
    QPen pen_point;

public:
    Cursor(Widgets::BaseWidget *wd = nullptr) : Abstract(wd) {pen_point.setWidth(3);}

    void paint(QPainter *p) override {
        p->setPen(pen_line);
        p->drawLine(_x,0,_x,_wd->height());
        p->drawLine(0,_y,_wd->width(),_y);
        p->setPen(pen_point);
        p->drawPoint(_x,_y);
        p->drawText(_x+2,_wd->height(),QString::number(_x));
        p->drawText(0,_y-2,QString::number(_y));
    }
    void setPenPoint(QPen pen){pen_point = pen;}
    void setPenLine(QPen pen){pen_line = pen;}
};

class TopRightBorder : public Abstract{
private:
    QPen pen_line;
    QBrush _brush;
public:
    TopRightBorder(Widgets::BaseWidget *wd = nullptr) : Abstract(wd) {}
    void setPenLine(QPen pen){pen_line = pen;}
    void setBrush(QBrush brush){_brush = brush;}
    void paint(QPainter *p){
        p->setPen(pen_line);
        p->drawLine(_x,_y,_x,_wd->height());
        p->drawLine(0,_y,_x,_y);
    }


};

}
