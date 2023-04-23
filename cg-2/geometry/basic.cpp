//
//  basic.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "basic.hpp"

void Cube::setup() {
    // 采用纸盒展开的贴图，下半部分顶点
    vertices[0] = vec3(-0.5, -0.5, -0.5);
    vertices[1] = vec3(0.25, 0.25, 0);
    vertices[2] = vec3(-0.5, -0.5, 0.5);
    vertices[3] = vec3(0.25, 0.5, 0);
    vertices[4] = vec3(0.5, -0.5, 0.5);
    vertices[5] = vec3(0.5, 0.5, 0);
    vertices[6] = vec3(0.5, -0.5, -0.5);
    vertices[7] = vec3(0.5, 0.25, 0);
    // 上半部分顶点
    vertices[8] = vec3(-0.5, 0.5, -0.5);
    vertices[9] = vec3(0, 0.25, 0);
    vertices[10] = vec3(-0.5, 0.5, 0.5);
    vertices[11] = vec3(0, 0.5, 0);
    vertices[12] = vec3(0.5, 0.5, 0.5);
    vertices[13] = vec3(0.75, 0.5, 0);
    vertices[14] = vec3(0.5, 0.5, -0.5);
    vertices[15] = vec3(0.75, 0.25, 0);
    // 然后是两翼，两侧顶点
    vertices[16] = vec3(-0.5, 0.5, -0.5);
    vertices[17] = vec3(0.25, 0, 0);
    vertices[18] = vec3(-0.5, 0.5, 0.5);
    vertices[19] = vec3(0.25, 0.75, 0);
    vertices[20] = vec3(0.5, 0.5, 0.5);
    vertices[21] = vec3(0.5, 0.75, 0);
    vertices[22] = vec3(0.5, 0.5, -0.5);
    vertices[23] = vec3(0.5, 0, 0);
    // 接缝处
    vertices[24] = vec3(-0.5, 0.5, -0.5);
    vertices[25] = vec3(1, 0.25, 0);
    vertices[26] = vec3(-0.5, 0.5, 0.5);
    vertices[27] = vec3(1, 0.5, 0);
    
    addFrag(3, 2, 1, 0);
    addFrag(2, 3, 7, 6);
    addFrag(0, 1, 5, 4);
    addFrag(1, 2, 10, 9);
    addFrag(3, 0, 8, 11);
    addFrag(6, 7, 12, 13);
}
