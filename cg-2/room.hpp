//
//  room.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/23.
//

#ifndef room_hpp
#define room_hpp

#include <string>
#include "common.h"
#include "basic.hpp"
#include "assembled.hpp"
#include "light.hpp"
#include "outterObject.hpp"

using namespace std;

class RoomControl {
public:
    void buildRoom(string baseUrl);
    void toDay();
    void toNight();
    Object *getItem(GLenum key);
private:
    Room *room;
    Table *table;
    Chair *chair;
    Vase *vase;
    Globe *globe;
    OutterObject *slime;
    Bulb *bulb;
    
    DirectionalLight sunLight = DirectionalLight(vec3(-1, -1, -0.2), vec3(1, 1, 0.9));
    PointLight roomLight = PointLight(vec3(0, 5, 0), vec3(0.9, 0.9, 0.6));
};

#endif /* room_hpp */
