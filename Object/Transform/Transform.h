//
// Created by kieru on 2022/9/22.
//

#ifndef OBJVIEWER_TRANSFORM_H
#define OBJVIEWER_TRANSFORM_H
#include"../../Vector/Vector3.h"
#include<GL/freeglut.h>
#include"../../Quaternion/Quaternion.h"

// class Transform : public Component : public Object
class Transform {
// rotate and translate
public:
    Transform() : localPosition_(0, 0, 0),
        rotation_(1, 0, 0, 0),
        scale_(1, 1, 1),
        eulerAngles_(0, 0, 0){};

    void translate(Vector3 translation);
    // self rotate
    void rotate(Vector3 eulerAngles);

    Vector3& localPosition() {return localPosition_;}
    Vector3& scale() {return scale_;}
    Vector3& eulerAngles() {return eulerAngles_;}
    const Vector3& localPosition() const {return localPosition_;}
    const Vector3& scale() const {return scale_;}
    // when it bigger than
    const Vector3& eulerAngles() const {return eulerAngles_;}
private:
    Vector3 localPosition_;
    Vector3 scale_;
    // self rotate
    Vector3 eulerAngles_;

    /* not realized */
    // rotate around father
    void rotate(Vector3 axis, GLfloat angle);
    const Quaternion& rotation() const {return rotation_;}
    Quaternion& rotation() {return rotation_;}
    Quaternion rotation_;
};


#endif //OBJVIEWER_TRANSFORM_H
