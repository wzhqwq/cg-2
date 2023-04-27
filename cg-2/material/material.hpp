//
//  material.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/27.
//

#ifndef material_hpp
#define material_hpp

#include "common.h"
#include "texture.hpp"

enum RenderMode {
    SingleColor, TexMask, TexPure, TexTest
};

class Material {
public:
    Material() : mode(TexPure) {}
    Material(vec3 currentColor) : color(currentColor), mode(SingleColor) {}
    
    GLuint texture;
    vec3 color;
    RenderMode mode;
    
    void useMaterial();
};

extern Material woodMaterial;
extern Material earthMaterial;
extern Material vaseMaterial;

void initMaterials();

#endif /* material_hpp */
