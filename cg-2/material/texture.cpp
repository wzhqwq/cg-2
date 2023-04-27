//
//  texture.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#include "texture.hpp"

Textures textures;

GLuint loadTexture(string path) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (!data) return 0;
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    return texture;
}

void initTexture(string basePath) {
    basePath += "/texture/";
    textures.selection = loadTexture(basePath + "selection.png");
    textures.cameraRotate = loadTexture(basePath + "camera_rotate.png");
    textures.magnifier = loadTexture(basePath + "magnify.png");
    textures.move = loadTexture(basePath + "move.png");
    textures.cubeTest = loadTexture(basePath + "cube_test.png");
    textures.wood = loadTexture(basePath + "wood.jpg");
    textures.earth = loadTexture(basePath + "earth.jpg");
    textures.chessboard = loadTexture(basePath + "chessboard.jpg");
    textures.marble = loadTexture(basePath + "marble.jpg");
}
