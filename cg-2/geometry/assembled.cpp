//
//  assembled.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "assembled.hpp"

void Table::setup() {
    Cube *top = new Cube();
    Cylinder *leg1 = new Cylinder(8), *leg2 = new Cylinder(8), *leg3 = new Cylinder(8), *leg4 = new Cylinder(8);
    top->material = leg1->material = leg2->material = leg3->material = leg4->material = woodMaterial;
    
    top->scale(vec3(TABLE_TOP_W, TABLE_TOP_H, TABLE_TOP_W));
    leg1->scale(vec3(TABLE_LEG_W, TABLE_H, TABLE_LEG_W));
    leg2->scale(vec3(TABLE_LEG_W, TABLE_H, TABLE_LEG_W));
    leg3->scale(vec3(TABLE_LEG_W, TABLE_H, TABLE_LEG_W));
    leg4->scale(vec3(TABLE_LEG_W, TABLE_H, TABLE_LEG_W));
    
    top->translate(vec3(0, TABLE_H, 0));
    leg1->translate(vec3((TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2, TABLE_H / 2, (TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2));
    leg2->translate(vec3((TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2, TABLE_H / 2, -(TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2));
    leg3->translate(vec3(-(TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2, TABLE_H / 2, (TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2));
    leg4->translate(vec3(-(TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2, TABLE_H / 2, -(TABLE_TOP_W - TABLE_LEG_W - 0.01) / 2));
    
    addObject(top);
    addObject(leg1);
    addObject(leg2);
    addObject(leg3);
    addObject(leg4);
}

void Chair::setup() {
    Cube *top = new Cube();
    Cylinder *leg1 = new Cylinder(8), *leg2 = new Cylinder(8), *leg3 = new Cylinder(8), *leg4 = new Cylinder(8);
    top->material = leg1->material = leg2->material = leg3->material = leg4->material = woodMaterial;
    
    top->scale(vec3(CHAIR_SIT_SURFACE_W, CHAIR_SIT_SURFACE_H, CHAIR_SIT_SURFACE_W));
    leg1->scale(vec3(CHAIR_LEG_W, CHAIR_H_1, CHAIR_LEG_W));
    leg2->scale(vec3(CHAIR_LEG_W, CHAIR_H_1, CHAIR_LEG_W));
    leg3->scale(vec3(CHAIR_LEG_W, CHAIR_H_1, CHAIR_LEG_W));
    leg4->scale(vec3(CHAIR_LEG_W, CHAIR_H_1, CHAIR_LEG_W));
    
    top->translate(vec3(0, CHAIR_H_1, 0));
    leg1->translate(vec3((CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2, CHAIR_H_1 / 2, (CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2));
    leg2->translate(vec3((CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2, CHAIR_H_1 / 2, -(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2));
    leg3->translate(vec3(-(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2, CHAIR_H_1 / 2, (CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2));
    leg4->translate(vec3(-(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2, CHAIR_H_1 / 2, -(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W - 0.01) / 2));
    
    addObject(top);
    addObject(leg1);
    addObject(leg2);
    addObject(leg3);
    addObject(leg4);
    
    Cube *back = new Cube();
    Cylinder *rod1 = new Cylinder(8), *rod2 = new Cylinder(8);
    back->material = rod1->material = rod2->material = woodMaterial;

    back->scale(vec3(CHAIR_BACK_W, CHAIR_BACK_H, CHAIR_SIT_SURFACE_H));
    rod1->scale(vec3(CHAIR_LEG_W, (CHAIR_H_2 - CHAIR_H_1), CHAIR_LEG_W));
    rod2->scale(vec3(CHAIR_LEG_W, (CHAIR_H_2 - CHAIR_H_1), CHAIR_LEG_W));
    
    back->rotate(CHAIR_BACK_R, vec3(1, 0, 0));
    rod1->rotate(CHAIR_BACK_R, vec3(1, 0, 0));
    rod2->rotate(CHAIR_BACK_R, vec3(1, 0, 0));

    back->translate(vec3(0, CHAIR_H_2, -(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W) / 2));
    rod1->translate(vec3((CHAIR_SIT_SURFACE_W - CHAIR_LEG_W) / 3,
                         (CHAIR_H_1 + CHAIR_H_2) / 2,
                         -(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W) / 2));
    rod2->translate(vec3(-(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W) / 3,
                         (CHAIR_H_1 + CHAIR_H_2) / 2,
                         -(CHAIR_SIT_SURFACE_W - CHAIR_LEG_W) / 2));

    addObject(back);
    addObject(rod1);
    addObject(rod2);
}

void Globe::setup() {
    Sphere *ball = new Sphere(20, 20);
    ball->scale(vec3(GLOBE_BALL_W));
    ball->rotate(GLOBE_BALL_R, vec3(0, 0, 1));
    ball->translate(vec3(0, GLOBE_BALL_H, 0));
    ball->material = earthMaterial;
    
    Cone *bottom = new Cone(15);
    bottom->scale(vec3(GLOBE_BOTTOM_W, GLOBE_BOTTOM_H, GLOBE_BOTTOM_W));
    bottom->material = vec3(0.2, 0.2, 0.2);
    
    Ring *arc = new Ring(10, 15, 1.0f - (GLOBE_ARC_T * 2) / GLOBE_ARC_W, -90.0f, 90.0f);
    arc->scale(vec3(GLOBE_ARC_W));
    arc->rotate(pi<float>() / 2, vec3(1, 0, 0));
    arc->rotate(GLOBE_BALL_R, vec3(0, 0, 1));
    arc->translate(vec3(0, GLOBE_BALL_H, 0));
    arc->material = vec3(0.1, 0.1, 0.1);

    
    Cylinder *rod = new Cylinder(15);
    rod->scale(vec3(GLOBE_ROD_T, GLOBE_ARC_W, GLOBE_ROD_T));
    rod->rotate(GLOBE_BALL_R, vec3(0, 0, 1));
    rod->translate(vec3(0, GLOBE_BALL_H, 0));
    rod->material = vec3(0.1, 0.1, 0.1);
    
    addObject(ball);
    addObject(bottom);
    addObject(arc);
    addObject(rod);
}
