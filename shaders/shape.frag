#version 330 core

in vec3 normalInterp;
in vec3 v;
in vec3 pos;
in mat3 TBN;

in vec2 TexCoord;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 materialCoefficients;
uniform int mode;

uniform vec4 lightPosDir;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 color;

void main() {
    float opacity = materialCoefficients.x;
    float shininess = materialCoefficients.y;
    float smoothness = materialCoefficients.z;
    
    if (mode == 1) {
        // unlit single color
        color = vec4(diffuse, opacity);
        return;
    }
    if (mode == 2) {
        // texture coordination test
        color = vec4(TexCoord, 0, opacity);
        return;
    }
    if (mode == 3) {
        // unlit texture
        color = vec4(vec3(texture(texture1, TexCoord)), opacity);
        return;
    }

    vec3 kd = diffuse;
    vec3 ka = ambient;
    vec3 ks = specular;
    
    vec3 n = normalize(normalInterp);
    if ((mode & 8) != 0) {
        vec4 textureColor = texture(texture1, TexCoord);
        if ((mode & 1) != 0) {
            // texture mask mode
            kd = textureColor.a * diffuse + (1 - textureColor.a) * vec3(1.0, 1.0, 1.0);
        }
        else {
            // texture
            kd = textureColor.rgb;
        }
        if ((mode & 2) != 0) {
            // with normal map
            n = texture(texture2, TexCoord).xyz;
            n = normalize(n * 2.0 - 1.0);
            n = normalize(TBN * n);
        }
    }
    vec3 l = -lightPosDir.xyz;
    float distance = 1.0f;
    if (lightPosDir.w > 0.5) {
        l = normalize(lightPosDir.xyz - pos);
        distance = length(lightPosDir.xyz - pos);
        distance = max(1, distance / 3);
    }
    vec3 h = normalize(l + v);
    
    vec3 Ia = lightColor * lightIntensity * 0.15f;
    vec3 Id = lightColor * lightIntensity;
    vec3 Is = lightColor * lightIntensity * smoothness;
    // sRGB色域下的灰度计算公式
    float kdGray = dot(kd, vec3(0.2126, 0.7152, 0.0722));
    float lambertian = max(0, dot(l, n)), specAngle = max(0, dot(n, h));
    color = vec4(kd * Id * lambertian / distance +
                 ks * Is * pow(specAngle, shininess / 4) / distance +
                 ka * Ia * kdGray,
                 opacity);
//    color = vec4(kd * Id * max(0, dot(l, n)) + ka * Ia, opacity);
//    color = vec4(n / 2 + 0.5, 1);
//    color = vec4(h, 1);
//    color = vec4(v, 1);
//    color = vec4(vec3(pow(max(0, dot(normalize(n), h)), shininess)), 1);
//    color = vec4(vec3(dot(l, n)), 1);
//    color = vec4(vec3(length(n)), 1);
}
