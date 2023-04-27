//
//  geometry.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#ifndef geometry_hpp
#define geometry_hpp

#include "common.h"
#include "material.hpp"
#include <vector>
#include <cmath>

using namespace std;

enum DrawMode {
    Filled, Outlined, Translucent
};

class Object {
public:
    virtual void applyTransformation(mat4 matrix);
    virtual void paint();
    void translate(vec3 t);
    void scale(vec3 s);
    void rotate(float angle, vec3 axis);
private:
    vec3 origin = vec3(0);
};

typedef vec<3, unsigned int, defaultp> frag;

class Geometry : public Object {
public:
    Geometry() : Object() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);
    }
    ~Geometry() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
    }
    
    void applyTransformation(mat4 matrix);
    void paint();
    void setMode(DrawMode mode);
    void reverse();

    GLuint getVAO();
    Material material;
protected:
    void updateBuffer();
    // must in anticlockwise
    void addFrag(unsigned int a, unsigned int b, unsigned int c);
    void addFrag(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
    void addVert(const vec3 &vertPos, const vec2 &fragPos, const vec3 &normal);
    
    GLuint VAO;
    GLuint vertexBuffer, indexBuffer;
    vector<vec3> vertices;
    vector<frag> indices;
    GLenum renderType = GL_TRIANGLES;
    mat4 modelMatrix = mat4(1);
};

class Group : public Object {
public:
    ~Group() {
        for (auto o : objects) {
            delete o;
        }
    }
    void applyTransformation(mat4 matrix);
    void addObject(Object *obj);
    void paint();
private:
    vector<Object *> objects;
};

#endif
