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

using namespace glm;

int altPressed = 0;
float camDist = 10.0f, camAngle = pi<float>() * -0.1, camHeight = 5.0f;
Scene *mainScene;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(programs.shapeProgram);
    mainScene->render(GL_RENDER);
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
        }
    }
    altPressed = (mods & GLFW_MOD_ALT) != 0;
}

void scrollBallback(GLFWwindow *window, double offsetX, double offsetY) {
    if (altPressed) {
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

    mainScene = new Scene(WIDTH, HEIGHT);
    mainScene->moveTo(vec3(camDist * sin(camAngle), camHeight, camDist * cos(camAngle)));
    initPrograms(argv[1]);
    initTexture(argv[1]);
    initMaterials();
    
    buildRoom(argv[1]);
    
//    glfwSetCursorPosCallback(window, mouseMoveCallback);
//    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollBallback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
