/*
 *  darwingelements.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef DARWINGELEMENTS_H
#define DARWINGELEMENTS_H

#include "basewidget.h"

namespace Darwings {
/* elements darwing for Image Widget */

class Abstract{
protected:
    qreal _x,_y;            //reletive
    Widgets::BaseWidget *_wd;
    qreal _ax,_ay;          //absolute

    void update_absolute(){
        _ax = _x*_wd->width();
        _ay = _y*_wd->height();
    }

public:
    Abstract(Widgets::BaseWidget *wd = nullptr){_wd = wd;}
    void setPos(qreal x,qreal y){
        _x = x/(qreal)_wd->width();
        _y = y/(qreal)_wd->height();
        _wd->update();
    }
    // only for paintEvent
    virtual void paint(QPainter *p) = 0;
    qreal getX(void){return _x*_wd->width();}
    qreal getY(void){return _y*_wd->height();}
};

class Cursor : public Abstract{
private:
    QPen pen_line;
    QPen pen_point;
    QPen pen_text;

public:
    Cursor(Widgets::BaseWidget *wd = nullptr) : Abstract(wd) {pen_point.setWidth(3);}

    void paint(QPainter *p) override {
        paintd(p,_x,_y);
    }

    void paintd(QPainter *p, qreal text_val_x, qreal text_val_y) {
        update_absolute();
        p->setPen(pen_line);
        p->drawLine(_ax,0,_ax,_wd->height());
        p->drawLine(0,_ay,_wd->width(),_ay);
        p->setPen(pen_point);
        p->drawPoint(_ax,_ay);
        p->setPen(pen_text);
        p->drawText(_ax+2,_wd->height(),QString::number(text_val_x));
        p->drawText(0,_ay-2,QString::number(text_val_y));
    }
    void setPenPoint(QPen pen){pen_point = pen;}
    void setPenLine(QPen pen){pen_line = pen;}
    void setPenText(QPen pen){pen_text = pen;}
};


class Border : public Abstract{
protected:
    QPen pen_line;
    QBrush _brush;

public:
    Border(Widgets::BaseWidget *wd = nullptr) : Abstract(wd) {}
    void setPenLine(QPen pen){pen_line = pen;}
    void setBrush(QBrush brush){_brush = brush;}
    void _paint(QPainter *p){
        update_absolute();
        QPen rect_pen = QPen(Qt::NoPen);
        p->setPen(pen_line);
        p->drawLine(_ax,0,_ax,_wd->height());
        p->drawLine(0,_ay,_wd->width(),_ay);
    }
};

class TopRightBorder : public Border{
public:
    TopRightBorder(Widgets::BaseWidget *wd = nullptr) : Border(wd){}
    void paint(QPainter *p){
        update_absolute();
        QPen rect_pen = QPen(Qt::NoPen);
        p->setBrush(_brush);
        p->setPen(rect_pen);
        p->drawRect(0,0,_ax,_ay);
        p->drawRect(_ax,0,_wd->width()-_ax+1,_ay);
        p->drawRect(_ax,_ay,_wd->width()-_ax+1,_wd->height()-_ay+1);

        _paint(p);
    }
};

class BottomLeftBorder : public Border{
public:
    BottomLeftBorder(Widgets::BaseWidget *wd = nullptr) : Border(wd){}
    void paint(QPainter *p){
        update_absolute();
        QPen rect_pen = QPen(Qt::NoPen);
        p->setBrush(_brush);
        p->setPen(rect_pen);
        p->drawRect(0,0,_ax,_ay);
        p->drawRect(0,_ay,_ax,_wd->height()-_ay+1);
        p->drawRect(_ax,_ay,_wd->width()-_ax,_wd->height()-_ay+1);


        _paint(p);
    }
};

}

#endif // DARWINGELEMENTS_H

