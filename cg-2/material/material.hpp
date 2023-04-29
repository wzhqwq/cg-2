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
    Material(vec3 color) : diffuseColor(color), mode(SingleColor) {}
    
    GLuint texture;
    vec3 ambientColor = vec3(1, 1, 1);
    vec3 diffuseColor;
    vec3 specularColor = vec3(0.5f, 0.5f, 0.5f);
    float opacity = 1.0f;
    float shininess = 50.0f;
    float smoothness = 1.0f;
    int translucent = 0;
    RenderMode mode;
    
    void useMaterial();
};

extern Material woodMaterial;
extern Material earthMaterial;
extern Material vaseMaterial;

void initMaterials();

#endif /* material_hpp */
