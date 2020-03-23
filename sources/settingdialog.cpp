/*
 *  settingdialog.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "settingdialog.h"

using namespace Dialogs;

Settings::Settings(If::Interface *iface, QWidget *parent) : QDialog(parent){
    auto layout = new QVBoxLayout();
    this->setLayout(layout);

    auto button_layout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignRight);
    auto close_button = new Widgets::RingCancelButton();
    connect(close_button,SIGNAL(release()),this,SLOT(close()));
    button_layout->addWidget(close_button);

    layout->addWidget(new QLabel("asdsadsa"));
    layout->addStretch();
    layout->addLayout(button_layout);


}