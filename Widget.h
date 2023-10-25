//
// Created by CHH on 2023/10/20.
//

#ifndef EASYX_TEST1_WIDGET_H
#define EASYX_TEST1_WIDGET_H


#include <cmath>
#include <string>
#include <conio.h>
#include <list>
#include<functional>
#include<future>
#include <functional>
#include <thread>

#include "Point.h"
#include "twoballsmove.h"
#include "Showellipse.h"

#define cE class Ellipse

class Widget {
public:
    Widget();
    ~Widget();
    void showidget();

private:
    twoballsmove *tbm;
    Point *p;//主函数鼠标坐标
    Showellipse *se;

    double last{};//点击持续时间
    int countpoints;//点击鼠标次数
    std::vector<int> *amountaftercilcked;
    HWND hwnd{};

    void ifclickdownup(const Point*);
    void timer(int,const Point*);//计时器

};


#endif //EASYX_TEST1_WIDGET_H
