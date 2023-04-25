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
        setup();
        updateBuffer();
    }
private:
    void setup();
};

class Sphere : public Geometry {
public:
    Sphere(int rotateSubdivision, int axisSubdivision) : Geometry() {
        setup(rotateSubdivision, axisSubdivision);
        updateBuffer();
    }
private:
    void setup(int rSub, int aSub);
};

class Cylinder : public Geometry {
public:
    Cylinder(int subdivision) : Geometry() {
        setup(subdivision);
        updateBuffer();
    }
private:
    void setup(int sub);
};

class Cone : public Geometry {
public:
    Cone(int subdivision) : Geometry() {
        setup(subdivision);
        updateBuffer();
    }
private:
    void setup(int sub);
};

class Ring : public Geometry {
public:
    Ring(int circleSubdivision, int arcSubdivision, float inset) : Ring(circleSubdivision, arcSubdivision, inset, 0, 360) {};
    Ring(int circleSubdivision, int arcSubdivision, float inset, float startAngle, float endAngle) {
        setup(circleSubdivision, arcSubdivision, inset, startAngle * pi<float>() / 180, endAngle * pi<float>() / 180);
        updateBuffer();
    }
private:
    void setup(int cSub, int aSub, float inset, float start, float end);
};

class Vase : public Geometry {
public:
    Vase(int subdivision) : Geometry() {
        setup();
        updateBuffer();
    }
private:
    void setup();
};

#endif /* basic_hpp */
