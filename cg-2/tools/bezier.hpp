//
//  bezier.hpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/25.
//

#ifndef bezier_hpp
#define bezier_hpp

#include "common.h"

inline vec2 quadricBezier(const vec2 *points, const float &t) {
    return  points[0] * ((1.0f - t) * (1.0f - t)) +
            points[1] * (2.0f * t * (1.0f - t)) +
            points[2] * (t * t);
}
inline vec2 cubicBezier(const vec2 *points, const float &t) {
    return  points[0] * ((1.0f - t) * (1.0f - t) * (1.0f - t)) +
            points[1] * (3.0f * t * (1.0f - t) * (1.0f - t)) +
            points[2] * (3.0f * t * t * (1.0f - t)) +
            points[3] * (t * t * t);
}

#endif /* bezier_hpp */
