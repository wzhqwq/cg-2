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

using namespace std;

class OutterObject : public Geometry {
public:
    OutterObject(string path) {
        loadFromObj(path.c_str());
    }
private:
    void loadFromObj(const char *path);
};

#endif /* outterObject_hpp */
