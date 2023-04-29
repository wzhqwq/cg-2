#version 330 core

in vec3 normalInterp;
in vec3 v;
in vec3 pos;

in vec2 TexCoord;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 materialCoefficients;
uniform int mode;

uniform vec4 lightPosDir;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform sampler2D ourTexture;

out vec4 color;

void main() {
    vec3 kd = vec3(0.0, 0.0, 0.0);
    vec3 ka = ambient;
    vec3 ks = specular;
    
    vec4 textureColor = texture(ourTexture, TexCoord);
    if (mode == 0) {
        kd = diffuse;
    }
    else if (mode == 1) {
        // texture mask mode
        kd = textureColor.a * diffuse + (1 - textureColor.a) * vec3(1.0, 1.0, 1.0);
    }
    else if (mode == 2) {
        // texture
        kd = textureColor.rgb;
    }
    else if (mode == 3) {
        // texture coordination test
        color = vec4(TexCoord, 0, 1);
        return;
    }
    
    vec3 l = -lightPosDir.xyz;
    float distance = 1.0f;
    if (lightPosDir.w > 0.5) {
        l = normalize(lightPosDir.xyz - pos);
        distance = length(lightPosDir.xyz - pos);
        distance = max(1, distance / 3);
    }
    vec3 n = normalize(normalInterp);
    vec3 h = normalize(l + v);
    
    float opacity = materialCoefficients.x;
    float shininess = materialCoefficients.y;
    float smoothness = materialCoefficients.z;
    
    vec3 Ia = lightColor * lightIntensity * 0.1f;
    vec3 Id = lightColor * lightIntensity;
    vec3 Is = lightColor * lightIntensity * smoothness;
    float lambertian = max(0, dot(l, n)), specAngle = max(0, dot(n, h));
    color = vec4(kd * Id * lambertian / distance +
                 ks * Is * pow(specAngle, shininess / 4) / distance +
                 ka * Ia,
                 opacity);
//    color = vec4(kd * Id * max(0, dot(l, n)) + ka * Ia, opacity);
//    color = vec4(n / 2 + 0.5, 1);
//    color = vec4(h, 1);
//    color = vec4(v, 1);
//    color = vec4(vec3(pow(max(0, dot(normalize(n), h)), shininess)), 1);
//    color = vec4(vec3(dot(l, n)), 1);
//    color = vec4(vec3(length(n)), 1);
}
