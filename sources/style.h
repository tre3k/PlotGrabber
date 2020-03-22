/*
 *  style.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

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
public:
    Style(BaseStyle _base_style,SecondStyle _second_style): base_style{_base_style},second_style {_second_style}{}
    Style(void){}
};

}
