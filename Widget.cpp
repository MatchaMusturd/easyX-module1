//
// Created by CHH on 2023/10/20.
//

#include "Widget.h"

using namespace std;


Widget::Widget() {
    hwnd = initgraph(1720,900);
    se = new Showellipse;
    se->width = getwidth();
    se->height = getheight();
    p = new Point;
    amountaftercilcked = new std::vector<int>;//记录每次点击之后椭圆数量
    se->ellipselist = new std::vector<class Ellipse>;//椭圆队列
    countpoints = 0;//点击次数
    tbm = new twoballsmove;
}

Widget::~Widget() {

    delete se;
    delete p;
    delete amountaftercilcked;
}

void Widget::ifclickdownup(const Point* p_){
    int s;
    Point point = *p_;
    //每次调用本函数都初始化一个point点
    //为传给showpoints函数使每个点颜色不同
    if(!Showellipse::moveellipse){
        auto *e = new cE;
        se->ellipsesmove(e);//对所有椭圆进行操作
        s = int(se->ellipselist->size());
        amountaftercilcked->push_back(s);
        cout<<"clicked "<<countpoints<<" times"<<endl;
        cout<<"amount of ellipes is "<<s<<endl;
        cout<<"the amount of all vanished ellipses is "
                <<Showellipse::amountofvanishellipses<<endl;
    }
    countpoints++;
    if(countpoints % 2==1) point.rgb = WHITE;
    else point.rgb = BLACK;
    tbm->showpoints(point);//展示点
}

void Widget::timer(const int t, const Point* p_){

    double start, end, total;
    start = clock();
    while(true){
        end = clock();
        total = end - start;
        if(total > t) break;

    }
    if(tbm->iflbuttonup){
        //如果在400ms中鼠标按键抬起事件触发直接结束
        return;
    }else if(twoballsmove::pointlist.size() > 1){
        //如果未触发则判定为一直按下
        float length;
        ifclickdownup(p_);
        twoballsmove::backpoint = twoballsmove::pointlist.back();
        length = Point::getlength(*p_, twoballsmove::backpoint);
        if(length > float(Point::movepath)){
            //如果鼠标距离大于两球间距可以按照鼠标按下跑球
            //否则正常移动
            Showellipse::moveellipse = true;
            auto answer = async(&Showellipse::ellipsemovecment, se, p_);
            //在子线程上再开一个子线程用于跑椭圆
//            se->ellipsemovecment(p_);
            tbm->timerinner(length, p_);

        }
    }
}

void Widget::showidget() {//主体函数

    bool ifjumpoutloop = true;
    double start, end;
    future<void> answer;
    auto *m = new MOUSEMSG;
    auto *point = new POINT;

    setbkcolor(LIGHTGRAY);
    cleardevice();

    //将额外线程计时器打包
    while(ifjumpoutloop){
        GetCursorPos(point);//获取鼠标坐标
        ScreenToClient(hwnd, point);//将鼠标坐标转至窗体下
        *m = GetMouseMsg();
        p->x = float(point->x);
        p->y = float(point->y);
//        if(ifmousemeg){//小球返回时接受鼠标消息模块锁死
            switch (m->uMsg) {
                case WM_LBUTTONDOWN:
                    if(tbm->iflbuttondown){
                        cleardevice();
                        tbm->iflbuttonup = false;
                        start = clock();
                        answer = async(launch::async, &Widget::timer, this, 150, p);
//                        answer.get();
                        //开启异步线程
                    }
                    break;
                case WM_LBUTTONUP:
                    tbm->iflbuttonup = true;
                    end = clock();
                    last = end - start;
//                    cout<<"last is "<<last<<endl;
                    if(last < 150||
                       (last > 150&&twoballsmove::pointlist.size() < 2)) ifclickdownup(p);
                    else if(last > 200
                            &&twoballsmove::pointlist.size() > 1
                            &&!tbm->ballreturn){
                        Showellipse::moveellipse = false;
                        tbm->returnball();
                        tbm->ballreturn = true;
//                    cout<<"clicked "<<last<<" ms"<<endl;
                    }
                    break;
                case WM_MBUTTONUP:
                    for(int i = 0; i < amountaftercilcked->size(); i++){
                        std::cout<<i + 1<<" times amount of ellipes is "
                                 <<amountaftercilcked->at(i)<<std::endl;
                    }
                    std::cout<<"Quit"<<std::endl;
                    ifjumpoutloop = false;
                    break;

            }
//        }

    }
    _getch();
    closegraph();
}

