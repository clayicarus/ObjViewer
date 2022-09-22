//
// Created by kieru on 2022/9/14.
//

#ifndef OBJIMPORT_TOOL_H
#define OBJIMPORT_TOOL_H

#include<cmath>
#include<gl/freeglut.h>
class Utility {
public:
    static GLfloat toRad(GLfloat angle) { return angle * M_PI / 180.; }
    static GLfloat toGL_RGB(GLfloat color) { return color / 255.; }
    static unsigned int to24BitColor(unsigned char red, unsigned char green, unsigned char blue);
};


#endif //OBJIMPORT_TOOL_H
