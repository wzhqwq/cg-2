//
//  geoControl.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/20.
//

#ifndef geoControl_hpp
#define geoControl_hpp

#include "common.h"
#include "geometry.hpp"
#include "assembled.hpp"

class GeoControl : public Object {
public:
    GeoControl() {
        setup();
    }
    
    void select(Object *obj);
    void toggle(int id);
    void hide();
    void move(float delta);
    
    void paint();
    void applyTransformation(mat4 matrix);
private:
    void setup();
    
    Object *selectedItem = NULL;
    Arrow *tx, *ty, *tz;
    int controlId = 0;
};

#endif /* geoControl_hpp */
