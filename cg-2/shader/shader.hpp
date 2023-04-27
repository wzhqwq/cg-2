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
#include <string>

using namespace std;

struct Programs {
    GLuint shapeProgram;
    GLuint fixedProgram;
};

GLuint loadProgram(string vert, string frag);
void initPrograms(string basePath);

extern Programs programs;

#endif /* shader_hpp */
