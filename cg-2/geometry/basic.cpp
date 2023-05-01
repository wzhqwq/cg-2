//
//  basic.cpp
//  cg-2
//
//  Created by 王子涵 on 2023/4/22.
//

#include "basic.hpp"

void Cube::setup() {
    // 采用纸盒展开的贴图
    // 上 y = 0.5
    addVert(vec3(-0.5, 0.5, -0.5), vec2(0.25, 0.25), vec3(0, 1, 0));
    addVert(vec3(-0.5, 0.5, 0.5), vec2(0.25, 0.5), vec3(0, 1, 0));
    addVert(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5), vec3(0, 1, 0));
    addVert(vec3(0.5, 0.5, -0.5), vec2(0.5, 0.25), vec3(0, 1, 0));
    addFrag(0, 1, 2, 3);
    // 下 y = -0.5
    addVert(vec3(0.5, -0.5, -0.5), vec2(0.75, 0.25), vec3(0, -1, 0));
    addVert(vec3(0.5, -0.5, 0.5), vec2(0.75, 0.5), vec3(0, -1, 0));
    addVert(vec3(-0.5, -0.5, 0.5), vec2(1.0, 0.5), vec3(0, -1, 0));
    addVert(vec3(-0.5, -0.5, -0.5), vec2(1.0, 0.25), vec3(0, -1, 0));
    addFrag(4, 5, 6, 7);
    // 右 x = 0.5
    addVert(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5), vec3(1, 0, 0));
    addVert(vec3(0.5, -0.5, 0.5), vec2(0.75, 0.5), vec3(1, 0, 0));
    addVert(vec3(0.5, -0.5, -0.5), vec2(0.75, 0.25), vec3(1, 0, 0));
    addVert(vec3(0.5, 0.5, -0.5), vec2(0.5, 0.25), vec3(1, 0, 0));
    addFrag(8, 9, 10, 11);
    // 左 x = -0.5
    addVert(vec3(-0.5, 0.5, -0.5), vec2(0.25, 0.25), vec3(-1, 0, 0));
    addVert(vec3(-0.5, -0.5, -0.5), vec2(0.0, 0.25), vec3(-1, 0, 0));
    addVert(vec3(-0.5, -0.5, 0.5), vec2(0.0, 0.5), vec3(-1, 0, 0));
    addVert(vec3(-0.5, 0.5, 0.5), vec2(0.25, 0.5), vec3(-1, 0, 0));
    addFrag(12, 13, 14, 15);
    // 前 z = 0.5
    addVert(vec3(-0.5, 0.5, 0.5), vec2(0.25, 0.5), vec3(0, 0, 1));
    addVert(vec3(-0.5, -0.5, 0.5), vec2(0.25, 0.75), vec3(0, 0, 1));
    addVert(vec3(0.5, -0.5, 0.5), vec2(0.5, 0.75), vec3(0, 0, 1));
    addVert(vec3(0.5, 0.5, 0.5), vec2(0.5, 0.5), vec3(0, 0, 1));
    addFrag(16, 17, 18, 19);
    // 后 z = -0.5
    addVert(vec3(0.5, 0.5, -0.5), vec2(0.5, 0.25), vec3(0, 0, -1));
    addVert(vec3(0.5, -0.5, -0.5), vec2(0.5, 0.0), vec3(0, 0, -1));
    addVert(vec3(-0.5, -0.5, -0.5), vec2(0.25, 0.0), vec3(0, 0, -1));
    addVert(vec3(-0.5, 0.5, -0.5), vec2(0.25, 0.25), vec3(0, 0, -1));
    addFrag(20, 21, 22, 23);
}

void Sphere::setup(int slices, int stacks) {
    float texFragX = 1.0f / slices, texFragY = 1.0f / stacks;
    float Pi = pi<float>();
    for (int i = 0; i <= slices; i++) {
        float longitude = 2 * Pi * i / slices;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        addVert(vec3(0, 0.5f, 0), vec2(texFragX * (i + 0.5f), 0), vec3(0, 1, 0));
        for (int j = 1; j < stacks; j++) {
            float latitude = Pi * (0.5f - (float) j / stacks);
            vec3 pos = vec3(x * cos(latitude), 0.5f * sin(latitude), z * cos(latitude));
            addVert(pos, vec2(texFragX * i, texFragY * j), pos * 2.0f);
        }
        addVert(vec3(0, -0.5f, 0), vec2(texFragX * (i + 0.5f), 1), vec3(0, -1, 0));
    }
    for (int i = 0; i < slices; i++) {
        int offset = (stacks + 1) * i;
        int nextOffset = offset + (stacks + 1);
        addFrag(offset, offset + 1, nextOffset + 1);
        for (int j = 1; j < stacks - 1; j++) {
            addFrag(offset + j, offset + j + 1, nextOffset + j + 1, nextOffset + j);
        }
        addFrag(offset + stacks - 1, offset + stacks, nextOffset + stacks - 1);
    }
}

