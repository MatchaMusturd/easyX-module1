//
// Created by CHH on 2023/10/25.
//

#ifndef EASYX_TEST1_TWOBALLSMOVE_H
#define EASYX_TEST1_TWOBALLSMOVE_H

#include <graphics.h>
#include <deque>
#include <ctime>
#include <iostream>

#include "Point.h"
#include "Showellipse.h"

class twoballsmove {
public:
    static Point backpoint;//两个球队列中弹出的球中心点
    static std::deque<Point> pointlist;
    int speed{};//小球运动速度
    float angle{};//角度(弧度制)
    bool ifmorethanhalfpie{};//角度是否超过半圆
    int radius{};//圆的半径
    static int speedchangetime, steptime;
    //每个速度持续的时间，每次移动的时间（睡眠的时间）
    bool iflbuttonup{};//左键是否抬起
    bool ballreturn{}, iflbuttondown{};
    //小球是否是通过达到终点而不是通过鼠标抬起返回

    twoballsmove();
//    ~twoballsmove();

    void showpoints(Point&);
    void getinitialspeed(float);
    //根据两点距离获取初速度
    void returnball();//小球返回
    void timerinner(float, const Point*);
    Point* backpointmove(Point*) const;
    //第一个参数是速度  第二个参数是传入的运动点  返回运动之后的运动点
    Point* backpointmove_(Point*, float) const;//小球返回用的返回点函数
private:

};


#endif //EASYX_TEST1_TWOBALLSMOVE_H
