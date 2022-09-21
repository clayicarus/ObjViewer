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
#include "../Vertex/Vertex3.h"
#include "../Vertex/Vertex2.h"

class Object {
public:
    typedef std::vector<std::array<long long, 3>> Face;

    Object() = default;
    Object(std::string path) {import(path);};

    std::vector<Vertex3>::size_type vertexNum() const {return vertices_.size();}
    std::vector<Vertex3>& vertices() {return vertices_;}
    std::vector<Vertex2>& textureCoordinates() {return texCoords_;}
    std::vector<Vertex3>& normalVectors() {return normalVectors_;}
    std::vector<Face>& faces() {return faces_;}
    unsigned& faceColor() {return faceColor_;}
    void import(const std::string path);
    void draw() const;
    GLfloat modelSize() const {return modelSize_;}
private:
    unsigned faceColor_ = 0xffffff;
    GLfloat modelSize_;
    std::vector<Vertex3> vertices_;
    std::vector<Vertex2> texCoords_;
    std::vector<Vertex3> normalVectors_;
    std::vector<Face> faces_;
    void readAnnotation(std::stringstream &ss);
    void readVertex(std::stringstream &ss);
    void readTexture(std::stringstream &ss);
    void readNormalVector(std::stringstream &ss);
    void readFace(std::stringstream &ss);
    void setGLColor() const;
};

#endif //OBJIMPORT_OBJECT_H
