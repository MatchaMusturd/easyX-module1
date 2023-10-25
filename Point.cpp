//
// Created by CHH on 2023/10/20.
//

#include <iostream>
#include "Point.h"

float Point::pi = float(acos(-1));
int Point::movepath = 100;//移动步长

Point::Point() {
    x = -1;
    y = -1;
//    iswall = false;
}

void Point::randompoint(const float width, const float height) {
    //从屏幕上获取随机点的坐标
    std::random_device r;
    std::mt19937 generator(r());
    std::uniform_real_distribution<float> widthdistribut(0,width);
    std::uniform_real_distribution<float> heightdistribut(0,height);
    x = widthdistribut(generator);
    y = heightdistribut(generator);
}

int Point::getrandomlength(const int a, const int b) {
    int length;
    std::random_device r;
    int max, min;
    max = std::max(a, b);
    min = std::min(a, b);
    std::mt19937 generator(r());
    std::uniform_int_distribution<int> lengthdistribution(min, max);
    length = lengthdistribution(generator);
//    std::cout<<"random length is "<<length<<std::endl;
    return length;
}

void Point::random_angle(){
    std::random_device r;
    std::mt19937 generator(r());
    std::uniform_real_distribution<float> angledistribution(0,2 * pi);
    randomangle = angledistribution(generator);
    if(randomangle > pi) randomangle -= pi;
}

Point Point::randomposition(const Point point) {
    //根据起始点获取随机终点
    Point returnpoint;
    std::random_device r;
    double x_, y_;
    int length = getrandomlength(20, 40);//获取20到40间的随机值
    random_angle();
    if(randomangle > pi){
        randomangle -= pi;
        x_ = -cos(randomangle) * length;
        y_ = -sin(randomangle) * length;
    }else{
        x_ = cos(randomangle) * length;
        y_ = sin(randomangle) * length;
    }
    returnpoint.x = point.x + float(x_);
    returnpoint.y = point.y + float(y_);
    return returnpoint;
}

float Point::getangle(const Point p1, const Point p2){
    //从p1出发到p2对于p1的角度
    float x_, y_;
    float x_y;
    float angle;
    x_ = p2.x - p1.x;
    y_ = p2.y - p1.y;
    x_y = float(y_) / float(x_);
    angle = std::atan(x_y);
    if(angle < 0) angle += pi;
    if((p2.x >= p1.x&&p2.y >= p1.y)
       ||(p2.x < p1.x&&p2.y >= p1.y)) {
        morethan = false;
    }
    else morethan = true;
    return angle;
}

void Point::getpoint(const Point point1, const Point mousepoint, const int length){
    //通过获取鼠标和上一个点的坐标来获取下一个点的坐标

    float returnpoint_x, returnpoint_y;
//    float angle_;
    moveangle = getangle(point1, mousepoint);
    //获取角度
//    angle_ = angle * arcpi;
    if(morethan){
//        angle_ += 180;
        returnpoint_x = - float(double(length) * cos(moveangle));
        returnpoint_y = - float(double(length) * sin(moveangle));
    }else{
        returnpoint_x = float(double(length) * cos(moveangle));
        returnpoint_y = float(double(length) * sin(moveangle));
    }
//    std::cout<<"angle_="<<angle_<<std::endl;
    x = point1.x + returnpoint_x;
    y = point1.y + returnpoint_y;
}


float Point::getlength(const Point p1, const Point p2) {
    float length;
    float x_, y_;

    x_ = fabsf(p1.x - p2.x);
    y_ = fabsf(p1.y - p2.y);
    x_ = powf(x_, 2);
    y_ = powf(y_, 2);
    length = sqrtf(x_ + y_);
    return length;
}

