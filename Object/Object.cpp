//
// Created by kieru on 2022/9/20.
//

#include "Object.h"
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<algorithm>

using namespace std;

void Object::readAnnotation(std::stringstream &ss)
{
    string s;
    getline(ss, s);
    if(s.size() > 0)
        cout << s.substr(1) << endl;
}
void Object::readVertex(std::stringstream &ss)
{
    GLfloat m_v(0);
    vector<GLfloat> fv;
    Vector3 vtx3;
    GLfloat f;
    while(ss >> f){
        fv.push_back(f);
        m_v = max(m_v, abs(f));
    }
    if(fv.size() >= 3){
        vtx3.x() = fv[0];
        vtx3.y() = fv[1];
        vtx3.z() = fv[2];
        vertices_.push_back(vtx3);
    }else{
        // throw
    }
    modelSize_ = m_v;
}
void Object::readTexture(std::stringstream &ss)
{
    vector<GLfloat> fv;
    Vector2 vtx2;
    GLfloat f;
    while(ss >> f){
        fv.push_back(f);
    }
    if(fv.size() >= 2){
        vtx2.x() = fv[0];
        vtx2.y() = fv[1];
        texCoords_.push_back(vtx2);
    }else{
        // throw
    }
}
void Object::readNormalVector(std::stringstream &ss)
{
    vector<GLfloat> fv;
    Vector3 vtx3;
    GLfloat f;
    while(ss >> f){
        fv.push_back(f);
    }
    if(fv.size() >= 3){
        vtx3.x() = fv[0];
        vtx3.y() = fv[1];
        vtx3.z() = fv[2];
        normalVectors_.push_back(vtx3);
    }else{
        // throw
    }
}
void Object::readFace(std::stringstream &ss)
{
    // assume there's no ' ' between '/'.
    string::iterator i1, i2;
    Face f;
    int idx;
    string s;
    while(ss >> s){
        array<long long, 3> fi({-1, -1, -1});
        // "a/*/c" or "a/b" or "a"
        i1 = find(s.begin(), s.end(), '/');
        idx = stoi(string(s.begin(), i1));
        fi[0] = idx - 1;
        if(i1 != s.end()){
            // "a//c", "a/b", "a/b/c"
            i2 = find(++i1 , s.end(), '/');
            if(i2 != s.end()){
                // a//c, a/b/c
                if(i1 == i2){
                    // a//c
                    idx = stoi(string(++i2, s.end()));
                    fi[2] = idx - 1;
                }else{
                    idx = stoi(string(i1, i2));
                    fi[1] = idx - 1;
                    idx = stoi(string(++i2, s.end()));
                    fi[2] = idx - 1;
                }
            }else{
                // a/b
                fi[1] = idx - 1;
            }
        }else{
            // "a"
        }
        f.push_back(fi);
    }
    faces_.push_back(f);
}

void Object::import(const std::string path)
{
    const unordered_map<std::string, void(Object::*)(stringstream&)> obj_flag = {
            {"vn", &Object::readNormalVector}, {"f", &Object::readFace},
            {"#", &Object::readAnnotation}, {"v", &Object::readVertex},
            {"vt", &Object::readTexture}
    };
    fstream fs;
    string line;
    fs.open(path, ios::in);
    if(!fs.is_open()){
        cerr << path << " open failed." << endl;
        exit(-1);
    }
    cout << path << " opened." << endl;
    while(getline(fs, line)){
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        // wtf?
        if(obj_flag.find(cmd) != obj_flag.end())
            (this->*obj_flag.at(cmd))(ss);
        else if(cmd != " " && cmd != ""){
            cerr << "Command \"" << cmd << "\" not found." << endl;
        }
    }
    fs.close();
}

void Object::draw() const {
    setGLColor();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(const auto &f : faces_){
        glBegin(GL_POLYGON);
        for(const auto &iv : f){
            if(iv[0] != -1)
                glVertex3fv(vertices_[iv[0]].data());
            if(iv[2] != -1)
                glNormal3fv(normalVectors_[iv[2]].data());
        }
        glEnd();
    }
}



void Object::setGLColor() const {
    unsigned color = faceColor_;
    unsigned char r, g, b;
    b = color & 255;
    color = color >> 8;
    g = color & 255;
    color = color >> 8;
    r = color & 255;
    glColor3b(r, g, b);
}

void Object::init() const
{
    /* world coordinate system */
    glPushMatrix();
    /* father coordinate system */

    // rotate around father obj
    glRotatef(0, 0, 1, 0);
    glTranslatef(transform_.localPosition().x(), transform_.localPosition().y(), transform_.localPosition().z());
    // rotate itself
    /* eulerAngle realize */
    glRotatef(transform_.eulerAngles().x(), 1, 0, 0);
    glRotatef(transform_.eulerAngles().y(), 0, 1, 0);
    glRotatef(transform_.eulerAngles().z(), 0, 0, 1);

    glScalef(transform_.scale().x(), transform_.scale().y(), transform_.scale().z());
    draw();
    glPopMatrix();
}
