/*
 *  settingdialog.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "settingdialog.h"

using namespace Dialogs;

Settings::Settings(If::Interface *iface, QWidget *parent) : QDialog(parent){
    this->setWindowTitle("Settings");
    connect(this,SIGNAL(Accepted()),iface,SLOT(update()));
    _iface = iface;

    auto layout = new QVBoxLayout();
    this->setLayout(layout);

    auto button_layout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignRight);
    auto close_button = new Widgets::RingCancelButton();
    connect(close_button,SIGNAL(release()),this,SLOT(close()));
    auto accept_button = new Widgets::RingAcceptButton();
    connect(accept_button,SIGNAL(release()),this,SLOT(Accept()));

    button_layout->setMargin(0);
    button_layout->setSpacing(0);
    button_layout->addWidget(accept_button);
    button_layout->addWidget(close_button);

    layout->addWidget(new QLabel("asdsadsa"));
    layout->addStretch();
    layout->addLayout(button_layout);
}


void Settings::Accept(){
    if(_iface->settings.light_dark){
        _iface->getStyle()->setBaseStyle(Styles::STYLE_LIGHT);
        _iface->settings.light_dark = false;
    }else{
        _iface->getStyle()->setBaseStyle(Styles::STYLE_DARK);
        _iface->settings.light_dark = true;
    }
    _iface->getStyle()->setSecondStyle(_iface->settings.second_style);

    emit Accepted();
    this->close();
}
