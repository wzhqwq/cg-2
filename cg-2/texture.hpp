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

struct Textures {
    GLuint selection, move, magnifier, cameraRotate, cubeTest, wood, earth, chessboard, marble;
};

GLuint loadTexture(const char *textureUrl, const char *fileName);
void initTexture(const char *textureUrl);

extern Textures textures;

#endif /* texture_hpp */
