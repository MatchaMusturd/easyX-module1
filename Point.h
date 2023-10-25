//
// Created by CHH on 2023/10/20.
//

#ifndef EASYX_TEST1_POINT_H
#define EASYX_TEST1_POINT_H

#include <random>
#include <graphics.h>

class Point {
public:

    COLORREF rgb{};
    static float pi;
    static int movepath;
    float x, y;
    double moveangle{};
    bool morethan{};//鼠标点与小球连线与水平夹角是否大于180度
//    double returnangle{};

    Point();
//    bool iswall;
    void randompoint(float ,float);
    void random_angle();
    Point randomposition(Point);
    static int getrandomlength(int, int);//获取随机长度

    void getpoint(Point, Point, int);//获取小球下个位置
    static float getlength(Point, Point);
    float getangle(Point, Point);
    //通过两点获取两点连线与水平角度的弧度制
private:
    double randomangle{};
//    std::random_device r;
};


#endif //EASYX_TEST1_POINT_H
