//
// Created by kieru on 2022/9/21.
//

#ifndef OBJVIEWER_FACE_H
#define OBJVIEWER_FACE_H
#include<vector>
#include"../Vertex/Vertex3.h"

class Face {
public:
    std::vector<Vertex3>::size_type vertexNums() const {return vertices_.size();}
private:
    std::vector<Vertex3> vertices_;
};


#endif //OBJVIEWER_FACE_H
