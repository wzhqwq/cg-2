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
    
    if (translucent) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else {
        glDisable(GL_BLEND);
    }
    
    glVertexAttrib3fv(2, &ambientColor[0]);
    glVertexAttrib3fv(3, &diffuseColor[0]);
    glVertexAttrib3fv(4, &specularColor[0]);
    glVertexAttrib1f(5, opacity);
    glVertexAttribI1i(6, mode);
}

void initMaterials() {
    woodMaterial.texture = textures.wood;
    earthMaterial.texture = textures.earth;
    vaseMaterial.texture = textures.marble;
}
