//
//  material.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/27.
//

#include "material.hpp"

Material woodMaterial;
Material earthMaterial;
Material vaseMaterial;

void Material::useMaterial() {
    if (mode != SingleColor) glBindTexture(GL_TEXTURE_2D, texture);
    
    glVertexAttrib3fv(2, &color[0]);
    glVertexAttribI1i(3, mode);
}

void initMaterials() {
    woodMaterial.texture = textures.wood;
    earthMaterial.texture = textures.earth;
    vaseMaterial.texture = textures.marble;
}
