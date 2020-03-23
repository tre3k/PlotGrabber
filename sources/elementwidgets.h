/*
 *  elementwidgets.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef ELEMENTWIDGETS_H
#define ELEMENTWIDGETS_H

#include "basewidget.h"

namespace Widgets {

/* RING BUTTON */
class RingButton : public BaseWidget{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor)
public:
    RingButton(If::Interface *_iface = nullptr,QWidget *parent = nullptr);
    QColor getColor(void){return _brush.color();}
    void setColor(QColor b){
        _brush = QBrush(b);
        this->repaint();
    }

private:
    QLabel *label;
    QPen _pen;
    QBrush _brush;

protected:
    QPropertyAnimation *p_animation;

    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);

    void mouseEnter(QColor from,QColor to){
        p_animation->setStartValue(from);
        p_animation->setEndValue(to);
        p_animation->start();
    }

signals:
    void clicked(void);
    void release(void);

public slots:
    void setPixmap(QPixmap pixmap){
        label->setPixmap(pixmap);
        update();
    }
};

class RingCancelButton : public RingButton{
    Q_OBJECT
public:
    RingCancelButton(If::Interface *_iface = nullptr, QWidget *parent = nullptr)
    : RingButton(_iface, parent){
        reloadPixmap();
        connect(iface,SIGNAL(updated()),this,SLOT(reloadPixmap()));
    }
public slots:
    void reloadPixmap(void){
        this->setPixmap(iface->getStyle()->buttonColosePixmap());
    }
};

class RingAcceptButton : public RingButton{
    Q_OBJECT
public:
    RingAcceptButton(If::Interface *_iface = nullptr, QWidget *parent = nullptr)
    : RingButton(_iface, parent){
        reloadPixmap();
        connect(iface,SIGNAL(updated()),this,SLOT(reloadPixmap()));
    }
public slots:
    void reloadPixmap(void){
        this->setPixmap(iface->getStyle()->buttonAcceptPixmap());
    }
};


/* TOGGLE BUTTON */
class ToggleButton : public BaseWidget{

};


/* TOP PANEL */
class TopPanel : public BaseWidget{
    Q_OBJECT
public:
    TopPanel(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
private:
    RingButton *open_button;
    RingButton *sett_button;
    QLabel *filename_label;
    void paintEvent(QPaintEvent *e);

public slots:
    void updatePixmapsOnButtons(void);
    void setFileNameLabel(QString filename){
        filename_label->setText("<h4>"+filename+"</h4>");
    }
};

}


#endif
