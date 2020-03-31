/*
 *  calculation.cpp
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#include "calculation.h"

using namespace Calc;

Calculation::Calculation(Darwings::Cursor *cursor){
    _cursor = cursor;
}

void Calculation::setBorders(Darwings::TopRightBorder *top_right_border, Darwings::BottomLeftBorder *bottom_left_border){
    _t_r_b = top_right_border;
    _b_l_b = bottom_left_border;
}

void Calculation::setBordersValues(double x0, double x1, double y0, double y1){
    _x0 = x0; _x1 = x1; _y0 = y0; _y1 = y1;
    _b_x1 = _t_r_b->getX(); _b_y0 = _t_r_b->getY();
    _b_x0 = _b_l_b->getX(); _b_y1 = _b_l_b->getY();

}

double Calculation::getValX(){
    const double cd = (_x1-_x0)/(_b_x1-_b_x0);
    return _cursor->getX()*cd-_b_x0*cd+_x0;
}

double Calculation::getValY(){
    const double cd = (_y1-_y0)/(_b_y1-_b_y0);
    return _y0-_cursor->getY()*cd+_b_y1*cd;
}
