//
// Created by kieru on 2022/9/22.
//
#include"Quaternion.h"

Quaternion Quaternion::operator+(const Quaternion& a)
{
    this->w += a.w;
    this->x += a.x;
    this->y += a.y;
    this->z += a.z;
    return *this;
}

Quaternion Quaternion::operator-(const Quaternion& a)
{
    this->w -=a.w;
    this->x -=a.x;
    this->y -=a.y;
    this->z -=a.z;
    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& a)
{
    this->w *=a.w;
    this->x *=a.x;
    this->y *=a.y;
    this->z *=a.z;
    return *this;
}

Quaternion Quaternion::operator=(const Quaternion& a)
{
    this->w = a.w;
    this->x = a.x;
    this->y = a.y;
    this->z = a.z;
    return *this;
}

bool Quaternion::operator==(const Quaternion& a)
{
    if (this->w == a.w && this->x == a.x && this->y == a.y && this->z == a.z)
        return  true;
    else return false;
}

bool Quaternion::operator!=(const Quaternion& a)
{
    return !(*this == a);
}

void Quaternion::conjugate()
{
    this->x = -x;
    this->y = -y;
    this->z = -z;
}

double Quaternion::mod()
{
    return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
}

Quaternion operator*(GLfloat a, Quaternion b)
{
    return b*a;
}

Quaternion Quaternion::operator*(GLfloat a)
{
    this->w *= a;
    this->x *= a;
    this->y *= a;
    this->z *= a;
    return *this;
}

