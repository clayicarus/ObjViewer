#include <iostream>
#include <GL/freeglut.h>
#include "main.h"
#include "Tool.h"
#include "Object/Object.h"
#include <array>
#include <ctime>
#include<iomanip>
#include<vector>
#include<memory>
using namespace std;

static vector<weak_ptr<Object>> objs;

int main(int argc, char *argv[])
{
    string dir(argv[0]);
    dir = dir.substr(0, dir.rfind('\\')) + "\\..\\objdata\\gaoda.obj";
    if(argc == 2){
        dir = argv[1];
    }
    shared_ptr<Object> sp_obj = make_shared<Object>(dir);
    sp_obj->faceColor() = Tool::to24BitColor(65, 65, 65);
    objs.push_back(weak_ptr<Object>(sp_obj));
    cam_poz.r() = sp_obj->modelSize() * 3;

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(TITLE);

    init();
    light();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMainLoop();

    return 0;
}

void light()
{
    array<GLfloat, 4> ambient = {1, 1, 1, 1};
    array<GLfloat, 4> diffuse = {1, 1, 1, .5};
    array<GLfloat, 4> specular = {1, 1, 1, .5};
    array<GLfloat, 4> poz = {100, 100, 100, 0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());

    glLightfv(GL_LIGHT0, GL_POSITION, poz.data());
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init()
{
    enableSmooth();
    glEnable(GL_DEPTH_TEST);
    glClearColor(Tool::toGL_RGB(BG_RED),
                 Tool::toGL_RGB(BG_GREEN),
                 Tool::toGL_RGB(BG_BLUE),
                 BG_ALPHA);
}

void enableSmooth()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cam_poz.calCart();
    glLoadIdentity();
    // carmera
    gluLookAt(cam_poz.x(), cam_poz.y(), cam_poz.z(),
              0, 0, 0,
              -sin(cam_poz.theta()), cos(cam_poz.theta()), 0);
    drawAxis();
    for(auto &i : objs){
        shared_ptr<Object> sp(i.lock());
        if(sp){
            sp->draw();
        }
    }

    // clear matrix stack.
    glutSwapBuffers();
}

void mouse(GLint btn, GLint state, GLint x, GLint y)
{
    switch(btn){

    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case VK_SPACE :
            cout << "space key" << endl;
            break;
        case VK_ESCAPE :
            exit(0);
        case 'w':
        case 'W':
            if(cam_poz.r() > 0){
                cam_poz.r() -= .25;
            }
            cout << cam_poz.r() << endl;
            break;
        case 'S':
        case 's':
            if(cam_poz.r() < 10000){
                cam_poz.r() += .25;
            }
            cout << cam_poz.r() << endl;
            break;
    }
}

void specialKey(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_UP:
            if(cam_poz.theta() < Tool::toRad(90)){
                cam_poz.theta() += Tool::toRad(4);
            }
            break;
        case GLUT_KEY_DOWN:
            if(cam_poz.theta() > Tool::toRad(-90)){
                cam_poz.theta() -= Tool::toRad(4);
            }
            break;
    }
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // if(w <= h){
    //     glOrtho(-2, 2, -2.f * h / w, 2. * w / h, 1, 20);
    // }else{
    //     glOrtho(-2.f * w / h, 2.f * w / h, -2, 2, 1, 20);
    // }
    gluPerspective(100, static_cast<GLdouble>(w) / h , 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}

void idle()
{
    // lock fps
    static clock_t dt = 0;
    static clock_t clk = 0;
    double fps;
    dt = clock() - clk;
    clk = clock();
    fps = CLOCKS_PER_SEC / static_cast<double>(dt);
    if(fps < fps_lock && fps_adapt > 0){
        --fps_adapt;
    }else{
        ++fps_adapt;
    }
    // cout << setiosflags(ios::fixed) << setprecision(1);
    // cout << "FPS: " << CLOCKS_PER_SEC / static_cast<double>(dt) << " adapt: "
    //      << fps_adapt << " \r" ;
    Sleep(fps_adapt);
    glutPostRedisplay();
}

void drawAxis()
{
    const std::vector<std::array<GLfloat, 3>> xa = {
            {0, 0, 0}, {2, 0, 0}
    };
    const std::vector<std::array<GLfloat, 3>> ya = {
            {0, 0, 0}, {0, 2, 0}
    };
    const std::vector<std::array<GLfloat, 3>> za = {
            {0, 0, 0}, {0, 0, 2}
    };
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(LINE_WIDTH);
    glBegin(GL_POLYGON);
    glColor3fv(array<GLfloat, 3>({1, 0, 0}).data());
    glVertex3fv(xa[0].data());
    glVertex3fv(xa[1].data());
    glColor3fv(array<GLfloat, 3>({0, 1, 0}).data());
    glVertex3fv(ya[0].data());
    glVertex3fv(ya[1].data());
    glColor3fv(array<GLfloat, 3>({0, 0, 1}).data());
    glVertex3fv(za[0].data());
    glVertex3fv(za[1].data());
    glEnd();
}
