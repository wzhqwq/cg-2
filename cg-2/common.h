//
//  common.h
//  cg-1
//
//  Created by 王子涵 on 2023/3/21.
//

#ifndef common_h
#define common_h

#include <cstdio>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 1000
#define HEIGHT 800
#define DOT_SIZE 10

using namespace glm;

inline void printVec(const char *label, vec4 v) {
    printf("%s: (%.2f %.2f %.2f %.2f)\n", label, v.x, v.y, v.z, v.w);
}
inline void printVec(const char *label, vec3 v) {
    printf("%s: (%.2f %.2f %.2f)\n", label, v.x, v.y, v.z);
}
inline void printMat(const char *label, mat4 m) {
    printf("%s:\t(%.2f %.2f %.2f %.2f\n", label, m[0][0], m[0][1], m[0][2], m[0][3]);
    printf("\t\t %.2f %.2f %.2f %.2f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
    printf("\t\t %.2f %.2f %.2f %.2f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
    printf("\t\t %.2f %.2f %.2f %.2f)\n", m[3][0], m[3][1], m[3][2], m[3][3]);
}

const float r90 = pi<float>() / 2;
const float r180 = pi<float>();

#endif /* common_h */
