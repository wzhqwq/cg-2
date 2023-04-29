//
//  light.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/28.
//

#include "light.hpp"
#include "shader.hpp"

void Light::setLight() {
    glUniform4fv(shapeShader->lightPosLoc, 1, &position[0]);
    glUniform3fv(shapeShader->lightColorLoc, 1, &color[0]);
    glUniform1f(shapeShader->lightIntensityLoc, intensity);
}

void Light::setIntensity(float _intensity) {
    intensity = _intensity;
    glUniform1f(shapeShader->lightIntensityLoc, intensity);
}
