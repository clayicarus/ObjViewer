//
// Created by kieru on 2022/9/14.
//

#include "Tool.h"

unsigned int Tool::to24BitColor(unsigned char red, unsigned char green, unsigned char blue) {
    unsigned color(0);
    color |= red;
    color = color << 8;
    color |= green;
    color = color << 8;
    color |= blue;
    return color;
}
