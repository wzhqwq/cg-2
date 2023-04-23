//
//  assembled.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "assembled.hpp"

void Table::setup() {
    Cube *top = new Cube(), *leg1 = new Cube(), *leg2 = new Cube(), *leg3 = new Cube(), *leg4 = new Cube();
    top->texture = textures.wood;
    top->renderMode = TexPure;
    leg1->texture = textures.wood;
    leg1->renderMode = TexPure;
    leg2->texture = textures.wood;
    leg2->renderMode = TexPure;
    leg3->texture = textures.wood;
    leg3->renderMode = TexPure;
    leg4->texture = textures.wood;
    leg4->renderMode = TexPure;
    
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
    Cube *top = new Cube(), *leg1 = new Cube(), *leg2 = new Cube(), *leg3 = new Cube(), *leg4 = new Cube();
    top->texture = textures.wood;
    top->renderMode = TexPure;
    leg1->texture = textures.wood;
    leg1->renderMode = TexPure;
    leg2->texture = textures.wood;
    leg2->renderMode = TexPure;
    leg3->texture = textures.wood;
    leg3->renderMode = TexPure;
    leg4->texture = textures.wood;
    leg4->renderMode = TexPure;
    
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
    
    Cube *back = new Cube(), *rod1 = new Cube(), *rod2 = new Cube();
    back->texture = textures.wood;
    back->renderMode = TexPure;
    rod1->texture = textures.wood;
    rod1->renderMode = TexPure;
    rod2->texture = textures.wood;
    rod2->renderMode = TexPure;

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
