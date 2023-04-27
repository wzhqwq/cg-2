//
//  scene.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "scene.hpp"

mat4 Scene::getVPMatrix() {
    changed = 0;
    updateVPMatrix();
    return VP;
}
mat4 Scene::getProjectionMatrix() { return projection; }
void Scene::updateVPMatrix() {
    VP = projection * view;
//    invVP = inverse(VP);
}

int Scene::isChanged() { return changed; }

void Scene::moveTo(vec3 p) {
    currentPos = p;
    view = lookAt(currentPos, vec3(0, 0, 0), vec3(0, 1, 0));
    changed = 1;
}

vec3 Scene::toWorldPos(float posX, float posY) {
    if (changed) updateVPMatrix();
    vec4 viewPos = vec4(posX / (w * 0.5f) - 1.0f,
                          -(posY / (h * 0.5f) - 1.0f),
                          1.0f,
                          1.0f);
    vec4 worldPos = invVP * viewPos;

    return vec3(worldPos);
}

void Scene::render(GLenum renderMode) {
    glRenderMode(renderMode);
    if (renderMode == GL_SELECT) {
        glInitNames();
        glPushName(0);
    }
    for (int i = 0; i < objects.size(); i++) {
        if (renderMode == GL_SELECT) glLoadName(i);
        objects[i]->paint();
    }
}
