/*
 *  elementwidgets.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef ELEMENTWIDGETS_H
#define ELEMENTWIDGETS_H

#include <QFileInfo>
#include <QEvent>
#include <QMouseEvent>
#include <QDoubleSpinBox>

#include "basewidget.h"
#include "darwingelements.h"
#include "calculation.h"

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


/* ColorRingButton */
class ColorRingButton : public BaseWidget{
    Q_OBJECT
private:
    const int diameter = 25;
    bool _state = false;
    QPen _pen;
    QBrush _brush;
public:
    ColorRingButton(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
    void setBrush(QBrush brush){
        _brush = brush;
        update();
    }
    void setColorPen(QColor color){
        _pen.setColor(color);
        update();
    }
    bool getState(void){return _state;}
public slots:
    void setChecked(bool state){
        _state = state;
        if(state)
            _pen.setStyle(Qt::SolidLine);
        else
            _pen.setStyle(Qt::NoPen);
        update();
        emit stateChanged(state);
    }
protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void stateChanged(bool state);
};

/* ColorRingButtons */
class ColorRingButtons : public BaseWidget{
    Q_OBJECT
private:
    QVector<bool> states;
    QVector<ColorRingButton *> buttons;
    int _index = 0;
public:
     ColorRingButtons(If::Interface *_iface = nullptr, QWidget *parent = nullptr);

public slots:
     void buttonSelected(bool state){
         if(!state) return;
         int i = 0;
         for(bool s : states){
            if(s){
                buttons.at(i)->setChecked(false);
                states[i] = false;
            }
            i++;
         }
         i = 0;
         for(auto button : buttons){
            if(button->getState()){
                _index = i;
                states[i] = true;
                emit numChanged(_index);
                break;
            }
            i++;
         }
     }

     void setButtonSelect(int index){
        _index = index;
        int i = 0;
        for(auto button : buttons){
            states[i] = false;
            button->setChecked(false);
            if(i==_index){
                button->setChecked(true);
            }
            i++;
        }
        states[index] = true;
    }

    int getCurrentIndex(void){return _index;}
signals:
    void numChanged(int num);

};

/* TOGGLE BUTTON */
class ToggleButton : public BaseWidget{
    Q_OBJECT
    Q_PROPERTY(qreal cpos READ getCpos WRITE setCpos)
private:
    bool _state = false;
    qreal _circle_position = 0.5;       // from 0 - left, to 1.0 - right

    qreal getCpos(void){return _circle_position;}
    void setCpos(qreal cpos){_circle_position={cpos}; update();}

    QPropertyAnimation *p_animation;

    /* geometry */
    const int backgroud_width = 36;
    const int backgroud_height = 16;

    /* colors */
    QBrush _circle_brush;
    QPen _circle_pen;
    QBrush _back_brush;
    QPen _back_pen;

public:
    ToggleButton(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
    bool getState(void){return _state;}

public slots:
    void setState(bool state){
        _state = state;
        if(state){
            p_animation->setStartValue(0.0);
            p_animation->setEndValue(1.0);
        }else{
            p_animation->setStartValue(1.0);
            p_animation->setEndValue(0.0);
        }
        p_animation->start();
        emit stateChanged(state);
    }
signals:
    void stateChanged(bool state);

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);

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
    QLabel *about;
    void paintEvent(QPaintEvent *e);

public slots:
    void updatePixmapsOnButtons(void);
    void setFileNameLabel(QString filename){
        filename_label->setText("<h4>"+QFileInfo(filename).fileName()+"</h4>");
    }
};

/* INPUT NUMBER */
class InputNumber : public BaseWidget{
    Q_OBJECT
private:
    int _width = 75, _height = 25;
    QDoubleSpinBox *spin_box;
protected:
    void paintEvent(QPaintEvent *event);
public:
    InputNumber(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
    double getValue(void);
};

/* IMAGE WIDGET */
class ImageWidget : public BaseWidget{
    Q_OBJECT
private:
    QPixmap _pixmap;
    Darwings::Cursor cursor;
    Darwings::TopRightBorder top_right_border;
    Darwings::BottomLeftBorder bottom_left_border;

    InputNumber *input_min_x;
    InputNumber *input_max_x;
    InputNumber *input_min_y;
    InputNumber *input_max_y;

    enum WorkMode{CURSOR_MODE,BORDER_RT_MODE,BORDER_LB_MODE,ZOOM_MODE};
    WorkMode w_mode = CURSOR_MODE;

    Calc::Calculation *calculate;

public:
    ImageWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr);

public slots:
    void setImage(QString filename);
    void updateDarwingElements(void);
    void setMode(ImageWidget::WorkMode _w_mode){w_mode = _w_mode;}

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *event);

};


}


#endif
