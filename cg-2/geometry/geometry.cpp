//
//  geometry.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "geometry.hpp"
#include "scene.hpp"

void Geometry::paint() {
    glBindVertexArray(VAO);
    material.useMaterial();
    
    mat4 MVP = mainScene->getVPMatrix() * modelMatrix;
    mat4 MV = mainScene->getProjectionMatrix() * modelMatrix;
    glUniformMatrix4fv(programs.shapeMVPLocation, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(programs.shapeMVLocation, 1, GL_FALSE, &MV[0][0]);
    if (indices.size()) {
        glDrawElements(renderType, (int) indices.size() * 3, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(renderType, 0, (int) vertices.size() / 3);
    }

    glBindVertexArray(0);
}

void Geometry::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            renderType = GL_TRIANGLES;
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
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));

    if (indices.size()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(frag), &indices[0], GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}

void Geometry::addFrag(unsigned int a, unsigned int b, unsigned int c) {
    indices.push_back(frag(a, b, c));
}
void Geometry::addFrag(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
    indices.push_back(frag(a, b, c));
    indices.push_back(frag(c, d, a));
}
void Geometry::addVert(const vec3 &vertPos, const vec2 &fragPos, const vec3 &normal) {
    vertices.push_back(vertPos);
    vertices.push_back(vec3(fragPos, 0));
    vertices.push_back(normal);
}
void Geometry::reverse() {
    for (int i = 0; i < indices.size(); i++) {
        indices[i] = vec3(indices[i].z, indices[i].y, indices[i].x);
    }
    updateBuffer();
}

void Geometry::applyTransformation(mat4 matrix) {
    modelMatrix = matrix * modelMatrix;
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
