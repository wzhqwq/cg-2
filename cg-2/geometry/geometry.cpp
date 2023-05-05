//
//  geometry.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "geometry.hpp"
#include "scene.hpp"
#include "shader.hpp"

void Geometry::paint() {
    glBindVertexArray(VAO);
    material.useMaterial();
    
    glUniformMatrix4fv(shapeShader->modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    if (indices.size()) {
        glDrawElements(renderType, (int) indices.size() * 3, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(renderType, 0, (int) vertices.size() / 3);
    }

    glBindVertexArray(0);
}
void Geometry::castShadow(mat4 t){
    glBindVertexArray(VAO);
    
    mat4 shadowMatrix = t * modelMatrix;
    glUniformMatrix4fv(shapeShader->modelLoc, 1, GL_FALSE, &shadowMatrix[0][0]);
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
    for (int i = 0; i < vertices.size(); i += 3) {
        vertices[i + 2] = -vertices[i + 2];
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
void Object::castShadow(mat4 t) {}
vec3 Object::getTranslation() {
    return origin;
}
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
void Object::translateOrigin(vec3 delta) {
    origin += delta;
}

void Group::applyTransformation(mat4 matrix) {
    vec3 translation = matrix * vec4(0, 0, 0, 1);
    for (auto o : objects) {
        o->applyTransformation(matrix);
        o->translateOrigin(translation);
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
void Group::castShadow(mat4 t) {
    for (auto o : objects) {
        o->castShadow(t);
    }
}
