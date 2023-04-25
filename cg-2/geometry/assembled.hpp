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

#define TABLE_H 1.4f
#define TABLE_TOP_W 2.0f
#define TABLE_TOP_H 0.1f
#define TABLE_LEG_W 0.15f

#define CHAIR_H_1 0.8f
#define CHAIR_H_2 1.8f
#define CHAIR_SIT_SURFACE_W 0.8f
#define CHAIR_SIT_SURFACE_H 0.15f
#define CHAIR_LEG_W 0.1f
#define CHAIR_BACK_W 0.7f
#define CHAIR_BACK_H 0.6f
#define CHAIR_BACK_R -0.2f

#define GLOBE_BOTTOM_W 0.6f
#define GLOBE_BOTTOM_H 0.15f
#define GLOBE_BALL_W 1.0f
#define GLOBE_BALL_R -0.41f
#define GLOBE_BALL_H 0.7f
#define GLOBE_ARC_W 1.2f
#define GLOBE_ARC_T 0.08f
#define GLOBE_ROD_T 0.05f

class Table : public Group {
public:
    Table() : Group() {
        setup();
    }
    float sx = TABLE_TOP_W, sy = TABLE_H + TABLE_TOP_H / 2, sz = TABLE_TOP_W;
private:
    void setup();
};

class Chair : public Group {
public:
    Chair() : Group() {
        setup();
    }
    float sx = CHAIR_SIT_SURFACE_W, sy = CHAIR_H_2 + CHAIR_BACK_H / 2, sz = CHAIR_SIT_SURFACE_W;
private:
    void setup();
};

class Globe : public Group {
public:
    Globe() : Group() {
        setup();
    }
    float sx = GLOBE_ARC_W, sy = GLOBE_BALL_H + GLOBE_ARC_W / 2, sz = GLOBE_ARC_W;
private:
    void setup();
};

#endif /* assembled_hpp */
