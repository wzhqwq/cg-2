#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 ambientColor;
layout (location = 4) in vec3 diffuseColor;
layout (location = 5) in vec3 specularColor;
layout (location = 6) in float opacity;
layout (location = 7) in int renderMode;

uniform mat4 MVP;
uniform mat4 MV;

out vec3 ambient;
out vec3 diffuse;
out vec3 specular;
out float alpha;
out vec2 TexCoord;
flat out int mode;

out vec3 n;
out vec3 v;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    
    ambient = ambientColor;
    diffuse = diffuseColor;
    specular = specularColor;
    alpha = opacity;
    
    TexCoord = aTexCoord;
    mode = renderMode;
    
    n = normal;
    v = normalize(-vec3(MV * vec4(position, 1.0)));
}