void Cylinder::setup(int slices, int stacks) {
    float texFragX = 1.0f / slices, texFragY = 1.0f / (stacks + 2);
    float Pi = pi<float>();
    for (int i = 0; i <= slices; i++) {
        float longitude = 2 * Pi * i / slices;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        vec3 sideNormal = vec3(sin(longitude), 0, cos(longitude));

        addVert(vec3(0, 0.5f, 0), vec2(texFragX * (i + 0.5f), 0), vec3(0, 1, 0));
        addVert(vec3(x, 0.5f, z), vec2(texFragX * i, texFragY), vec3(0, 1, 0));

        for (int j = 0; j <= stacks; j++)
            addVert(vec3(x, 0.5f - 1.0f * j / stacks, z),
                    vec2(texFragX * (i + 0.5f), texFragY * (j + 1)),
                    sideNormal);
        
        addVert(vec3(x, -0.5f, z), vec2(texFragX * i, 1.0f - texFragY), vec3(0, -1, 0));
        addVert(vec3(0, -0.5f, 0), vec2(texFragX * (i + 0.5f), 1), vec3(0, -1, 0));
    }
    for (int i = 0; i < slices; i++) {
        int offset = i * (stacks + 5);
        int nextOffset = offset + (stacks + 5);
        addFrag(offset, offset + 1, nextOffset + 1);
        for (int j = 0; j < stacks; j++) {
            addFrag(offset + j + 2, offset + j + 3, nextOffset + j + 3, nextOffset + j + 2);
        }
        addFrag(offset + stacks + 3, offset + stacks + 4, nextOffset + stacks + 3);
    }
}

void Cone::setup(int slices, int stacks) {
    float texFragX = 1.0f / slices, texFragY = 1.0f / (stacks + 1);
    float Pi = pi<float>();
    for (int i = 0; i <= slices; i++) {
        float longitude = 2 * Pi * i / slices;
        float x = 0.5f * sin(longitude), z = 0.5f * cos(longitude);
        vec3 sideNormal = normalize(vec3(sin(longitude), 1, cos(longitude)));
        
        for (int j = 0; j <= stacks; j++)
            addVert(vec3(x * j / stacks, (float)(stacks - j) / stacks, z * j / stacks),
                    vec2(texFragX * (i + 0.5f), texFragY * j),
                    sideNormal);

        addVert(vec3(x, 0, z), vec2(texFragX * i, 1.0f - texFragY), vec3(0, -1, 0));
        addVert(vec3(0, 0, 0), vec2(texFragX * (i + 0.5f), 1), vec3(0, -1, 0));
    }
    for (int i = 0; i < slices; i++) {
        int offset = i * (stacks + 3);
        int nextOffset = offset + (stacks + 3);
        addFrag(offset, offset + 1, nextOffset + 1);
        for (int j = 0; j < stacks - 1; j++) {
            addFrag(offset + j + 2, offset + j + 3, nextOffset + j + 3, nextOffset + j + 2);
        }
        addFrag(offset + stacks + 1, offset + stacks + 2, nextOffset + stacks + 1);
    }
}

void Ring::setup(int slices, int stacks, float inset, float start, float end) {
    float texFragX = 1.0f / slices, texFragY = 1.0f / (stacks + 2);
    float Pi = pi<float>();
    float r = (1 - inset) / 4;
    float R = inset / 2 + r;
    for (int i = 0; i <= slices; i++) {
        float longitude = 2 * Pi * i / slices;
        vec4 pos = vec4(r * sin(longitude) + R, r * cos(longitude), 0, 1);
        vec4 normal = vec4(sin(longitude), cos(longitude), 0, 0);
        
        // 起始面的法线是起始角+90度
        addVert(vec3(R * cos(start), 0, -R * sin(start)),
                vec2(texFragX * (i + 0.5f), 0),
                vec3(-sin(start), 0, -cos(start)));
        addVert(vec3(glm::rotate(mat4(1), start, vec3(0, 1, 0)) * pos),
                vec2(texFragX * (i + 0.5f), texFragY),
                vec3(-sin(start), 0, -cos(start)));
        for (int j = 0; j <= stacks; j++) {
            float angle = start + (end - start) * j / stacks;
            mat4 rMat = glm::rotate(mat4(1), angle, vec3(0, 1, 0));
            // 将xy平面上的圆形样条沿弧旋转
            addVert(vec3(rMat * pos),
                    vec2(texFragX * i, texFragY * (j + 1)),
                    vec3(rMat * normal));
        }
        // 终止面的法线是终止角-90度
        addVert(vec3(glm::rotate(mat4(1), end, vec3(0, 1, 0)) * pos),
                vec2(texFragX * (i + 0.5f), 1.0f - texFragY),
                vec3(sin(end), 0, cos(end)));
        addVert(vec3(R * cos(end), 0, -R * sin(end)),
                vec2(texFragX * (i + 0.5f), 1),
                vec3(sin(end), 0, cos(end)));
    }
    for (int i = 0; i < slices; i++) {
        int offset = i * (stacks + 5);
        int nextOffset = offset + (stacks + 5);
        addFrag(offset, nextOffset + 1, offset + 1);
        for (int j = 0; j < stacks; j++) {
            addFrag(offset + j + 2, nextOffset + j + 2, nextOffset + j + 3, offset + j + 3);
        }
        addFrag(offset + stacks + 3, nextOffset + stacks + 3, offset + stacks + 4);
    }
}

