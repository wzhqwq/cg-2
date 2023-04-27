//
//  outterObject.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/26.
//

#include "outterObject.hpp"

void OutterObject::loadFromObj(const char *path) {
    FILE * file = fopen(path, "r");
    if(file == NULL) {
        printf("Impossible to open the file !\n");
        return;
    }
    
    vector<frag> vertexIndices, uvIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;
    while(1){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        
        // else : parse lineHeader
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            frag vertexIndex, uvIndex, normalIndex;
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9){
                printf("Wrong fragment format\n");
                return;
            }
            vertexIndices.push_back(vertexIndex);
            uvIndices.push_back(uvIndex);
            normalIndices.push_back(normalIndex);
            // 4-edge face
            matches = fscanf(file, "%d/%d/%d\n",
                             &vertexIndex[1], &uvIndex[1], &normalIndex[1]);
            if (matches == 3) {
                vertexIndices.push_back(vec3(vertexIndex.z, vertexIndex.y, vertexIndex.x));
                uvIndices.push_back(vec3(uvIndex.z, uvIndex.y, uvIndex.x));
                normalIndices.push_back(vec3(normalIndex.z, normalIndex.y, normalIndex.x));
            }
        }
    }
    for(unsigned int i = 0; i < vertexIndices.size(); i++) {
        for (unsigned int j = 0; j < 3; j++) {
            addVert(temp_vertices[vertexIndices[i][j] - 1],
                    temp_uvs[uvIndices[i][j] - 1],
                    temp_normals[normalIndices[i][j] - 1]);
        }
    }
}
