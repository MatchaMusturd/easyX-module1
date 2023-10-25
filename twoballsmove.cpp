//
// Created by CHH on 2023/10/25.
//

#include "twoballsmove.h"

using namespace std;

std::deque<Point> twoballsmove::pointlist;
Point twoballsmove::backpoint ;
int twoballsmove::speedchangetime = 200;
int twoballsmove::steptime = 20;

twoballsmove::twoballsmove() {
//    pointlist = new std::deque<Point>;//两个点的队列
//    speedchangetime = 200;//200ms
//    steptime = 20;//20ms
    radius = 5;//圆半径
    ballreturn = false;//是否可以接受鼠标消息
    iflbuttondown = true;//鼠标按下消息是否可以接受
}

//twoballsmove::~twoballsmove() {
////    delete pointlist;
//}

void twoballsmove::showpoints(Point& p_) {

    if(pointlist.empty()) pointlist.push_back(p_);
    else if(pointlist.size() < 2){
        p_.getpoint(pointlist.front(), p_, Point::movepath);
        pointlist.push_back(p_);
    }else if(pointlist.size() < 3){
        clearcircle(int(pointlist.front().x), int(pointlist.front().y), radius );
        p_.getpoint(pointlist.back(), p_, Point::movepath);
        pointlist.pop_front();
        pointlist.push_back(p_);
    }

    ifmorethanhalfpie = p_.morethan;
    angle = float(p_.moveangle);
//    cout<<"angle is "<<angle<<endl;
    Point front, back;
    front = pointlist.front();
    back = pointlist.back();
    BeginBatchDraw();
    setfillcolor(front.rgb);
    solidcircle(int(front.x), int(front.y), radius);
    setfillcolor(back.rgb);
    solidcircle(int(back.x), int(back.y), radius);
    FlushBatchDraw();
}

void twoballsmove::getinitialspeed(const float l){
    int ratio = speedchangetime / steptime;
    ratio /= 2;
    ratio += 1;
    //在速度固定时间内可以进行单次移动的次数
    int s = 1;//speed
    int oncestep = ratio;//在一定速度下步长
    while (float(oncestep) < l){
        s++;
        oncestep += s * ratio;
    }
    speed = s;
}

void twoballsmove::returnball(){
    Showellipse::moveellipse = false;
    int mv = Point::movepath;
    //两个球最终距离
    Point frontpoint = pointlist.front();
    float length = Point::getlength(backpoint, frontpoint);
    int l = int(length) - mv;//小球返回需要移动的直线长度
    double start, end, total;
    int every200ms, count200ms;
    Point front = pointlist.front();
    float returnangle = backpoint.getangle( backpoint, front);
    BeginBatchDraw();
    start = clock();
    while(l > 20){
        count200ms = every200ms;
        end = clock();
        total = end - start;
//        cout<<"l="<<l<<endl;
        backpoint = *backpointmove_(&backpoint, returnangle);
        Sleep(steptime);
        FlushBatchDraw();
        length = Point::getlength(backpoint, frontpoint);
        l = int(length) - mv;
        if(l < 10){
            cout<<"length is less than 10"<<endl;
            break;
        }
        every200ms = int(total) / speedchangetime;
        if(every200ms - count200ms == 1)
            speed += 1;
    }
    pointlist.pop_back();
    pointlist.push_back(backpoint);

}

void twoballsmove::timerinner(const float length, const Point *p_){
    int countime, every, endcount;
    double end_ = clock();
    float l = length;
    iflbuttondown = false;
    ballreturn = false;
    clearcircle(int(backpoint.x), int(backpoint.y), radius);
    getinitialspeed(length);
//    cout<<"initial speed is "<<speed<<endl;
    BeginBatchDraw();
    while(!iflbuttonup){
        endcount = every;

        countime = int(clock() - end_);
        l = Point::getlength(*p_, backpoint);
//            cout<<"length is "<<length<<endl;
        if(l < 10&&!iflbuttonup&&!ballreturn){
            ballreturn = true;
            cout<<"length less than 20"<<endl;
            returnball();
            break;
        }
        backpoint = *backpointmove(&backpoint);
        //每次20ms指定速度进行运动
        Sleep(steptime);
        FlushBatchDraw();
        every = countime / speedchangetime;
//            cout<<"speed is "<<speed<<endl;
        if((every - endcount == 1)&&speed > 1){
            speed -= 1;
        }
    }
    iflbuttondown = true;
}

Point* twoballsmove::backpointmove(Point* bp) const{
    auto step = float(speed);
    if(ifmorethanhalfpie) step = - step;
    setfillcolor(bp->rgb);
    clearcircle(int(bp->x), int(bp->y), radius + 3);
    bp->x += cosf(float(angle)) * step;
    bp->y += sinf(float(angle)) * step;
    solidcircle(int(bp->x), int(bp->y), radius);
    return bp;
}

Point *twoballsmove::backpointmove_(Point * bp,const float returnangle) const {
    auto step = float(speed);
    if(bp->morethan) step = - step;
    setfillcolor(bp->rgb);
    clearcircle(int(bp->x), int(bp->y), radius + 3);
    bp->x += cosf(float(returnangle)) * step;
    bp->y += sinf(float(returnangle)) * step;
    solidcircle(int(bp->x), int(bp->y), radius);
    return bp;
}

