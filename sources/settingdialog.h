/*
 *  settingdialog.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include <QDialog>

#include "interface.h"
#include "basewidget.h"
#include "elementwidgets.h"

namespace Dialogs {
    class Settings : public QDialog{
        Q_OBJECT
    private:
        If::Interface *_iface;
    public:
        Settings(If::Interface *iface = nullptr,QWidget *parent = nullptr);

    public slots:
        void Accept(void);
    signals:
        void Accepted(void);
    };
}
