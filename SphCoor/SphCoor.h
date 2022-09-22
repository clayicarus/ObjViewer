//
// Created by kieru on 2022/9/14.
//

#ifndef OBJIMPORT_SPHCOOR_H
#define OBJIMPORT_SPHCOOR_H

#include<GL/freeglut.h>
class SphCoor{
public:
    SphCoor() = default;
    SphCoor(GLfloat r, GLfloat phi, GLfloat theta) :
            r_(r), phi_(phi), theta_(theta) {}
    GLfloat& r() { return r_; }
    GLfloat& phi() { return phi_; }
    GLfloat& theta() { return theta_; }

    void calCart();
    GLfloat x() const { return x_; }
    GLfloat y() const { return y_; }
    GLfloat z() const { return z_; }
private:
    GLfloat r_ = 0;
    GLfloat phi_ = 0;
    GLfloat theta_ = 0;
    GLfloat x_ = 0;
    GLfloat y_ = 0;
    GLfloat z_ = 0;
};


#endif //OBJIMPORT_SPHCOOR_H
