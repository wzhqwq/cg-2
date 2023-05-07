//
//  scene.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "scene.hpp"

void Scene::moveTo(vec3 p) {
    mat4 viewProjection = projection * lookAt(p, vec3(0, 0, 0), vec3(0, 1, 0));
    glUseProgram(shapeShader->program);
    glUniformMatrix4fv(shapeShader->viewProjectionLoc, 1, GL_FALSE, &viewProjection[0][0]);
    glUniform3fv(shapeShader->viewerPosLoc, 1, &p[0]);
}

void Scene::render() {
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->paint();
    }
}
