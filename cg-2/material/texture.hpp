//
//  texture.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#ifndef texture_hpp
#define texture_hpp

#include "stb_image.h"
#include "common.h"
#include <string>

using namespace std;

struct Textures {
    GLuint selection, move, magnifier, cameraRotate;
    GLuint cubeTest, wood, earth, chessboard, marble, wood1;
    GLuint floor, floorNM, wall, wallNM;
};

GLuint loadTexture(string path);
void initTexture(string basePath);

extern Textures textures;

#endif /* texture_hpp */
