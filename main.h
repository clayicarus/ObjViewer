//
// Created by kieru on 2022/9/14.
//

#ifndef OBJVIEWER_MAIN_H
#define OBJVIEWER_MAIN_H

#include<vector>
#include<gl/freeglut.h>
#include<array>
#include"SphCoor/SphCoor.h"
#include"Utility.h"
#include <ctime>
#include"Object/Object.h"

static SphCoor cam(4, Utility::toRad(90), Utility::toRad(30));

static constexpr size_t LEN = 50;
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const char TITLE[LEN] = "OBJViewer";

static const GLfloat LINE_WIDTH = 1.5;
// 213, 215, 216
static const unsigned char BG_RED = 0;
static const unsigned char BG_GREEN = 0;
static const unsigned char BG_BLUE = 0;
static const GLfloat BG_ALPHA = 1;

static unsigned int fps_adapt = 10;
static double fps_lock = 50;

void reshape(GLint w, GLint h);
void init();
void display();
void mouse(GLint btn, GLint state, GLint x, GLint y);
void keyboard(unsigned char, int, int);
void specialKey(int key, int x, int y);
void enableSmooth();
void drawAxis();
void idle();
void light();

#endif //OBJVIEWER_MAIN_H
