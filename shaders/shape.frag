#version 330 core

in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in float alpha;

in vec3 n;
in vec3 v;

in vec2 TexCoord;
flat in int mode;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    vec4 textureColor = texture(ourTexture, TexCoord);
    vec4 finalDiffuse = vec4(0.0, 0.0, 0.0, 1.0);
    if (mode == 0) {
        finalDiffuse = vec4(diffuse, 1.0);
    }
    else if (mode == 1) {
        // texture mask mode
        finalDiffuse = vec4(textureColor.a * diffuse + (1 - textureColor.a) * vec3(1.0, 1.0, 1.0), 1.0);
    }
    else if (mode == 2) {
        // texture
        finalDiffuse = textureColor;
    }
    else if (mode == 3) {
        // texture coordination test
        finalDiffuse = vec4(TexCoord, 0.0, 1.0);
    }
    finalDiffuse.a = finalDiffuse.a * alpha;
    color = finalDiffuse;
}
