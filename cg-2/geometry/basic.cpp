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
        vertices.push_back(vec3(texFragX * (i + 0.5f), 0, 0));
        for (int j = 1; j < aSub; j++) {
            float latitude = Pi * ((float) j / aSub - 0.5f);
            vertices.push_back(vec3(x * cos(latitude), 0.5f * sin(latitude), z * cos(latitude)));
            vertices.push_back(vec3(texFragX * i, texFragY * j, 0));
        }
        vertices.push_back(vec3(0, 0.5, 0));
        vertices.push_back(vec3(texFragX * (i + 0.5f), 1, 0));
    }
    for (int i = 0; i < rSub; i++) {
        int offset = (aSub + 1) * i;
        int nextOffset = (aSub + 1) * (i + 1);
        addFrag(offset, nextOffset + 1, offset + 1);
        for (int j = 1; j < aSub - 1; j++) {
            addFrag(offset + j, nextOffset + j, nextOffset + j + 1, offset + j + 1);
        }
        addFrag(offset + aSub - 1, nextOffset + aSub - 1, offset + aSub);
    }
}
