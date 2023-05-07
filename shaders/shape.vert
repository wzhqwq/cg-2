#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;

uniform mat4 Model;
uniform mat4 ViewProjection;

uniform vec3 viewerPos;

out vec2 TexCoord;

out vec3 normalInterp;
out vec3 v;
out vec3 pos;
out mat3 TBN;

void main() {
    vec4 worldPos = Model * vec4(position, 1);
    // 阴影矩阵可能会导致最终model矩阵齐次系数为负数，所以对世界坐标处理一下
    worldPos /= worldPos.w;
    gl_Position = ViewProjection * worldPos;

    TexCoord = aTexCoord;
    
    normalInterp = transpose(inverse(mat3(Model))) * normal;
    pos = worldPos.xyz;
    v = normalize(viewerPos - pos);

    // 切线空间标架计算，仅考虑平面的法线贴图（各点切线空间相同，偷个懒），平面初始位置面向z轴正方向
    vec3 T = normalize(vec3(Model * vec4(1, 0, 0, 0)));
    vec3 B = normalize(vec3(Model * vec4(0, 1, 0, 0)));
    vec3 N = normalize(vec3(Model * vec4(0, 0, 1, 0)));
    TBN = mat3(T, B, N);
}
