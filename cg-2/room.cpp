//
//  room.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/23.
//

#include "room.hpp"

void buildRoom(string baseUrl) {
    Cube *room = new Cube();
    room->scale(vec3(10));
    room->translate(vec3(0, 5, 0));
    room->material.texture = textures.cubeTest;
    room->reverse();
    mainScene->objects.push_back(room);
    
    Table *table = new Table();
    mainScene->objects.push_back(table);
    
    Chair *chair = new Chair();
    chair->translate(vec3(0, 0, -1.5));
    mainScene->objects.push_back(chair);
    
    Globe *globe = new Globe();
    globe->translate(vec3(0.4f, table->sy, 0));
    mainScene->objects.push_back(globe);
    
    Vase *vase = new Vase(15, 6);
    vase->scale(vec3(0.8f));
    vase->translate(vec3(-0.6f, table->sy, 0));
    vase->material = vaseMaterial;
    mainScene->objects.push_back(vase);
    
    OutterObject *slime = new OutterObject(baseUrl + "/object/Slime.obj");
    slime->material.mode = TexTest;
    mainScene->objects.push_back(slime);
}
