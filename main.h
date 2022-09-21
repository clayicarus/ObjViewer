//
// Created by kieru on 2022/9/14.
//

#ifndef OBJVIEWER_MAIN_H
#define OBJVIEWER_MAIN_H

#include<vector>
#include<gl/freeglut.h>
#include<array>
#include"SphCoor/SphCoor.h"
#include"Tool.h"
#include <ctime>
enum Axis{
    X, Y, Z
};

static SphCoor cam_poz(4, Tool::toRad(90), Tool::toRad(30));

static const size_t LEN = 50;
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const char TITLE[LEN] = "OBJViewer";

static const GLfloat LINE_WIDTH = 1.5;
static const unsigned char BG_RED = 213;
static const unsigned char BG_GREEN = 215;
static const unsigned char BG_BLUE = 216;
static const GLfloat BG_ALPHA = 1;

static unsigned int fps_adapt = 10;
static double fps_lock = 60;

void reshape(GLint w, GLint h);
void init();
void display();
void mouse(GLint btn, GLint state, GLint x, GLint y);
void keyboard(unsigned char, int, int);
void specialKey(int key, int x, int y);
void enableSmooth();
void drawAxis();
void idle();

#endif //OBJVIEWER_MAIN_H
