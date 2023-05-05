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
    
    bulb = new Bulb();
    bulb->translate(vec3(0, 6, 0));
    mainScene->objects.push_back(bulb);
        
    toDay();
}

void RoomControl::toDay() {
    sunLight.setLight();
    room->updateLight(sunLight);
    table->updateLight(sunLight);
    bulb->setOff();
}

void RoomControl::toNight() {
    roomLight.setLight();
    room->updateLight(roomLight);
    table->updateLight(roomLight);
    bulb->setOn();
}

Object *RoomControl::getItem(GLenum key) {
    switch (key) {
        case GLFW_KEY_T:
            return table;
        case GLFW_KEY_C:
            return chair;
        case GLFW_KEY_G:
            return globe;
        case GLFW_KEY_V:
            return vase;
        case GLFW_KEY_S:
            return slime;
        default:
            return NULL;
    }
}
