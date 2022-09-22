//
// Created by kieru on 2022/9/20.
//

#ifndef OBJIMPORT_OBJECT_H
#define OBJIMPORT_OBJECT_H

#include<vector>
#include<gl/freeglut.h>
#include<array>
#include<string>
#include<sstream>
#include<functional>
#include<unordered_map>
#include "../Vector/Vector3.h"
#include "../Vector/Vector2.h"
#include "Transform/Transform.h"

class Object {
public:
    typedef std::vector<std::array<long long, 3>> Face;

    Object() = default;
    Object(std::string path) {import(path);};

    std::vector<Vector3>::size_type vertexNum() const {return vertices_.size();}
    std::vector<Vector3>& vertices() {return vertices_;}
    std::vector<Vector2>& textureCoordinates() {return texCoords_;}
    std::vector<Vector3>& normalVectors() {return normalVectors_;}
    std::vector<Face>& faces() {return faces_;}
    unsigned& faceColor() {return faceColor_;}
    Transform& transform() {return transform_;}

    GLfloat modelSize() const {return modelSize_;}

    void import(const std::string path);
    void init() const;
private:
    unsigned faceColor_ = 0xffffff;
    GLfloat modelSize_;
    std::vector<Vector3> vertices_;
    std::vector<Vector2> texCoords_;
    std::vector<Vector3> normalVectors_;
    std::vector<Face> faces_;

    Transform transform_;

    void readAnnotation(std::stringstream &ss);
    void readVertex(std::stringstream &ss);
    void readTexture(std::stringstream &ss);
    void readNormalVector(std::stringstream &ss);
    void readFace(std::stringstream &ss);
    void setGLColor() const;
    void draw() const;
};

#endif //OBJIMPORT_OBJECT_H
