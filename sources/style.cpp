/*
 *  style.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "style.h"

using namespace Styles;

void Style::update(){
    switch(base_style){
    case STYLE_DARK:
        top_panel_background = QColor("#323232");
        top_panel_border_color = QColor("#a2a2a2");

        button_close_pixmap = QPixmap(":/icons/close_button_dark.svg");
        button_setting_pixmap = QPixmap(":/icons/sett_button_dark.svg");
        button_open_pixmap = QPixmap(":/icons/open_button_dark.svg");
        button_accept_pixmap = QPixmap(":/icons/accept_button_dark.svg");

        palette.setColor(QPalette::WindowText,"#fcfcfc");
        palette.setColor(QPalette::Window,"#525252");

        break;

    case STYLE_LIGHT:
        top_panel_background = QColor("#fcfcfc");
        top_panel_border_color = QColor("#b2b2b2");

        button_close_pixmap = QPixmap(":/icons/close_button_light.svg");
        button_setting_pixmap = QPixmap(":/icons/sett_button_light.svg");
        button_open_pixmap = QPixmap(":/icons/open_button_light.svg");
        button_accept_pixmap = QPixmap(":/icons/accept_button_light.svg");

        palette.setColor(QPalette::WindowText,"#222222");
        palette.setColor(QPalette::Window,"#e7e7e7");

        break;
    }

    switch(second_style){
    case STYLE_GREEN:
        button_color_alpha = QColor("#004d9646");
        button_color = QColor("#ac4d9646");
        button_border_color = QColor("#ff4d9646");
        break;

    case STYLE_BLUE:
        button_color_alpha = QColor("#004d4696");
        button_color = QColor("#ac4d4696");
        button_border_color = QColor("#ff4d4696");
        break;

    case STYLE_RED:
        button_color_alpha = QColor("#0096464d");
        button_color = QColor("#ac96464d");
        button_border_color = QColor("#ff96464d");
        break;

    case STYLE_ORANGE:
        button_color_alpha = QColor("#00db7d32");
        button_color = QColor("#acdb7d32");
        button_border_color = QColor("#ffdb7d32");
        break;
    }

    button_close_pixmap = button_close_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_setting_pixmap = button_setting_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_open_pixmap = button_open_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_accept_pixmap = button_accept_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}
