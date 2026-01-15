#pragma once
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Assets/Texture.h"
#include "Assets/Mesh.h"
#include <vector>
#include <memory>

namespace YUGA {

class Terrain {
public:
    Terrain(int width, int height, float scale = 1.0f);
    ~Terrain() = default;
    
    // Heightmap
    void SetHeight(int x, int z, float height);
    float GetHeight(int x, int z) const;
    float GetHeightAtPosition(float worldX, float worldZ) const;
    
    void LoadHeightmap(const std::string& filepath);
    void GenerateHeightmap(int seed = 0);
    
    // Mesh generation
    void GenerateMesh();
    std::shared_ptr<Mesh> GetMesh() const { return mesh; }
    
    // Texturing
    void SetTexture(int layer, std::shared_ptr<Texture> texture);
    std::shared_ptr<Texture> GetTexture(int layer) const;
    
    // Properties
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float GetScale() const { return scale; }
    
    void SetScale(float newScale) { scale = newScale; }
    
    // Painting
    void Paint(float worldX, float worldZ, int layer, float radius, float strength);
    
    // Normal calculation
    Vector3 GetNormal(int x, int z) const;
    
private:
    int width;
    int height;
    float scale;
    
    std::vector<float> heightData;
    std::vector<std::shared_ptr<Texture>> textures;
    std::shared_ptr<Mesh> mesh;
    
    int GetIndex(int x, int z) const { return z * width + x; }
    bool IsValid(int x, int z) const { return x >= 0 && x < width && z >= 0 && z < height; }
    
    void GenerateVertices(std::vector<float>& vertices, std::vector<float>& normals, 
                         std::vector<float>& texCoords, std::vector<unsigned int>& indices);
};

} // namespace YUGA
