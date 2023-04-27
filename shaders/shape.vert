#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;

uniform mat4 MVP;
uniform mat4 MV;

out vec2 TexCoord;

out vec3 n;
out vec3 v;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    
    TexCoord = aTexCoord;
    
    n = normal;
    v = normalize(-vec3(MV * vec4(position, 1.0)));
}
