//
// Created by CHH on 2023/10/25.
//

#ifndef EASYX_TEST1_SHOWELLIPSE_H
#define EASYX_TEST1_SHOWELLIPSE_H

#include "Ellipse.h"
#include "twoballsmove.h"
#define cE class Ellipse

class Showellipse {
public:

    std::vector<cE> *ellipselist;

    float ellipsepointlengthx, ellipsepointlengthy;
    //各个椭圆圆心与小球圆心的距离
    int width{}, height{};//窗体高度和宽度
    std::vector<cE>::iterator iter, iter2, iter3;
    float ellipselengthx{}, ellipselengthy{};
    //各个椭圆之间横纵坐标的距离
    Point ellipsecenter;//椭圆中心
    static bool moveellipse;
    //通过判断鼠标是否按下来判断椭圆是否应该移动
    static int amountofvanishellipses;
//    bool returnellipse;

    Showellipse();
    ~Showellipse();
    void checkellipseifexists();
    void ellipsesmove(cE*);
    static void clearellipse_(cE&);
//    static void clearellipse_2(cE&);
    static void drawellipse(cE&);
    void ellipsemovecment(const Point*);
    static cE draw_ellipse(cE, int);
};


#endif //EASYX_TEST1_SHOWELLIPSE_H
