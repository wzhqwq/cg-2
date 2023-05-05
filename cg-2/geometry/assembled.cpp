//
//  assembled.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "assembled.hpp"

void Table::setup() {
    Cube *top = new Cube();
    Cylinder *leg1 = new Cylinder(8, 8), *leg2 = new Cylinder(8, 8);
    Cylinder *leg3 = new Cylinder(8, 8), *leg4 = new Cylinder(8, 8);
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
    
    shadowTop = new ShadowPlane();
    shadowTop->scale(vec3(sx, 1, sz));
    shadowTop->translate(vec3(0, sy, 0));
    addObject(shadowTop);
}
void Table::putOnObject(Object *obj) {
    addObject(obj);
    shadowTop->casters.push_back(obj);
}
void Table::updateLight(Light light) {
    shadowTop->updateLight(light);
}

void Chair::setup() {
    Cube *top = new Cube();
    Cylinder *leg1 = new Cylinder(8, 4), *leg2 = new Cylinder(8, 4);
    Cylinder *leg3 = new Cylinder(8, 4), *leg4 = new Cylinder(8, 4);
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

void Room::setup() {
//    Cube *cube = new Cube();
//    cube->scale(vec3(w, h, w));
//    cube->translate(vec3(0, h / 2, 0));
//    cube->material.texture = textures.cubeTest;
//    cube->material.smoothness = 0.2f;
//    cube->reverse();
//    addObject(cube);
    Plane *floor = new Plane(w / 2, w / 2);
    floor->scale(vec3(w, w, 1));
    floor->rotate(-r90, vec3(1, 0, 0));
    floor->material = floorMaterial;
    addObject(floor);
    
    Plane *wall1 = new Plane(w, h), *wall2 = new Plane(w, h);
    Plane *wall3 = new Plane(w, h), *wall4 = new Plane(w, h);
    wall1->scale(vec3(w, h, 1));
    wall2->scale(vec3(w, h, 1));
    wall3->scale(vec3(w, h, 1));
    wall4->scale(vec3(w, h, 1));
    wall2->rotate(r180, vec3(0, 1, 0));
    wall3->rotate(-r90, vec3(0, 1, 0));
    wall4->rotate(r90, vec3(0, 1, 0));
    wall1->translate(vec3(0, h / 2, -w / 2));
    wall2->translate(vec3(0, h / 2, w / 2));
    wall3->translate(vec3(w / 2, h / 2, 0));
    wall4->translate(vec3(-w / 2, h / 2, 0));
    wall1->material = wall2->material = wall3->material = wall4->material = wallMaterial;
    addObject(wall1);
    addObject(wall2);
    addObject(wall3);
    addObject(wall4);
    
    ShadowPlane *bottom = new ShadowPlane();
    bottom->scale(vec3(w, 1, w));
    addObject(bottom);
    shadowPlanes.push_back(bottom);
}
void Room::putInObject(Object *obj) {
    addObject(obj);
    for (auto plane : shadowPlanes) {
        plane->casters.push_back(obj);
    }
}
void Room::updateLight(Light light) {
    for (auto plane : shadowPlanes) {
        plane->updateLight(light);
    }
}

void Bulb::setup() {
    head = new Sphere(10, 10);
    head->scale(vec3(0.4f));
    Cylinder *tail = new Cylinder(10);
    tail->scale(vec3(0.2f));
    tail->translate(vec3(0, 0.2f, 0));
    tail->material = Material(vec3(1));
    
    addObject(head);
    addObject(tail);
}
void Bulb::setOff() {
    head->material = unlitBulbOffMaterial;
}
void Bulb::setOn() {
    head->material = unlitBulbOnMaterial;
}

void Arrow::setup(float length) {
    body = new Cylinder(10);
    body->scale(vec3(0.05f, length, 0.05f));
    body->translate(vec3(0, length / 2, 0));
    body->material = Material(vec3(1));
    body->material.mode = UnlitSingleColor;

    head = new Cone(10);
    head->scale(vec3(0.2f));
    head->translate(vec3(0, length, 0));
    head->material = Material(vec3(1));
    head->material.mode = UnlitSingleColor;
    
    addObject(body);
    addObject(head);
}
void Arrow::setColor(vec3 color) {
    body->material.diffuseColor = color;
    head->material.diffuseColor = color;
}
void Arrow::setOpacity(float opacity) {
    if (1.0f - opacity > 1e-3f) {
        body->material.translucent = 1;
        head->material.translucent = 1;
    }
    body->material.opacity = opacity;
    head->material.opacity = opacity;
}
