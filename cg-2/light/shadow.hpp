//
//  shadow.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/29.
//

#ifndef shadow_hpp
#define shadow_hpp

#include "common.h"
#include "geometry.hpp"
#include "light.hpp"
#include <vector>

class ShadowPlane : public Geometry {
public:
    ShadowPlane() {
        setup();
        updateBuffer();
    }
    void paint();
    void updateLight(Light light);
    void applyTransformation(mat4 matrix);
    
    vector<Object *> casters;
private:
    void setup();
    void updateShadowMatrix();
    
    mat4 shadowMatrix;
    vec4 lightPosDir;
    vec4 plane = vec4(0, 1, 0, 0);
};

#endif /* shadow_hpp */
