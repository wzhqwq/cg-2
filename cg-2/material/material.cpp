//
//  material.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/27.
//

#include "material.hpp"
#include "shader.hpp"

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
    
    glUniform3fv(shapeShader->ambientLoc, 1, &ambientColor[0]);
    glUniform3fv(shapeShader->diffuseLoc, 1, &diffuseColor[0]);
    glUniform3fv(shapeShader->specularLoc, 1, &specularColor[0]);
    glUniform1f(shapeShader->opacityLoc, opacity);
    glUniform1i(shapeShader->modeLoc, mode);
}

void initMaterials() {
    woodMaterial.texture = textures.wood;
    earthMaterial.texture = textures.earth;
    vaseMaterial.texture = textures.marble;
}
