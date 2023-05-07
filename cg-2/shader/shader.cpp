//
//  shader.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#include "shader.hpp"

ShapeShader *shapeShader;

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
    shapeShader = new ShapeShader(basePath);
}

ShapeShader::ShapeShader(string basePath) {
    program = loadProgram(basePath + "shape.vert", basePath + "shape.frag");
    modelLoc = glGetUniformLocation(program, "Model");
    viewProjectionLoc = glGetUniformLocation(program, "ViewProjection");
    modeLoc = glGetUniformLocation(program, "mode");
    ambientLoc = glGetUniformLocation(program, "ambient");
    diffuseLoc = glGetUniformLocation(program, "diffuse");
    specularLoc = glGetUniformLocation(program, "specular");
    materialCoefficientsLoc = glGetUniformLocation(program, "materialCoefficients");
    lightPosLoc = glGetUniformLocation(program, "lightPosDir");
    lightColorLoc = glGetUniformLocation(program, "lightColor");
    lightIntensityLoc = glGetUniformLocation(program, "lightIntensity");
    viewerPosLoc = glGetUniformLocation(program, "viewerPos");
    
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(program, "texture2"), 1);
}
