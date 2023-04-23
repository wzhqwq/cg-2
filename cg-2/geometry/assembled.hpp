//
//  assembled.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#ifndef assembled_hpp
#define assembled_hpp

#include "common.h"
#include "geometry.hpp"
#include "basic.hpp"
#include "texture.hpp"

#define TABLE_H 1.4
#define TABLE_TOP_W 2
#define TABLE_TOP_H 0.1
#define TABLE_LEG_W 0.15

#define CHAIR_H_1 0.8
#define CHAIR_H_2 1.5
#define CHAIR_SIT_SURFACE_W 0.8
#define CHAIR_SIT_SURFACE_H 0.15
#define CHAIR_LEG_W 0.1
#define CHAIR_BACK_W 0.7
#define CHAIR_BACK_H 0.6
#define CHAIR_BACK_R -0.2

class Table : public Group {
public:
    Table() : Group() {
        setup();
    }
    void setup();
};

class Chair : public Group {
public:
    Chair() : Group() {
        setup();
    }
    void setup();
};

#endif /* assembled_hpp */
