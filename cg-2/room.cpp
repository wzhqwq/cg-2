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
    
    Globe *globe = new Globe();
    globe->translate(vec3(0, table->sy, 0));
    mainScene->objects.push_back(globe);
}
