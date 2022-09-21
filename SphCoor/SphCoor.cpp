//
// Created by kieru on 2022/9/14.
//

#include"SphCoor.h"
#include<cmath>

void SphCoor::calCart()
{
    double temp;
    z_ = r_ * cos(phi_);
    temp = r_ * sin(phi_);
    y_ = temp * sin(theta_);
    x_ = temp * cos(theta_);
}
