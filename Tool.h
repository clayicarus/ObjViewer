//
// Created by kieru on 2022/9/14.
//

#ifndef OBJIMPORT_TOOL_H
#define OBJIMPORT_TOOL_H

#include<cmath>
class Tool {
public:
    static double toRad(double angle) { return angle * M_PI / 180.; }
    static double toGL_RGB(double color) { return color / 255.; }
    static unsigned int to24BitColor(unsigned char red, unsigned char green, unsigned char blue);
};


#endif //OBJIMPORT_TOOL_H
