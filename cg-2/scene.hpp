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
#include "shader.hpp"

#include <vector>

class Scene {
public:
    Scene(int _w, int _h): w(_w), h(_h) {
        glViewport(0, 0, _w, _h);
        projection = perspective(45.0f, (float) w / h, 0.1f, 1000.0f);
        view = lookAt(currentPos, vec3(0, currentPos.y, 0), vec3(0, 1, 0));
        glUseProgram(shapeShader->program);
        glUniformMatrix4fv(shapeShader->projectionLoc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(shapeShader->viewLoc, 1, GL_FALSE, &view[0][0]);
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
    mat4 view;
    
    vec3 currentPos = vec3(100, 10, 0);
    
    int w, h;
};

extern Scene *mainScene;

#endif /* scene_hpp */
