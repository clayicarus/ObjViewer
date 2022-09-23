#include <iostream>
#include <GL/freeglut.h>
#include "main.h"
#include "Utility.h"
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
    static Object demo_model;
    demo_model.vertices() = {{1, 1, 1}, {1, 1, -1}, {-1, 1, -1}, {-1, 1, 1},
                            {1, -1, 1}, {1, -1, -1}, {-1, -1, -1}, {-1, -1, 1}};
    demo_model.faceColor() = Utility::to24BitColor(65, 65, 65);
    demo_model.faces() = {{{0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}},
                          {{4, -1, -1}, {0, -1, -1}, {3, -1, -1}, {7, -1, -1}},
                          {{6, -1, -1}, {2, -1, -1}, {1, -1, -1}, {5, -1, -1}},
                          {{5, -1, -1}, {4, -1, -1}, {7, -1, -1}, {6, -1, -1}},
                          {{5, -1, -1}, {1, -1, -1}, {0, -1, -1}, {4, -1, -1}}};

    string dir;
    if(argc == 2){
        dir = argv[1];
    }
    shared_ptr<Object> spObj;
    if(dir != "")
        spObj = make_shared<Object>(dir);
    else
        spObj = shared_ptr<Object>(&demo_model);

    spObj->faceColor() = Utility::to24BitColor(65, 65, 65);
    spObj->transform().localPosition() = Vector3(0, -spObj->modelSize() / 4 * 3, 0);
    spObj->transform().eulerAngles() = Vector3(0, 30, 0);

    objs.push_back(weak_ptr<Object>(spObj));
    cam.r() = spObj->modelSize() * 3;
    cout << "camera r: " << cam.r() << endl;

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(TITLE);

    init();
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
    glClearColor(Utility::toGL_RGB(BG_RED),
                 Utility::toGL_RGB(BG_GREEN),
                 Utility::toGL_RGB(BG_BLUE),
                 BG_ALPHA);
    light();
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
    // init
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // carmera view
    cam.calCart();
    gluLookAt(cam.x(), cam.y(), cam.z(),
              0, 0, 0,
              -sin(cam.theta()), cos(cam.theta()), 0);
    // world axis
    drawAxis();
    // object
    for(auto &i : objs){
        shared_ptr<Object> sp(i.lock());
        if(sp){
            sp->init();
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
            break;
        case VK_ESCAPE :
            exit(0);
        case 'w':
        case 'W':
            if(cam.r() - 200 * deltaTime_s > 0){
                cam.r() -= 200 * deltaTime_s;
            }
            break;
        case 'S':
        case 's':
            if(cam.r() + 200 * deltaTime_s < 10000){
                cam.r() += 200 * deltaTime_s;
            }
            break;
    }
}

void specialKey(int key, int x, int y)
{
    shared_ptr<Object> obj(objs.back());
    GLfloat deltaRad = Utility::toRad(200);
    switch(key){
        case GLUT_KEY_LEFT:
            obj->transform().eulerAngles() = (Vector3(obj->transform().eulerAngles().x(),
                                            obj->transform().eulerAngles().y() - 300 * deltaTime_s,
                                            obj->transform().eulerAngles().z()));
            break;
        case GLUT_KEY_RIGHT:
            obj->transform().eulerAngles() = (Vector3(obj->transform().eulerAngles().x(),
                                            obj->transform().eulerAngles().y() + 300 * deltaTime_s,
                                            obj->transform().eulerAngles().z()));
            break;
        case GLUT_KEY_UP:
            if(cam.theta() + deltaRad * deltaTime_s < Utility::toRad(90)){
                cam.theta() += deltaRad * deltaTime_s;
            }
            break;
        case GLUT_KEY_DOWN:
            if(cam.theta() - deltaRad * deltaTime_s > Utility::toRad(-90)){
                cam.theta() -= deltaRad * deltaTime_s;
            }
            break;
    }
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, static_cast<GLdouble>(w) / h , 0.1, 500);
}

void idle()
{
    // lock fps, time
    static clock_t clk = 0;
    double fps;
    deltaTime_clock = clock() - clk;
    clk = clock();
    deltaTime_s = deltaTime_clock / static_cast<double>(CLOCKS_PER_SEC);
    fps = 1 / deltaTime_s;
    if(fps < fps_lock && fps_adapt > 0){
        --fps_adapt;
    }else{
        ++fps_adapt;
    }
    // debug log
    cout << setiosflags(ios::fixed) << setprecision(1);
    cout << "FPS: " << fps << " adapt: "
         << fps_adapt << "         \r";
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
