//
// Created by CHH on 2023/10/25.
//

#include "Showellipse.h"

bool Showellipse::moveellipse = false;
int Showellipse::amountofvanishellipses = 0;

Showellipse::Showellipse() {
    ellipselist = new std::vector<cE>;
    ellipsepointlengthx = 50;//椭圆中心到圆心x方向上的距离
    ellipsepointlengthy = 50;//椭圆中心到圆心y方向上的距离
}

Showellipse::~Showellipse() {
    delete ellipselist;
}

void Showellipse::checkellipseifexists() {
    Point frontpoint = twoballsmove::pointlist.front();
    int length;
    Point center;
    for(iter = ellipselist->begin(); iter!=ellipselist->end(); ){
        length = Point::getrandomlength(50, 70);
        //椭圆移动步长取50~70随机值
        ellipsecenter = iter->centrepoint;
        center.getpoint(ellipsecenter, frontpoint, length);
        iter->topleftandbuttomright(center);//获取椭圆的左上和右下顶点

        if(twoballsmove::pointlist.size() > 1){
            ellipsepointlengthx = std::fmin(fabsf(iter->centrepoint.x - twoballsmove::pointlist.front().x),
                                            fabsf(iter->centrepoint.x - twoballsmove::pointlist.back().x));
            ellipsepointlengthy = std::fmin(fabsf(iter->centrepoint.y - twoballsmove::pointlist.front().y),
                                            fabsf(iter->centrepoint.y - twoballsmove::pointlist.back().y));
        }//圆心和椭圆中心的距离取最小值
        if(ellipsepointlengthx < iter->half_x
           ||ellipsepointlengthy < iter->half_y
           ||iter->centrepoint.x < 0
           ||iter->centrepoint.x > float(width)
           ||iter->centrepoint.y < 0
           ||iter->centrepoint.y > float(height)){
            iter = ellipselist->erase(iter);
            amountofvanishellipses++;
//            std::cout<<"erase ellipse"<<std::endl;
        }else iter++;
    }
    if(ellipselist->size() > 1){
        float halfx, halfy;
        bool iter3isdeleted = false;
        for(iter3 = ellipselist->begin(); iter3!=ellipselist->end(); ){
            if(iter3isdeleted) iter3isdeleted = false;
            for(iter2 = ellipselist->begin(); iter2!=iter3; iter2++){
                ellipselengthx = fabsf(iter2->centrepoint.x - iter3->centrepoint.x);
                ellipselengthy = fabsf(iter2->centrepoint.y - iter3->centrepoint.y);
                halfx = iter2->half_x + iter3->half_x;
                halfy = iter2->half_y + iter3->half_y;
                if(ellipselengthx < halfx&&ellipselengthy < halfy){
                    iter3 = ellipselist->erase(iter3);
                    amountofvanishellipses++;
                    iter3isdeleted = true;
                    break;
                }
            }
            if(ellipselist->size() < 2) break;
            else if(!iter3isdeleted) iter3++;
        }
    }
}

void Showellipse::ellipsesmove(struct Ellipse *e) {
    e->centrepoint.randompoint(float(width), float(height));
    //中心点设置随机坐标
    e->topleftandbuttomright(e->centrepoint);
    //获取椭圆左上和右下坐标
    for(iter = ellipselist->begin(); iter!=ellipselist->end(); iter++){
        clearellipse_(*iter);
    }//将上次队列中的所有椭圆从界面上清除代表移动到下一个位置
    ellipselist->push_back(*e);
    if(ellipselist->size() > 1){

        checkellipseifexists();//判断椭圆是否满足继续存在条件
    }
    for(iter = ellipselist->begin(); iter!=ellipselist->end(); iter++){
        drawellipse(*iter);
    }//将操作一次后的椭圆队列中的所有椭圆显示
}

//void Showellipse::clearellipse_2(cE& e){
//    setfillcolor(LIGHTGRAY);
//    solidellipse(int(e.topleft.x), int(e.topleft.y),
//                 int(e.buttomright.x), int(e.buttomright.y));
//}

void Showellipse::clearellipse_(cE& e){
    clearellipse(int(e.topleft.x), int(e.topleft.y),
                 int(e.buttomright.x), int(e.buttomright.y));
//    setbkcolor(LIGHTGRAY);
}

void Showellipse::drawellipse(cE& e){
    setfillcolor(e.rgb);
    solidellipse(int(e.topleft.x), int(e.topleft.y),
                 int(e.buttomright.x), int(e.buttomright.y));
}

void Showellipse::ellipsemovecment(const Point* p){

    Point point = *p;
    int speed = 1;
    int countime, every, endcount;
    float l_, circlellipsel1, maxlofellipse;
    double end_ = clock();
    int sleept = twoballsmove::steptime;
    int spct = twoballsmove::speedchangetime;
    int sleeptime, speedtime;//真正的步长时间和速度改变时间
    int sz;//取pointlist大小
    BeginBatchDraw();
    while(moveellipse){
        endcount = every;
        countime = int(clock() - end_);
        for(iter = ellipselist->begin(); iter!=ellipselist->end(); ){

            l_ = Point::getlength(iter->centrepoint, point);
            circlellipsel1 = Point::getlength(iter->centrepoint, twoballsmove::backpoint);
            maxlofellipse = fmaxf(iter->half_y, iter->half_x);
            if(ellipselist->size() < 2){
                moveellipse = false;
                break;
            }else if(l_ < maxlofellipse){

                clearellipse_(*iter);
//                clearellipse_2(*iter);
                iter = ellipselist->erase(iter);
                amountofvanishellipses++;
            }else if(circlellipsel1 < maxlofellipse){
                clearellipse_(*iter);
//                clearellipse_2(*iter);
                iter = ellipselist->erase(iter);
                amountofvanishellipses++;
            }else iter++;

            iter->moveangle = point.getangle(iter->centrepoint, point);
            iter->morethanhalf = point.morethan;

            clearellipse_(*iter);
//            clearellipse_2(*iter);

            *iter = draw_ellipse(*iter, speed);
            //每次20ms指定速度进行运动

        }
        sz = int(ellipselist->size());
        sleeptime = sz * sleept;
        speedtime = sz * spct;
        Sleep(sleeptime);
        FlushBatchDraw();
        every = countime / speedtime;
//            cout<<"speed is "<<speed<<endl;
        if(every - endcount == 1){
            speed += 1;
        }
    }

}

cE Showellipse::draw_ellipse(cE e, const int speed) {
    auto step = float(speed);
    float angle = e.moveangle;
    if(e.morethanhalf) step = -step;
    setfillcolor(e.rgb);
    clearellipse_(e);
    e.centrepoint.x += cosf(float(angle)) * step;
    e.centrepoint.y += sinf(float(angle)) * step;
    e.topleftandbuttomright(e.centrepoint);
    drawellipse(e);
    return e;
}

