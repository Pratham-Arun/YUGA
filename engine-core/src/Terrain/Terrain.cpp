#include "Terrain/Terrain.h"
#include "Math/MathUtils.h"
#include <cmath>
#include <algorithm>

namespace YUGA {

Terrain::Terrain(int width, int height, float scale)
    : width(width)
    , height(height)
    , scale(scale)
{
    heightData.resize(width * height, 0.0f);
    textures.resize(4); // Support 4 texture layers
}

void Terrain::SetHeight(int x, int z, float height) {
    if (IsValid(x, z)) {
        heightData[GetIndex(x, z)] = height;
    }
}

float Terrain::GetHeight(int x, int z) const {
    if (IsValid(x, z)) {
        return heightData[GetIndex(x, z)];
    }
    return 0.0f;
}

float Terrain::GetHeightAtPosition(float worldX, float worldZ) const {
    // Convert world position to terrain coordinates
    float x = worldX / scale;
    float z = worldZ / scale;
    
    // Get integer coordinates
    int x0 = static_cast<int>(std::floor(x));
    int z0 = static_cast<int>(std::floor(z));
    int x1 = x0 + 1;
    int z1 = z0 + 1;
    
    // Get fractional part
    float fx = x - x0;
    float fz = z - z0;
    
    // Bilinear interpolation
    float h00 = GetHeight(x0, z0);
    float h10 = GetHeight(x1, z0);
    float h01 = GetHeight(x0, z1);
    float h11 = GetHeight(x1, z1);
    
    float h0 = Math::Lerp(h00, h10, fx);
    float h1 = Math::Lerp(h01, h11, fx);
    
    return Math::Lerp(h0, h1, fz);
}

void Terrain::GenerateHeightmap(int seed) {
    // Simple Perlin-like noise generation
    srand(seed);
    
    for (int z = 0; z < height; ++z) {
        for (int x = 0; x < width; ++x) {
            float nx = static_cast<float>(x) / width;
            float nz = static_cast<float>(z) / height;
            
            // Multiple octaves of noise
            float h = 0.0f;
            float amplitude = 1.0f;
            float frequency = 1.0f;
            
            for (int octave = 0; octave < 4; ++octave) {
                float sampleX = nx * frequency;
                float sampleZ = nz * frequency;
                
                // Simple noise (replace with proper Perlin noise for better results)
                float noise = (std::sin(sampleX * 10.0f) + std::cos(sampleZ * 10.0f)) * 0.5f;
                h += noise * amplitude;
                
                amplitude *= 0.5f;
                frequency *= 2.0f;
            }
            
            // Scale height
            h = (h + 1.0f) * 0.5f * 10.0f; // Height range 0-10
            
            SetHeight(x, z, h);
        }
    }
}

void Terrain::GenerateMesh() {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
    
    GenerateVertices(vertices, normals, texCoords, indices);
    
    // Create mesh (simplified - you'd use your actual Mesh class)
    mesh = std::make_shared<Mesh>();
    // mesh->SetVertices(vertices);
    // mesh->SetNormals(normals);
    // mesh->SetTexCoords(texCoords);
    // mesh->SetIndices(indices);
}

void Terrain::GenerateVertices(std::vector<float>& vertices, std::vector<float>& normals,
                               std::vector<float>& texCoords, std::vector<unsigned int>& indices) {
    // Generate vertices
    for (int z = 0; z < height; ++z) {
        for (int x = 0; x < width; ++x) {
            float h = GetHeight(x, z);
            
            // Position
            vertices.push_back(x * scale);
            vertices.push_back(h);
            vertices.push_back(z * scale);
            
            // Normal
            Vector3 normal = GetNormal(x, z);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            
            // Texture coordinates
            texCoords.push_back(static_cast<float>(x) / (width - 1));
            texCoords.push_back(static_cast<float>(z) / (height - 1));
        }
    }
    
    // Generate indices
    for (int z = 0; z < height - 1; ++z) {
        for (int x = 0; x < width - 1; ++x) {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;
            
            // First triangle
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            
            // Second triangle
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

Vector3 Terrain::GetNormal(int x, int z) const {
    // Calculate normal using neighboring heights
    float hL = GetHeight(x - 1, z);
    float hR = GetHeight(x + 1, z);
    float hD = GetHeight(x, z - 1);
    float hU = GetHeight(x, z + 1);
    
    Vector3 normal;
    normal.x = hL - hR;
    normal.y = 2.0f * scale;
    normal.z = hD - hU;
    
    return normal.Normalized();
}

void Terrain::SetTexture(int layer, std::shared_ptr<Texture> texture) {
    if (layer >= 0 && layer < static_cast<int>(textures.size())) {
        textures[layer] = texture;
    }
}

std::shared_ptr<Texture> Terrain::GetTexture(int layer) const {
    if (layer >= 0 && layer < static_cast<int>(textures.size())) {
        return textures[layer];
    }
    return nullptr;
}

void Terrain::Paint(float worldX, float worldZ, int layer, float radius, float strength) {
    // Convert world position to terrain coordinates
    int centerX = static_cast<int>(worldX / scale);
    int centerZ = static_cast<int>(worldZ / scale);
    int radiusInt = static_cast<int>(radius / scale);
    
    // Paint in circular area
    for (int z = centerZ - radiusInt; z <= centerZ + radiusInt; ++z) {
        for (int x = centerX - radiusInt; x <= centerX + radiusInt; ++x) {
            if (!IsValid(x, z)) continue;
            
            // Calculate distance from center
            float dx = (x - centerX) * scale;
            float dz = (z - centerZ) * scale;
            float dist = std::sqrt(dx * dx + dz * dz);
            
            if (dist <= radius) {
                // Apply falloff
                float falloff = 1.0f - (dist / radius);
                falloff = Math::SmoothStep(0.0f, 1.0f, falloff);
                
                // Modify height (or texture weight in a real implementation)
                float currentHeight = GetHeight(x, z);
                float newHeight = currentHeight + strength * falloff;
                SetHeight(x, z, newHeight);
            }
        }
    }
    
    // Regenerate mesh after painting
    GenerateMesh();
}

} // namespace YUGA
