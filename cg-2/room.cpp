//
//  room.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/23.
//

#include "room.hpp"
#include "scene.hpp"
#include "shadow.hpp"


void RoomControl::buildRoom(string baseUrl) {
    room = new Room(8, 6);
    mainScene->objects.push_back(room);
    
    table = new Table();
    room->putInObject(table);
    
    chair = new Chair();
    chair->translate(vec3(0, 0, -1.5));
    room->putInObject(chair);
    
    globe = new Globe();
    globe->translate(vec3(0, table->sy, -0.4f));
    table->putOnObject(globe);
    
    vase = new Vase(15, 6);
    vase->scale(vec3(0.8f));
    vase->translate(vec3(-0.2f, table->sy, 0.6f));
    vase->material = vaseMaterial;
    table->putOnObject(vase);
    
    slime = new OutterObject(baseUrl + "/object/Slime.obj");
    slime->translate(vec3(2, 0, 0));
    room->putInObject(slime);
    
//    roomLight.intensity = 1.5f;
//    room->translate(vec3(0, -5, 0));
    toDay();
}

void RoomControl::toDay() {
    sunLight.setLight();
    room->updateLight(sunLight);
    table->updateLight(sunLight);
}

void RoomControl::toNight() {
    roomLight.setLight();
    room->updateLight(roomLight);
    table->updateLight(roomLight);
}
