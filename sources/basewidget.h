/*
 *  basewidget.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QPropertyAnimation>

#include "interface.h"

#include <QDebug>

namespace Widgets {

    //static If::Interface BaseWidget::_iface;

    class BaseWidget : public QWidget{
        Q_OBJECT
    public:
        BaseWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
        ~BaseWidget(void);

    protected:
        static If::Interface *iface;                // interface for communication


    public slots:
        void setInterface(If::Interface *_iface){iface = _iface;}

    };


    /* TOP PANEL */
    class TopPanel : public BaseWidget{
        Q_OBJECT
    public:
        TopPanel(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
    private:
        void paintEvent(QPaintEvent *e);
    };

    /* IMAGE WIDGET */
    class ImageWidget : public BaseWidget{
        Q_OBJECT
    public:
        ImageWidget(If::Interface *_iface = nullptr,QWidget *parent = nullptr);
    };

    /* RING BUTTON */
    class RingButton : public BaseWidget{
        Q_OBJECT
        Q_PROPERTY(QColor color READ getColor WRITE setColor)
    public:
        RingButton(If::Interface *_iface = nullptr,QWidget *parent = nullptr);
        QColor getColor(void){return _brush.color();}
        void setColor(QColor b){
            _brush = QBrush(b);
            qDebug() << "brush: "<< _brush;
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

    };

}



