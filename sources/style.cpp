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

        break;

    case STYLE_LIGHT:
        switch(second_style){
            case STYLE_GREEN:
            button_color_alpha = QColor("#004d9646");
            button_color = QColor("#ac4d9646");
            button_border_color = QColor("#ff4d9646");
            break;
        }

        break;
    }




}