// 外层
vec2 vaseCurve1[] = {
    vec2(0.2f, 0.0f),
    vec2(0.3f, 0.1f),
    vec2(0.3f, 0.3f),
};
vec2 vaseCurve2[] = {
    vec2(0.3f, 0.3f),
    vec2(0.3f, 0.5f),
    vec2(0.1f, 0.6f),
    vec2(0.1f, 0.8f),
};
vec2 vaseCurve3[] = {
    vec2(0.1f, 0.8f),
    vec2(0.1f, 0.9f),
    vec2(0.2f, 1.0f),
};
// 内层
vec2 vaseCurve4[] = {
    vec2(0.18f, 1.0f),
    vec2(0.08f, 0.9f),
    vec2(0.08f, 0.8f),
};
vec2 vaseCurve5[] = {
    vec2(0.08f, 0.8f),
    vec2(0.08f, 0.6f),
    vec2(0.28f, 0.5f),
    vec2(0.28f, 0.3f),
};
vec2 vaseCurve6[] = {
    vec2(0.28f, 0.3f),
    vec2(0.28f, 0.1f),
    vec2(0.2f, 0.02f),
};

inline vec2 rSpin90(vec2 v) { return vec2(v.y, -v.x); }

void Vase::setup(int rSub, int bSub) {
    float texFragX = 1.0f / rSub, texFragY = 0.04f;
    float Pi = pi<float>();
    float sub2 = 2.0f / bSub, sub3 = 3.0f / bSub, sub5 = 5.0f / bSub;
    for (int i = 0; i <= rSub; i++) {
        float angle = 2 * Pi * i / rSub;
        mat4 rMat = glm::rotate(mat4(1), angle, vec3(0, 1, 0));
        // 底盘+2
        addVert(vec3(0, 0, 0), vec2(texFragX * (i + 0.5f), 0), vec3(0, -1, 0));
        // 外部
        // 下段+3
        for (int j = 0; j < bSub; j++) {
            vec4 point = vec4(quadricBezier(vaseCurve1, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(quadricBezierDerivative(vaseCurve1, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub3 + 2)),
                    vec3(rMat * normal));
        }
        // 中段+5
        for (int j = 0; j < bSub; j++) {
            vec4 point = vec4(cubicBezier(vaseCurve2, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(cubicBezierDerivative(vaseCurve2, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub5 + 5)),
                    vec3(rMat * normal));
        }
        // 上段+2
        for (int j = 0; j <= bSub; j++) {
            vec4 point = vec4(quadricBezier(vaseCurve3, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(quadricBezierDerivative(vaseCurve3, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub2 + 10)),
                    vec3(rMat * normal));
        }
        // 边缘+1
        addVert(vec3(rMat * vec4(0.2f, 1, 0, 1)), vec2(texFragX * i, texFragY * 12), vec3(0, 1, 0));
        // 内部
        // 上段+2
        for (int j = 0; j < bSub; j++) {
            vec4 point = vec4(quadricBezier(vaseCurve4, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(quadricBezierDerivative(vaseCurve4, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub2 + 13)),
                    vec3(rMat * normal));
        }
        // 中段+5
        for (int j = 0; j < bSub; j++) {
            vec4 point = vec4(cubicBezier(vaseCurve5, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(cubicBezierDerivative(vaseCurve5, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub5 + 15)),
                    vec3(rMat * normal));
        }
        // 下段+3
        for (int j = 0; j <= bSub; j++) {
            vec4 point = vec4(quadricBezier(vaseCurve6, 1.0f * j / bSub), 0, 1);
            vec4 normal = vec4(rSpin90(quadricBezierDerivative(vaseCurve6, 1.0f * j / bSub)), 0, 0);
            addVert(vec3(rMat * point),
                    vec2(texFragX * i, texFragY * (j * sub3 + 20)),
                    vec3(rMat * normal));
        }
        // 底盘+2
        addVert(vec3(0, 0.02f, 0), vec2(texFragX * (i + 0.5f), 1), vec3(0, 1, 0));
    }
    int aSub = bSub * 6 + 4;
    for (int i = 0; i < rSub; i++) {
        int offset = (aSub + 1) * i;
        int nextOffset = offset + (aSub + 1);
        addFrag(offset, nextOffset + 1, offset + 1);
        for (int j = 0; j < aSub - 1; j++) {
            addFrag(offset + j, nextOffset + j, nextOffset + j + 1, offset + j + 1);
        }
        addFrag(offset + aSub - 1, nextOffset + aSub - 1, offset + aSub);
    }
}
