//
//  basic.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#ifndef basic_hpp
#define basic_hpp

#include "common.h"
#include "geometry.hpp"

class Cube : public Geometry {
public:
    Cube() : Geometry() {
        vertices.resize(28);
        indices.resize(12);
        setup();
        updateBuffer();
    }
private:
    void setup();
};

class Vase : public Geometry {
public:
    Vase() : Geometry() {
        setup();
        updateBuffer();
    }
private:
    void setup();
};

#endif /* basic_hpp */
