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
        top_panel_border_color = QColor("#626262");

        button_close_pixmap = QPixmap(":/icons/close_button_dark.svg");
        button_setting_pixmap = QPixmap(":/icons/sett_button_dark.svg");
        button_open_pixmap = QPixmap(":/icons/open_button_dark.svg");
        button_accept_pixmap = QPixmap(":/icons/accept_button_dark.svg");

        front_color = QColor("#ececec");
        back_color = QColor("#424242");

        break;

    case STYLE_LIGHT:
        top_panel_background = QColor("#fcfcfc");
        top_panel_border_color = QColor("#b2b2b2");

        button_close_pixmap = QPixmap(":/icons/close_button_light.svg");
        button_setting_pixmap = QPixmap(":/icons/sett_button_light.svg");
        button_open_pixmap = QPixmap(":/icons/open_button_light.svg");
        button_accept_pixmap = QPixmap(":/icons/accept_button_light.svg");

        front_color = QColor("#323232");
        back_color = QColor("#e7e7e7");

        break;
    }
    /* resize pixmaps */
    button_close_pixmap = button_close_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_setting_pixmap = button_setting_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_open_pixmap = button_open_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    button_accept_pixmap = button_accept_pixmap.scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    /* set second style */
    button_color = secondStylesColors.at(second_style);
    button_color_alpha = button_color;
    button_border_color = button_color;
    button_color.setAlpha(0xac);                            // Alpha
    button_color_alpha.setAlpha(0x00);                      // Alpha start Animation for button

    /* set Palette */
    palette.setColor(QPalette::WindowText,front_color);
    palette.setColor(QPalette::Window,back_color);
    palette.setColor(QPalette::Link,second_style);
    palette.setColor(QPalette::LinkVisited,second_style);
}
