//
//  main.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/17.
//

#include "common.h"
#include "shader.hpp"
#include "scene.hpp"
#include "texture.hpp"
#include "room.hpp"
#include "material.hpp"
#include "geoControl.hpp"

using namespace glm;

int altPressing = 0, shiftPressing = 0;
float camDist = 10.0f, camAngle = pi<float>() * -0.1, camHeight = 5.0f;
Scene *mainScene;
RoomControl *room;
GeoControl *control;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(shapeShader->program);
    mainScene->render();
    if (mainScene->selectionRect && mainScene->selectedItem) {
        mainScene->selectionRect->drawSelf();
    }
}

//void mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
//    int left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
//    int right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
//}
//
//void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
//    double x, y;
//    glfwGetCursorPos(window, &x, &y);
//}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_D:
                room->toDay();
                break;
            case GLFW_KEY_N:
                room->toNight();
                break;
            case GLFW_KEY_X:
                control->toggle(0);
                break;
            case GLFW_KEY_Y:
                control->toggle(1);
                break;
            case GLFW_KEY_Z:
                control->toggle(2);
                break;
            case GLFW_KEY_ESCAPE:
                control->hide();
                break;
            default:
                control->select(room->getItem(key));
                break;
        }
    }
    altPressing = (mods & GLFW_MOD_ALT) != 0;
    shiftPressing = (mods & GLFW_MOD_SHIFT) != 0;
}

void scrollCallback(GLFWwindow *window, double offsetX, double offsetY) {
    if (shiftPressing) {
        control->move(-offsetY * 0.1f);
        return;
    }
    if (altPressing) {
        camDist = glm::max(1.0f, (float)(camDist - offsetY * 0.1f));
    }
    else {
        camAngle -= offsetX * 0.02f;
        camHeight += offsetY * 0.1f;
    }
    mainScene->moveTo(vec3(camDist * sin(camAngle), camHeight, camDist * cos(camAngle)));
}

int main(int argc, char * argv[]) {
#ifdef TEST_BOUNDING
    printf("Bounding test enabled\n");
#endif
    if (!glfwInit()) {
        printf("GLFW Initialization Failed.\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "experiment 2", NULL, NULL);
    if (!window) {
        printf("Window Creation Failed.\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW Initialization Failed.\n");
        return -1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    initPrograms(argv[1]);
    initTexture(argv[1]);
    initMaterials();
    
    mainScene = new Scene(WIDTH, HEIGHT);
    mainScene->moveTo(vec3(camDist * sin(camAngle), camHeight, camDist * cos(camAngle)));

    room = new RoomControl();
    room->buildRoom(argv[1]);
    control = new GeoControl();
    mainScene->objects.push_back(control);
    
//    glfwSetCursorPosCallback(window, mouseMoveCallback);
//    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
