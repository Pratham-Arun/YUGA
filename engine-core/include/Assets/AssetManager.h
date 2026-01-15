#pragma once

#include "Core/Core.h"
#include "Assets/Model.h"
#include "Assets/Texture.h"
#include "Assets/Material.h"
#include "Rendering/Shader.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace YUGA {

    class AssetManager {
    public:
        static AssetManager& Get();

        // Model management
        std::shared_ptr<Model> LoadModel(const std::string& path);
        std::shared_ptr<Model> GetModel(const std::string& path);
        void UnloadModel(const std::string& path);

        // Texture management
        std::shared_ptr<Texture> LoadTexture(const std::string& path, TextureType type = TextureType::Diffuse);
        std::shared_ptr<Texture> GetTexture(const std::string& path);
        void UnloadTexture(const std::string& path);

        // Material management
        std::shared_ptr<Material> CreateMaterial(const std::string& name);
        std::shared_ptr<Material> GetMaterial(const std::string& name);
        void UnloadMaterial(const std::string& name);

        // Shader management
        std::shared_ptr<Shader> LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        std::shared_ptr<Shader> GetShader(const std::string& name);
        void UnloadShader(const std::string& name);

        // Cleanup
        void UnloadAll();
        void UnloadUnused(); // Unload assets with only 1 reference (only AssetManager holds it)

        // Statistics
        size_t GetModelCount() const { return m_Models.size(); }
        size_t GetTextureCount() const { return m_Textures.size(); }
        size_t GetMaterialCount() const { return m_Materials.size(); }
        size_t GetShaderCount() const { return m_Shaders.size(); }

    private:
        AssetManager() = default;
        ~AssetManager() = default;
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

        std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
        std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };

} // namespace YUGA
