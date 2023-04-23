//
//  shader.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#ifndef shader_hpp
#define shader_hpp

#include "common.h"
#include "shaderReader.hpp"

struct Programs {
    GLuint shapeProgram;
    GLuint fixedProgram;
};

GLuint loadProgram(const char *shaderDir, const char *vert, const char *frag);
void initPrograms(const char *shaderDir);

extern Programs programs;

#endif /* shader_hpp */
