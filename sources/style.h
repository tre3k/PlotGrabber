/*
 *  style.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef STYLES_H
#define STYLES_H

#include <QPalette>
#include <QPainter>

#define C_DARK_COLOR "#535353"
#define C_LIGHT_COLOR "#fcfcfc"
#define C_LIGHT_TEXT "#212121"
#define C_DARK_TEXT "#ececec"

namespace Styles{
// base styles
enum BaseStyle{
    STYLE_DARK,STYLE_LIGHT
};

// second styles
enum SecondStyle{
    STYLE_BLUE,STYLE_GREEN,STYLE_RED,STLYE_ORANGE
};

class Style{
private:
    BaseStyle base_style {STYLE_LIGHT};             //default values
    SecondStyle second_style {STYLE_BLUE};

    int button_border = 2;
    QColor button_border_color;
    QColor button_color;
    QColor button_color_alpha;


public:
    Style(BaseStyle _base_style,SecondStyle _second_style): base_style{_base_style},second_style {_second_style}{}
    Style(SecondStyle _second_style): second_style {_second_style}{}
    Style(Style& _style): base_style {_style.baseStyle()}, second_style {_style.seconStyle()}{}
    Style& operator=(Style _style){
        base_style = _style.baseStyle();
        second_style = _style.seconStyle();
        return *this;
    }
    bool operator==(Style _style){
        if(_style.baseStyle() == base_style && _style.seconStyle() == second_style){
            return true;
        }else{
            return false;
        }
        return false;
    }
    Style(void){}

    BaseStyle baseStyle(void){return base_style;}
    SecondStyle seconStyle(void){return second_style;}

    void update(void);

public:
    QColor buttonColor(void){return button_color;}
    QColor buttonColorAlpha(void){return button_color_alpha;}
    QColor buttonBorderColor(void){return button_border_color;}
    int buttonBorder(void){return button_border;}

};

}


#endif
