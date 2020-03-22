/*
 *  basewidget.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QWidget>
#include <QVector>

namespace Widgets {
    class BaseWidget : public QWidget{
        Q_OBJECT
    public:
        BaseWidget(QWidget *parent = nullptr);
        ~BaseWidget(void);
    };
}
