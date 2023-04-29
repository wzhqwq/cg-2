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

class ShapeShader {
public:
    ShapeShader(string basePath);
    
    GLuint program;
    GLuint modelLoc, viewLoc, projectionLoc, modeLoc;
    GLuint ambientLoc, diffuseLoc, specularLoc;
    GLuint materialCoefficientsLoc;
    GLuint lightPosLoc, lightColorLoc, lightIntensityLoc;
};

GLuint loadProgram(string vert, string frag);
void initPrograms(string basePath);

extern ShapeShader *shapeShader;

#endif /* shader_hpp */
