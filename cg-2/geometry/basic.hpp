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
#include "bezier.hpp"

class Cube : public Geometry {
public:
    Cube() {
        setup();
        updateBuffer();
    }
private:
    void setup();
};

class Sphere : public Geometry {
public:
    Sphere(int slices, int stacks) {
        setup(slices, stacks);
        updateBuffer();
    }
private:
    void setup(int slices, int stacks);
};

class Cylinder : public Geometry {
public:
    Cylinder(int slices) : Cylinder(slices, 1) {}
    Cylinder(int slices, int stacks) {
        setup(slices, stacks);
        updateBuffer();
    }
private:
    void setup(int slices, int stacks);
};

class Cone : public Geometry {
public:
    Cone(int slices) : Cone(slices, 1) {}
    Cone(int slices, int stacks) {
        setup(slices, stacks);
        updateBuffer();
    }
private:
    void setup(int slices, int stacks);
};

class Ring : public Geometry {
public:
    Ring(int slices, int stacks, float inset) : Ring(slices, stacks, inset, 0, 360) {}
    Ring(int slices, int stacks, float inset, float startAngle, float endAngle) {
        setup(slices, stacks, inset, startAngle * pi<float>() / 180, endAngle * pi<float>() / 180);
        updateBuffer();
    }
private:
    void setup(int cSub, int aSub, float inset, float start, float end);
};

class Vase : public Geometry {
public:
    Vase(int slices, int stacks) {
        setup(slices, stacks);
        updateBuffer();
    }
private:
    void setup(int slices, int stacks);
};

#endif /* basic_hpp */
