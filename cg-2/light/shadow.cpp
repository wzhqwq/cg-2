//
//  shadow.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/29.
//

#include "shadow.hpp"
#include "shader.hpp"


void ShadowPlane::setup() {
    addVert(vec3(-0.5, 0.001, -0.5), vec2(0, 0), vec3(0, 1, 0));
    addVert(vec3(-0.5, 0.001, 0.5), vec2(0, 0), vec3(0, 1, 0));
    addVert(vec3(0.5, 0.001, 0.5), vec2(0, 0), vec3(0, 1, 0));
    addVert(vec3(0.5, 0.001, -0.5), vec2(0, 0), vec3(0, 1, 0));
    addFrag(0, 1, 2, 3);
    material = Material(vec3(1, 1, 1));
}

void ShadowPlane::paint() {
    // 启用stencil buffer及其写入，清空缓冲区
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF);
    glClear(GL_STENCIL_BUFFER_BIT);

    // 仅在stencil buffer中绘制所有的阴影（置1），还需要禁用z缓冲绘制
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

    // 绘制阴影，使用简单材质
    unlitRedMaterial.useMaterial();
    for (auto o : casters) {
        o->castShadow(shadowMatrix);
    }

    // 在阴影图形内绘制平面以实现裁剪阴影（=1），禁用写入stencil buffer，启用z缓冲绘制
    glStencilMask(0x00);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    // 绘制平面，使用阴影材质
    glBindVertexArray(VAO);
//    unlitRedMaterial.useMaterial();
    shadowMaterial.useMaterial();
    glUniformMatrix4fv(shapeShader->modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, (int) indices.size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // 禁用stencil buffer
    glDisable(GL_STENCIL_TEST);
}

void ShadowPlane::updateLight(Light light) {
    lightPosDir = light.position;
    updateShadowMatrix();
}
void ShadowPlane::applyTransformation(mat4 matrix) {
    modelMatrix = matrix * modelMatrix;
    vec4 normal = normalize(modelMatrix * vec4(0, 1, 0, 0));
    vec4 center = modelMatrix * vec4(0, 0, 0, 1);
    center /= center.w;
    // (x - p.x)*n.x + (y - p.y)*n.y + (z - p.z)*n.z = 0 => ax + by + cz + d = 0
    plane = vec4(vec3(normal), -dot(normal, center));
    updateShadowMatrix();
}


void ShadowPlane::updateShadowMatrix() {
    if (lightPosDir.w < 0.5f) {
        // a * dx + b * dy + c * dz
        float denominator = dot(plane, lightPosDir);
        // [-a*dx -b*dx -c*dx -d*dx]
        // [-a*dy -b*dy -c*dy -d*dy] + I * denominator
        // [-a*dz -b*dz -c*dz -d*dz]
        // [0     0     0     0    ]
        mat4 baseMatrix = mat4(-lightPosDir.x * plane,
                               -lightPosDir.y * plane,
                               -lightPosDir.z * plane,
                               vec4(0));
        // glm是列优先访存，因此要做转置
        shadowMatrix = transpose(baseMatrix + mat4(denominator));
    }
    else {
        //    a(x - lx) + b(y - ly) + c(z - lz) + d = 0
        // => a*x + b*y + c*z + d + a*lx + b*ly + c*lz = 0
        // => new_d = d + a*lx + b*ly + c*lz
        float newD = plane.w + dot(vec3(lightPosDir), vec3(plane));
        mat4 baseMatrix = mat4(vec4(1, 0, 0, 0),
                               vec4(0, 1, 0, 0),
                               vec4(0, 0, 1, 0),
                               vec4(vec3(plane) / -newD, 0));
        shadowMatrix = (glm::translate(mat4(1), vec3(lightPosDir)) *
                        transpose(baseMatrix) *
                        glm::translate(mat4(1), -vec3(lightPosDir)));
    }
}
