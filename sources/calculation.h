/*
 *  calculation.h
 *  Under license GNU GPLv3
 *  Autor: Kirill Pshenichnyi (c) 2020
 *
 */

#ifndef CALCULATION_H
#define CALCULATION_H

#include "basewidget.h"
#include "darwingelements.h"

namespace Calc{

class Calculation{
private:
    double _x0,_x1,_y0,_y1;
    double _b_x0,_b_x1,_b_y0,_b_y1;
    Darwings::Cursor *_cursor;
    Darwings::TopRightBorder *_t_r_b;
    Darwings::BottomLeftBorder *_b_l_b;

public:
    Calculation(Darwings::Cursor *cursor = nullptr);

    void setBorders(Darwings::TopRightBorder *top_right_border,
                    Darwings::BottomLeftBorder *bottom_left_border);
    void setBordersValues(double x0,double x1,double y0, double y1);

    double getValX(void);
    double getValY(void);
};


}


#endif // CALCULATION_H
