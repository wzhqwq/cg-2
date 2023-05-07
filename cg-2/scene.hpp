//
//  scene.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#ifndef scene_hpp
#define scene_hpp

#include "common.h"
#include "geometry.hpp"
#include "selection.hpp"

#include <vector>

class Scene {
public:
    Scene(int _w, int _h): w(_w), h(_h) {
        glViewport(0, 0, _w, _h);
        projection = perspective(45.0f, (float) w / h, 0.1f, 1000.0f);
    }
    
    void moveTo(vec3 p);
    
    void render();
    
    vector<Object*> objects;
    vec3 currentColor = vec3(1.0f, 0.0f, 0.0f);
    DrawMode currentDrawMode = Filled;
    Geometry *selectedItem = NULL;
    SelectionRect *selectionRect = NULL;
private:
    void updateVPMatrix();
    
    mat4 projection;
    int w, h;
};

extern Scene *mainScene;

#endif /* scene_hpp */
