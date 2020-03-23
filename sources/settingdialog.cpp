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

    auto night_mode_layout = new QHBoxLayout();
    toggle_night_mode = new Widgets::ToggleButton();
    connect(toggle_night_mode,SIGNAL(stateChanged(bool)),this,SLOT(SwitchNightMode(bool)));
    night_mode_layout->addWidget(new QLabel("Night mode: "));
    night_mode_layout->addStretch();
    night_mode_layout->addWidget(toggle_night_mode);

    auto color_buttons = new Widgets::ColorRingButtons();
    connect(color_buttons,SIGNAL(numChanged(int)),this,SLOT(ChangeColor(int)));
    auto color_button_layout = new QHBoxLayout();
    color_button_layout->addWidget(new QLabel("Interface color: "));
    color_button_layout->addStretch();
    color_button_layout->addWidget(color_buttons);

    layout->addLayout(night_mode_layout);
    layout->addLayout(color_button_layout);
    layout->addStretch();
    layout->addLayout(button_layout);
}

void Settings::SwitchNightMode(bool mode){
    _iface->settings.light_dark = !mode;
    if(_iface->settings.light_dark){
        _iface->getStyle()->setBaseStyle(Styles::STYLE_LIGHT);
    }else{
        _iface->getStyle()->setBaseStyle(Styles::STYLE_DARK);
    }

    emit Accepted();
}


void Settings::Accept(){

    emit Accepted();
    this->close();
}
