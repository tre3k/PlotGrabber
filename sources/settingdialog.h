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

        Widgets::ToggleButton *toggle_night_mode;
    public:
        Settings(If::Interface *iface = nullptr,QWidget *parent = nullptr);

    public slots:
        void Accept(void);
        void SwitchNightMode(bool mode);
        void ChangeColor(int second_style){
            _iface->getStyle()->setSecondStyle((Styles::SecondStyle)second_style);
            emit Accepted();
        }
    signals:
        void Accepted(void);
    };
}
