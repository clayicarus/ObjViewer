//
// Created by kieru on 2022/9/21.
//

#ifndef OBJVIEWER_VECTOR3_H
#define OBJVIEWER_VECTOR3_H
#include<array>
#include<GL/freeglut.h>
#include<algorithm>

class Vector3 {
public:
    Vector3() = default;
    Vector3(std::initializer_list<GLfloat> il) {
        std::copy(il.begin(), il.end(), vertex3_.data());
    }
    Vector3(GLfloat x, GLfloat y, GLfloat z) {
        vertex3_[0] = x;
        vertex3_[1] = y;
        vertex3_[2] = z;
    }

    GLfloat& x() { return vertex3_[0]; }
    GLfloat& y() { return vertex3_[1]; }
    GLfloat& z() { return vertex3_[2]; }
    const GLfloat& x() const { return vertex3_[0]; }
    const GLfloat& y() const { return vertex3_[1]; }
    const GLfloat& z() const { return vertex3_[2]; }

    const GLfloat * data() const { return vertex3_.data(); }
private:
    std::array<GLfloat, 3> vertex3_;
};


#endif //OBJVIEWER_VECTOR3_H
