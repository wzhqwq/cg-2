//
//  geoControl.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/20.
//

#include "geoControl.hpp"

void GeoControl::setup() {
    tx = new Arrow(1.0f);
    tx->rotate(-r90, vec3(0, 0, 1));
    ty = new Arrow(1.0f);
    tz = new Arrow(1.0f);
    tz->rotate(r90, vec3(1, 0, 0));
    toggle(0);
}

void GeoControl::toggle(int id) {
    switch (id) {
        case 0:
            tx->setColor(vec3(1, 0, 0));
            ty->setColor(vec3(0.4f, 0.5f, 0.4f));
            tz->setColor(vec3(0.4f, 0.4f, 0.5f));
            break;
        case 1:
            tx->setColor(vec3(0.5f, 0.4f, 0.4f));
            ty->setColor(vec3(0, 1, 0));
            tz->setColor(vec3(0.4f, 0.4f, 0.5f));
            break;
        case 2:
            tx->setColor(vec3(0.5f, 0.4f, 0.4f));
            ty->setColor(vec3(0.4f, 0.5f, 0.4f));
            tz->setColor(vec3(0, 0, 1));
            break;
            
        default:
            break;
    }
    controlId = id;
}

void GeoControl::paint() {
    if (!selectedItem) return;
    glDisable(GL_DEPTH_TEST);
    tx->setOpacity(0.5f);
    ty->setOpacity(0.5f);
    tz->setOpacity(0.5f);
    tx->paint();
    ty->paint();
    tz->paint();
    glEnable(GL_DEPTH_TEST);
    tx->setOpacity(1);
    ty->setOpacity(1);
    tz->setOpacity(1);
    tx->paint();
    ty->paint();
    tz->paint();
}

void GeoControl::applyTransformation(mat4 matrix) {
    tx->applyTransformation(matrix);
    ty->applyTransformation(matrix);
    tz->applyTransformation(matrix);
}

void GeoControl::select(Object *obj) {
    if (!obj) return;
    selectedItem = obj;
    translate(obj->getTranslation() - getTranslation());
}

void GeoControl::hide() {
    selectedItem = NULL;
}

void GeoControl::move(float delta) {
    if (!selectedItem) return;
    switch (controlId) {
        case 0:
            selectedItem->translate(vec3(delta, 0, 0));
            translate(vec3(delta, 0, 0));
            break;
        case 1:
            selectedItem->translate(vec3(0, delta, 0));
            translate(vec3(0, delta, 0));
            break;
        case 2:
            selectedItem->translate(vec3(0, 0, delta));
            translate(vec3(0, 0, delta));
            break;
            
        default:
            break;
    }
}

