//
//  geometry.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "geometry.hpp"

void Geometry::paint() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    
    glVertexAttrib3fv(2, &currentColor[0]);
    glVertexAttribI1i(3, renderMode);
    glDrawElements(renderType, (int) indices.size() * 3, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
}

void Geometry::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            renderType = GL_TRIANGLE_STRIP;
            break;
        case Outlined:
            renderType = GL_LINE_LOOP;
            break;
        default:
            break;
    }
    updateBuffer();
}

void Geometry::updateBuffer() {
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(frag), &indices[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void Geometry::addFrag(unsigned int a, unsigned int b, unsigned int c) {
    indices.push_back(frag(a, b, c));
}
void Geometry::addFrag(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
    indices.push_back(frag(a, b, c));
    indices.push_back(frag(c, d, a));
}
void Geometry::reverse() {
    for (int i = 0; i < indices.size(); i++) {
        indices[i] = vec3(indices[i].z, indices[i].y, indices[i].x);
    }
    updateBuffer();
}

void Geometry::applyTransformation(mat4 matrix) {
    for (int i = 0; i < vertices.size(); i += 2) {
        vertices[i] = vec3(matrix * vec4(vertices[i], 1.0f));
    }
    updateBuffer();
}

GLuint Geometry::getVAO() {
    return VAO;
}

void Object::applyTransformation(mat4 matrix) {}
void Object::paint() {}
void Object::translate(vec3 t) {
    applyTransformation(glm::translate(mat4(1.0f), t));
    origin = glm::translate(mat4(1.0f), t) * vec4(origin, 1);
}
void Object::scale(vec3 s) {
    applyTransformation(glm::translate(glm::scale(glm::translate(mat4(1.0f), -origin), s), origin));
}
void Object::rotate(float angle, vec3 axis) {
    applyTransformation(glm::translate(glm::rotate(glm::translate(mat4(1.0f), -origin), angle, axis), origin));
}

void Group::applyTransformation(mat4 matrix) {
    for (auto o : objects) {
        o->applyTransformation(matrix);
    }
}
void Group::addObject(Object *obj) {
    objects.push_back(obj);
}
void Group::paint() {
    for (auto o : objects) {
        o->paint();
    }
}
