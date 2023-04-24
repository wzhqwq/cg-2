//
//  room.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/23.
//

#include "room.hpp"

void buildRoom() {
    Cube *room = new Cube();
    room->scale(vec3(10));
    room->translate(vec3(0, 5, 0));
    room->renderMode = TexPure;
    room->texture = textures.cubeTest;
    room->reverse();
    mainScene->objects.push_back(room);
    
    Table *table = new Table();
    mainScene->objects.push_back(table);
    
    Chair *chair = new Chair();
    chair->translate(vec3(0, 0, -1.5));
    mainScene->objects.push_back(chair);
    
    Sphere *ball = new Sphere(20, 10);
    ball->scale(vec3(4));
    ball->translate(vec3(0, 5, 0));
    ball->renderMode = TexPure;
    ball->texture = textures.earth;
    mainScene->objects.push_back(ball);
}
