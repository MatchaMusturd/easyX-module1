//
// Created by CHH on 2023/10/21.
//

#ifndef EASYX_TEST1_ELLIPSE_H
#define EASYX_TEST1_ELLIPSE_H

#include <windef.h>
#include <graphics.h>
#include <cmath>

#include "Point.h"



class Ellipse {
public:
    //椭圆左上角点和右下角点
    float half_x, half_y;
    COLORREF rgb;
    Point centrepoint;
    Point topleft, buttomright;
    float moveangle{};
    bool morethanhalf{};

    Ellipse();

//    ~Ellipse();

    void topleftandbuttomright(Point);


private:
    float hue, saturation, lightness;

};


#endif //EASYX_TEST1_ELLIPSE_H
