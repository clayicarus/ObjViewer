//
// Created by kieru on 2022/9/22.
//

#ifndef QUATERNION_H
#define QUATERNION_H
#include <type_traits>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include <GL/freeglut.h>

class Quaternion
{
public:
    Quaternion() = default;
    Quaternion(GLfloat a, GLfloat b, GLfloat c, GLfloat d) : w(a), x(b), y(c), z(d) {}
    Quaternion operator=(const Quaternion& a);
    Quaternion operator+(const Quaternion& a);
    Quaternion operator-(const Quaternion& a);
    Quaternion operator*(const Quaternion& a);
    Quaternion operator*(GLfloat a);
    bool operator==(const Quaternion& a);
    bool operator!=(const Quaternion& a);
    double mod();
    void conjugate();
private:
    GLfloat w, x, y, z;
};

#endif // QUATERNION_H

