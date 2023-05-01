//
//  room.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/23.
//

#include "room.hpp"
#include "common.h"
#include "basic.hpp"
#include "assembled.hpp"
#include "scene.hpp"
#include "outterObject.hpp"
#include "light.hpp"
#include "shadow.hpp"

void buildRoom(string baseUrl) {
    Cube *room = new Cube();
    room->scale(vec3(8, 6, 8));
    room->translate(vec3(0, 3, 0));
    room->material.texture = textures.cubeTest;
    room->material.smoothness = 0.2f;
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
    slime->translate(vec3(2, 0, 0));
    mainScene->objects.push_back(slime);
    
    DirectionalLight sunLight(vec3(-1, -1, 0), vec3(1, 1, 0.9));
    PointLight roomLight(vec3(0, 5, 0), vec3(1, 1, 1));
    roomLight.intensity = 1.0f;
    
    sunLight.setLight();
//    roomLight.setLight();
    
    ShadowPlane *shadowOnTable = new ShadowPlane(sunLight);
    shadowOnTable->scale(vec3(table->sx, 1, table->sz));
    shadowOnTable->translate(vec3(0, table->sy, 0));
    shadowOnTable->casters.push_back(globe);
    shadowOnTable->casters.push_back(vase);
    mainScene->objects.push_back(shadowOnTable);
    
    ShadowPlane *shadowOnFloor = new ShadowPlane(sunLight);
    shadowOnFloor->scale(vec3(8));
    shadowOnFloor->casters.push_back(table);
    shadowOnFloor->casters.push_back(chair);
    shadowOnFloor->casters.push_back(globe);
    shadowOnFloor->casters.push_back(vase);
    shadowOnFloor->casters.push_back(slime);
    mainScene->objects.push_back(shadowOnFloor);
}
