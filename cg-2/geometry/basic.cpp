//
//  basic.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "basic.hpp"

void Cube::setup() {
    // 采用纸盒展开的贴图，下半部分顶点
    vertices.push_back(vec3(-0.5, -0.5, -0.5));
    vertices.push_back(vec3(0.25, 0.25, 0));
    vertices.push_back(vec3(-0.5, -0.5, 0.5));
    vertices.push_back(vec3(0.25, 0.5, 0));
    vertices.push_back(vec3(0.5, -0.5, 0.5));
    vertices.push_back(vec3(0.5, 0.5, 0));
    vertices.push_back(vec3(0.5, -0.5, -0.5));
    vertices.push_back(vec3(0.5, 0.25, 0));
    // 上半部分顶点
    vertices.push_back(vec3(-0.5, 0.5, -0.5));
    vertices.push_back(vec3(0, 0.25, 0));
    vertices.push_back(vec3(-0.5, 0.5, 0.5));
    vertices.push_back(vec3(0, 0.5, 0));
    vertices.push_back(vec3(0.5, 0.5, 0.5));
    vertices.push_back(vec3(0.75, 0.5, 0));
    vertices.push_back(vec3(0.5, 0.5, -0.5));
    vertices.push_back(vec3(0.75, 0.25, 0));
    // 然后是两翼，两侧顶点
    vertices.push_back(vec3(-0.5, 0.5, -0.5));
    vertices.push_back(vec3(0.25, 0, 0));
    vertices.push_back(vec3(-0.5, 0.5, 0.5));
    vertices.push_back(vec3(0.25, 0.75, 0));
    vertices.push_back(vec3(0.5, 0.5, 0.5));
    vertices.push_back(vec3(0.5, 0.75, 0));
    vertices.push_back(vec3(0.5, 0.5, -0.5));
    vertices.push_back(vec3(0.5, 0, 0));
    // 接缝处
    vertices.push_back(vec3(-0.5, 0.5, -0.5));
    vertices.push_back(vec3(1, 0.25, 0));
    vertices.push_back(vec3(-0.5, 0.5, 0.5));
    vertices.push_back(vec3(1, 0.5, 0));
    
    addFrag(3, 2, 1, 0);
    addFrag(2, 3, 7, 6);
    addFrag(0, 1, 5, 4);
    addFrag(1, 2, 10, 9);
    addFrag(3, 0, 8, 11);
    addFrag(6, 7, 12, 13);
}

void Sphere::setup(int rSub, int aSub) {
    float texFragX = 1.0f / rSub, texFragY = 1.0f / aSub;
    float Pi = pi<float>();
    for (int i = 0; i <= rSub; i++) {
        float longitude = 2 * Pi * i / rSub;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        vertices.push_back(vec3(0, -0.5f, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 1, 0));
        for (int j = 1; j < aSub; j++) {
            float latitude = Pi * ((float) j / aSub - 0.5f);
            vertices.push_back(vec3(x * cos(latitude), 0.5f * sin(latitude), z * cos(latitude)));
            vertices.push_back(vec3(texFragX * i, 1.0f - texFragY * j, 0));
        }
        vertices.push_back(vec3(0, 0.5f, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 0, 0));
    }
    for (int i = 0; i < rSub; i++) {
        int offset = (aSub + 1) * i;
        int nextOffset = offset + (aSub + 1);
        addFrag(offset, nextOffset + 1, offset + 1);
        for (int j = 1; j < aSub - 1; j++) {
            addFrag(offset + j, nextOffset + j, nextOffset + j + 1, offset + j + 1);
        }
        addFrag(offset + aSub - 1, nextOffset + aSub - 1, offset + aSub);
    }
}

void Cylinder::setup(int sub) {
    float texFragX = 1.0f / sub;
    float Pi = pi<float>();
    for (int i = 0; i <= sub; i++) {
        float longitude = 2 * Pi * i / sub;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        vertices.push_back(vec3(0, -0.5f, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 1, 0));
        
        vertices.push_back(vec3(x, -0.5f, z));
        vertices.push_back(vec3(texFragX * i, 2.0f / 3, 0));
        vertices.push_back(vec3(x, 0.5f, z));
        vertices.push_back(vec3(texFragX * i, 1.0f / 3, 0));

        vertices.push_back(vec3(0, 0.5f, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 0, 0));
    }
    for (int i = 0; i < sub; i++) {
        int offset = i * 4;
        int nextOffset = offset + 4;
        addFrag(offset, nextOffset + 1, offset + 1);
        addFrag(offset + 1, nextOffset + 1, nextOffset + 2, offset + 2);
        addFrag(offset + 2, nextOffset + 2, offset + 3);
    }
}

void Cone::setup(int sub) {
    float texFragX = 1.0f / sub;
    float Pi = pi<float>();
    for (int i = 0; i <= sub; i++) {
        float longitude = 2 * Pi * i / sub;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        vertices.push_back(vec3(0, 0, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 1, 0));
        
        vertices.push_back(vec3(x, 0, z));
        vertices.push_back(vec3(texFragX * i, 0.5f, 0));

        vertices.push_back(vec3(0, 1, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 0, 0));
    }
    for (int i = 0; i < sub; i++) {
        int offset = i * 3;
        int nextOffset = offset + 3;
        addFrag(offset, nextOffset + 1, offset + 1);
        addFrag(offset + 1, nextOffset + 1, offset + 2);
    }
}

void Ring::setup(int cSub, int aSub, float inset, float start, float end) {
    float texFragX = 1.0f / cSub, texFragY = 1.0f / aSub;
    float Pi = pi<float>();
    float r = (1 - inset) / 4;
    float R = inset / 2 + r;
    for (int i = 0; i <= cSub; i++) {
        float longitude = 2 * Pi * i / cSub;
        vec4 pos = vec4(r * sin(longitude) + R, r * cos(longitude), 0, 0);
        vertices.push_back(vec3(R * cos(-start), 0, R * sin(-start)));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 1, 0));
        // 1 ~ aSub+1
        for (int j = 0; j <= aSub; j++) {
            float angle = start + (end - start) * j / aSub;
            // 将xy平面上的圆形样条沿弧旋转
            vertices.push_back(vec3(glm::rotate(mat4(1), angle, vec3(0, 1, 0)) * pos));
            vertices.push_back(vec3(texFragX * i, 1.0f - texFragY * j, 0));
        }
        // aSub+2
        vertices.push_back(vec3(R * cos(-end), 0, R * sin(-end)));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 0, 0));
    }
    for (int i = 0; i < cSub; i++) {
        int offset = (aSub + 3) * i;
        int nextOffset = offset + (aSub + 3);
        addFrag(offset, nextOffset + 1, offset + 1);
        for (int j = 1; j <= aSub; j++) {
            addFrag(offset + j, nextOffset + j, nextOffset + j + 1, offset + j + 1);
        }
        addFrag(offset + aSub + 1, nextOffset + aSub + 1, offset + aSub + 2);
    }
}
