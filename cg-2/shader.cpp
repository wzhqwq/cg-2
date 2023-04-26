//
//  shader.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#include "shader.hpp"

Programs programs;

GLuint loadProgram(string vert, string frag) {
    GLuint program = glCreateProgram();
    loadVertexShader(vert.c_str(), program);
    loadFragmentShader(frag.c_str(), program);
    glLinkProgram(program);
    
    char log[1000];
    int logLength;
    glGetProgramInfoLog(program, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("program linking error:\n%s\n", log);
    }
    
    return program;
}

void initPrograms(string basePath) {
    basePath += "/shaders/";
    programs.shapeProgram = loadProgram(basePath + "shape.vert", basePath + "shape.frag");
    programs.fixedProgram = loadProgram(basePath + "shape.vert", basePath + "shape.frag");
}
