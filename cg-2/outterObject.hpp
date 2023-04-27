//
//  outterObject.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/26.
//

#ifndef outterObject_hpp
#define outterObject_hpp

#include "common.h"
#include "geometry.hpp"
#include <string>
#include <map>

using namespace std;

class OutterObject : public Group {
public:
    OutterObject(string path) {
        loadFromObj(path.c_str());
    }
private:
    void loadFromMtl(const char *path);
    void loadFromObj(const char *path);
    
    vector<frag> vertexIndices, uvIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;
    map<string, Material> materials;
};

class Part : public Geometry {
    friend class OutterObject;
};

#endif /* outterObject_hpp */
