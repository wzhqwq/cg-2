//
//  outterObject.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/26.
//

#include "outterObject.hpp"

void OutterObject::loadFromObj(const char *path) {
    FILE * file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return;
    }
    
    Part *currentPart = NULL;
    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        
        // else : parse lineHeader
        if (strcmp(lineHeader, "v") == 0) {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            frag vertexIndex, uvIndex, normalIndex;
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9){
                printf("Wrong fragment format\n");
                return;
            }
            for (unsigned int i = 0; i < 3; i++) {
                currentPart->addVert(temp_vertices[vertexIndex[i] - 1],
                                     temp_uvs[uvIndex[i] - 1],
                                     temp_normals[normalIndex[i] - 1]);
            }
            // 4-edge face
            matches = fscanf(file, "%d/%d/%d\n",
                             &vertexIndex[1], &uvIndex[1], &normalIndex[1]);
            if (matches == 3) {
                for (int i = 2; i >= 0; i--) {
                    currentPart->addVert(temp_vertices[vertexIndex[i] - 1],
                                         temp_uvs[uvIndex[i] - 1],
                                         temp_normals[normalIndex[i] - 1]);
                }
            }
        }
        else if (strcmp(lineHeader, "mtllib") == 0) {
            char mtlName[100], mtlPath[100];
            fscanf(file, "%s", mtlName);
            strcpy(mtlPath, path);
            long pos = strrchr(path, '/') - path;
            snprintf(mtlPath + pos, 100, "/%s", mtlName);
            loadFromMtl(mtlPath);
        }
        else if (strcmp(lineHeader, "usemtl") == 0) {
            char materialNameC[100];
            fscanf(file, "%s", materialNameC);
            string materialName = materialNameC;
            
            if (currentPart) currentPart->updateBuffer();
            currentPart = new Part();
            currentPart->material = materials[materialName];
            addObject(currentPart);
        }
    }
    if (currentPart) currentPart->updateBuffer();
    
    fclose(file);
}

void OutterObject::loadFromMtl(const char *path) {
    FILE * file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return;
    }
    Material materialNow;
    string materialName = "";
    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        
        if (strcmp(lineHeader, "newmtl") == 0) {
            if (materialName != "") {
                materials[materialName] = materialNow;
                materialNow = Material();
            }
            materialNow.mode = SingleColor;
            char materialNameC[100];
            fscanf(file, "%s", materialNameC);
            materialName = materialNameC;
        }
        else if (strcmp(lineHeader, "Ka") == 0) {
            vec3 color;
            fscanf(file, "%f %f %f\n", &color.r, &color.g, &color.b);
            materialNow.ambientColor = color;
        }
        else if (strcmp(lineHeader, "Kd") == 0) {
            vec3 color;
            fscanf(file, "%f %f %f\n", &color.r, &color.g, &color.b);
            materialNow.diffuseColor = color;
        }
        else if (strcmp(lineHeader, "Ks") == 0) {
            vec3 color;
            fscanf(file, "%f %f %f\n", &color.r, &color.g, &color.b);
            materialNow.specularColor = color;
        }
        else if (strcmp(lineHeader, "d") == 0) {
            float opacity;
            fscanf(file, "%f\n", &opacity);
            materialNow.opacity = opacity;
            if (1.0f - opacity > 1e-3f) {
                materialNow.translucent = 1;
            }
        }
        else if (strcmp(lineHeader, "Ns") == 0) {
            float shininess;
            fscanf(file, "%f\n", &shininess);
            materialNow.shininess = shininess;
        }
    }
    if (materialName != "") {
        materials[materialName] = materialNow;
    }
    
    fclose(file);
}
