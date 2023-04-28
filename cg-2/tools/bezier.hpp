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
    return (points[0] * ((1.0f - t) * (1.0f - t)) +
            points[1] * (2.0f * t * (1.0f - t)) +
            points[2] * (t * t));
}
inline vec2 cubicBezier(const vec2 *points, const float &t) {
    return (points[0] * ((1.0f - t) * (1.0f - t) * (1.0f - t)) +
            points[1] * (3.0f * t * (1.0f - t) * (1.0f - t)) +
            points[2] * (3.0f * t * t * (1.0f - t)) +
            points[3] * (t * t * t));
}

inline vec2 quadricBezierDerivative(const vec2 *points, const float &t) {
    return (2.0f * (1.0f - t) * (points[1] - points[0]) +
            2.0f * t * (points[2] - points[1]));
}
inline vec2 cubicBezierDerivative(const vec2 *points, const float &t) {
    return (3.0f * (1.0f - t) * (1.0f - t) * (points[1] - points[0]) +
            6.0f * (1.0f - t) * t * (points[2] - points[1]) +
            3.0f * t * t * (points[3] - points[2]));
}

#endif /* bezier_hpp */
