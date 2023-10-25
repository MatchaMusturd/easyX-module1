//
// Created by CHH on 2023/10/21.
//

#include "Ellipse.h"

Ellipse::Ellipse() {

    std::random_device r;
    std::mt19937 generator(r());
    std::uniform_real_distribution<float> distribution(10,20);
    std::uniform_real_distribution<float> hdistribution(0,360);
    //色相随机值
    std::uniform_real_distribution<float> sdistribution(0.1, 1);
    //饱和度随机值
    std::uniform_real_distribution<float> ldistribution(0.3, 0.7);
    //亮度随机值

    hue = float(hdistribution(generator));
    saturation = sdistribution(generator);
    lightness = ldistribution(generator);
    rgb = HSLtoRGB(hue, saturation, lightness);
    half_x = distribution(generator);
    half_y = distribution(generator);
}


void Ellipse::topleftandbuttomright(const Point centerpoint) {
    topleft.x = centerpoint.x - half_x;
    topleft.y = centerpoint.y - half_y;
    buttomright.x = centerpoint.x + half_x;
    buttomright.y = centerpoint.y + half_y;
    centrepoint = centerpoint;
}



