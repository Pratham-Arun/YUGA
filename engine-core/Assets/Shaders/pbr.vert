#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat3 TBN;
} vs_out;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    vec4 worldPos = u_Model * vec4(a_Position, 1.0);
    vs_out.FragPos = worldPos.xyz;
    
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vs_out.Normal = normalize(normalMatrix * a_Normal);
    vs_out.TexCoords = a_TexCoords;
    
    // Calculate TBN matrix for normal mapping
    vec3 T = normalize(normalMatrix * a_Tangent);
    vec3 B = normalize(normalMatrix * a_Bitangent);
    vec3 N = vs_out.Normal;
    vs_out.TBN = mat3(T, B, N);
    
    gl_Position = u_Projection * u_View * worldPos;
}
