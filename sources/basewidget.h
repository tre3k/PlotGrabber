/*
 *  basewidget.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef BASEWIDGET_H
#define BASEWIDGET_H


#include <QWidget>
#include <QToolTip>
#include <QVector>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QPropertyAnimation>

#include "interface.h"


namespace Widgets {
    class BaseWidget : public QWidget{
        Q_OBJECT
    public:
        BaseWidget(If::Interface *_iface = nullptr, QWidget *parent = nullptr);
        BaseWidget(QWidget *parent = nullptr) : QWidget(parent){}
        ~BaseWidget(void);

    protected:
        static If::Interface *iface;                // interface for communication


    public slots:
        void setInterface(If::Interface *_iface){iface = _iface;}

    };



}

#endif

