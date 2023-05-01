//
//  light.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/28.
//

#ifndef light_hpp
#define light_hpp

#include "common.h"

enum LightType {
    Directional, Point
};

class Light {
public:
    Light(vec4 p, vec3 c) : position(p), color(c) {}
    
    void setLight();
    void setIntensity(float _intensity);
    
    // position for point light, direction for directional light
    vec4 position;
    // rgba
    vec3 color;
    float intensity = 1.0f;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(vec3 dir, vec3 c) : Light(vec4(normalize(dir), 0), c) {}
};

class PointLight : public Light {
public:
    PointLight(vec3 pos, vec3 c) : Light(vec4(pos, 1), c) {}
};

#endif /* light_hpp */
