#version 460 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat3 TBN;
} fs_in;

// Material properties
struct Material {
    vec3 albedo;
    float metallic;
    float roughness;
    float ao;
    vec3 emissive;
    float emissiveStrength;
    float opacity;
    
    int hasAlbedoMap;
    int hasNormalMap;
    int hasMetallicMap;
    int hasRoughnessMap;
    int hasAOMap;
    int hasEmissiveMap;
};

uniform Material u_Material;

// Texture maps
uniform sampler2D u_AlbedoMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_MetallicMap;
uniform sampler2D u_RoughnessMap;
uniform sampler2D u_AOMap;
uniform sampler2D u_EmissiveMap;

// Lighting
uniform vec3 u_CameraPos;
uniform vec3 u_LightPositions[4];
uniform vec3 u_LightColors[4];
uniform int u_NumLights;

const float PI = 3.14159265359;

// PBR Functions
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    
    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    
    return ggx1 * ggx2;
}

vec3 getNormalFromMap() {
    vec3 tangentNormal = texture(u_NormalMap, fs_in.TexCoords).xyz * 2.0 - 1.0;
    return normalize(fs_in.TBN * tangentNormal);
}

void main() {
    // Sample textures
    vec3 albedo = u_Material.hasAlbedoMap == 1 
        ? pow(texture(u_AlbedoMap, fs_in.TexCoords).rgb, vec3(2.2)) * u_Material.albedo
        : u_Material.albedo;
    
    float metallic = u_Material.hasMetallicMap == 1 
        ? texture(u_MetallicMap, fs_in.TexCoords).r 
        : u_Material.metallic;
    
    float roughness = u_Material.hasRoughnessMap == 1 
        ? texture(u_RoughnessMap, fs_in.TexCoords).r 
        : u_Material.roughness;
    
    float ao = u_Material.hasAOMap == 1 
        ? texture(u_AOMap, fs_in.TexCoords).r 
        : u_Material.ao;
    
    vec3 emissive = u_Material.hasEmissiveMap == 1 
        ? texture(u_EmissiveMap, fs_in.TexCoords).rgb * u_Material.emissive * u_Material.emissiveStrength
        : u_Material.emissive * u_Material.emissiveStrength;
    
    // Get normal
    vec3 N = u_Material.hasNormalMap == 1 ? getNormalFromMap() : normalize(fs_in.Normal);
    vec3 V = normalize(u_CameraPos - fs_in.FragPos);
    
    // Calculate reflectance at normal incidence
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);
    
    // Reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < u_NumLights && i < 4; ++i) {
        // Calculate per-light radiance
        vec3 L = normalize(u_LightPositions[i] - fs_in.FragPos);
        vec3 H = normalize(V + L);
        float distance = length(u_LightPositions[i] - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = u_LightColors[i] * attenuation;
        
        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;
        
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;
        
        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }
    
    // Ambient lighting
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo + emissive;
    
    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // Gamma correction
    color = pow(color, vec3(1.0/2.2));
    
    FragColor = vec4(color, u_Material.opacity);
}
