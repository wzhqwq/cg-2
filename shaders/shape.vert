#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 TexCoord;

out vec3 normalInterp;
out vec3 v;
out vec3 pos;

void main() {
    vec4 worldPos = Model * vec4(position, 1);
    // 阴影矩阵可能会导致最终model矩阵齐次系数为负数，所以对世界坐标处理一下
    worldPos /= worldPos.w;
    vec4 viewPos = View * worldPos;
    gl_Position = Projection * viewPos;

    TexCoord = aTexCoord;
    
    vec4 worldNormal = Model * vec4(normal, 0);
    normalInterp = normalize(worldNormal.xyz);
    v = (inverse(View) * vec4(normalize(-viewPos.xyz), 0)).xyz;
    pos = worldPos.xyz;
}
