//
// Created by kieru on 2022/9/21.
//

#ifndef OBJVIEWER_VECTOR2_H
#define OBJVIEWER_VECTOR2_H
#include<array>
#include<GL/freeglut.h>
#include<algorithm>

class Vector2 {
public:
    Vector2() = default;
    Vector2(std::initializer_list<GLfloat> il) {
        std::copy(il.begin(), il.end(), Vertex2_.data());
    }
    Vector2(GLfloat x, GLfloat y) {
        Vertex2_[0] = x;
        Vertex2_[1] = y;
    }

    GLfloat& x() { return Vertex2_[0]; }
    GLfloat& y() { return Vertex2_[1]; }
    const GLfloat * data() const { return Vertex2_.data(); }
private:
    std::array<GLfloat, 2> Vertex2_;
};

#endif //OBJVIEWER_VECTOR2_H
