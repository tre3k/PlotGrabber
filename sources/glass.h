/*
 *  glass.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>

namespace Effects {

class Glass : public QWidget{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ getOpacity WRITE setOpacity)
private:
    QWidget *_parent;
    qreal _opacity = 0.0;
    QPropertyAnimation *p_animation;

    int _duration = 400;

public:
    Glass(QWidget *parent = nullptr);
    void setOpacity(qreal opacity){
        _opacity = opacity;
        update();
    }
    qreal getOpacity(void){
        return _opacity;
    }
    void setDuration(int duration){
        _duration = duration;
        p_animation->setDuration(duration);
    }

protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void startShow();
    void endShow();
    void theEnd(){
        disconnect(p_animation,SIGNAL(finished()),this,SLOT(theEnd()));
        setVisible(false);
    }
};

}
