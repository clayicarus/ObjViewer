//
// Created by kieru on 2022/9/21.
//

#ifndef OBJVIEWER_VERTEX3_H
#define OBJVIEWER_VERTEX3_H
#include<array>
#include<GL/freeglut.h>
#include<algorithm>

class Vertex3 {
public:
    Vertex3() = default;
    Vertex3(std::initializer_list<GLfloat> il) {
        std::copy(il.begin(), il.end(), vertex3_.data());
    }
    Vertex3(GLfloat x, GLfloat y, GLfloat z) {
        vertex3_[0] = x;
        vertex3_[1] = y;
        vertex3_[2] = z;
    }

    GLfloat& x() { return vertex3_[0]; }
    GLfloat& y() { return vertex3_[1]; }
    GLfloat& z() { return vertex3_[2]; }
    const GLfloat * data() const { return vertex3_.data(); }
private:
    std::array<GLfloat, 3> vertex3_;
};


#endif //OBJVIEWER_VERTEX3_H
