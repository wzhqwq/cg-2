//
//  shaderReader.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/20.
//

#ifndef shaderReader_hpp
#define shaderReader_hpp

#include "common.h"

char *readFromFile(const char *fileName);
void loadVertexShader(const char *path, GLuint program);
void loadFragmentShader(const char *path, GLuint program);

#endif /* shaderReader_hpp */
