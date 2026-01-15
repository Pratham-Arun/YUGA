#include "Assets/AssetManager.h"
#include "Core/Log.h"

namespace YUGA {

    AssetManager& AssetManager::Get() {
        static AssetManager instance;
        return instance;
    }

    // Model Management
    std::shared_ptr<Model> AssetManager::LoadModel(const std::string& path) {
        // Check if already loaded
        auto it = m_Models.find(path);
        if (it != m_Models.end()) {
            LOG_INFO("Model already loaded: {}", path);
            return it->second;
        }

        // Load new model
        auto model = std::make_shared<Model>();
        if (model->LoadFromFile(path)) {
            m_Models[path] = model;
            LOG_INFO("Model cached: {}", path);
            return model;
        }

        LOG_ERROR("Failed to load model: {}", path);
        return nullptr;
    }

    std::shared_ptr<Model> AssetManager::GetModel(const std::string& path) {
        auto it = m_Models.find(path);
        if (it != m_Models.end()) {
            return it->second;
        }
        return nullptr;
    }

    void AssetManager::UnloadModel(const std::string& path) {
        auto it = m_Models.find(path);
        if (it != m_Models.end()) {
            it->second->Cleanup();
            m_Models.erase(it);
            LOG_INFO("Model unloaded: {}", path);
        }
    }

    // Texture Management
    std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string& path, TextureType type) {
        // Check if already loaded
        auto it = m_Textures.find(path);
        if (it != m_Textures.end()) {
            return it->second;
        }

        // Load new texture
        auto texture = std::make_shared<Texture>();
        if (texture->LoadFromFile(path, type)) {
            m_Textures[path] = texture;
            return texture;
        }

        LOG_ERROR("Failed to load texture: {}", path);
        return nullptr;
    }

    std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& path) {
        auto it = m_Textures.find(path);
        if (it != m_Textures.end()) {
            return it->second;
        }
        return nullptr;
    }

    void AssetManager::UnloadTexture(const std::string& path) {
        auto it = m_Textures.find(path);
        if (it != m_Textures.end()) {
            it->second->Cleanup();
            m_Textures.erase(it);
            LOG_INFO("Texture unloaded: {}", path);
        }
    }

    // Material Management
    std::shared_ptr<Material> AssetManager::CreateMaterial(const std::string& name) {
        auto it = m_Materials.find(name);
        if (it != m_Materials.end()) {
            LOG_WARN("Material already exists: {}", name);
            return it->second;
        }

        auto material = std::make_shared<Material>(name);
        m_Materials[name] = material;
        LOG_INFO("Material created: {}", name);
        return material;
    }

    std::shared_ptr<Material> AssetManager::GetMaterial(const std::string& name) {
        auto it = m_Materials.find(name);
        if (it != m_Materials.end()) {
            return it->second;
        }
        return nullptr;
    }

    void AssetManager::UnloadMaterial(const std::string& name) {
        auto it = m_Materials.find(name);
        if (it != m_Materials.end()) {
            m_Materials.erase(it);
            LOG_INFO("Material unloaded: {}", name);
        }
    }

    // Shader Management
    std::shared_ptr<Shader> AssetManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end()) {
            LOG_INFO("Shader already loaded: {}", name);
            return it->second;
        }

        auto shader = std::make_shared<Shader>(vertexPath, fragmentPath);
        m_Shaders[name] = shader;
        LOG_INFO("Shader loaded: {}", name);
        return shader;
    }

    std::shared_ptr<Shader> AssetManager::GetShader(const std::string& name) {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end()) {
            return it->second;
        }
        return nullptr;
    }

    void AssetManager::UnloadShader(const std::string& name) {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end()) {
            m_Shaders.erase(it);
            LOG_INFO("Shader unloaded: {}", name);
        }
    }

    // Cleanup
    void AssetManager::UnloadAll() {
        LOG_INFO("Unloading all assets...");
        
        for (auto& [path, model] : m_Models) {
            model->Cleanup();
        }
        m_Models.clear();

        for (auto& [path, texture] : m_Textures) {
            texture->Cleanup();
        }
        m_Textures.clear();

        m_Materials.clear();
        m_Shaders.clear();

        LOG_INFO("All assets unloaded");
    }

    void AssetManager::UnloadUnused() {
        // Remove models with only 1 reference (only AssetManager holds it)
        for (auto it = m_Models.begin(); it != m_Models.end();) {
            if (it->second.use_count() == 1) {
                LOG_INFO("Unloading unused model: {}", it->first);
                it->second->Cleanup();
                it = m_Models.erase(it);
            } else {
                ++it;
            }
        }

        // Remove textures with only 1 reference
        for (auto it = m_Textures.begin(); it != m_Textures.end();) {
            if (it->second.use_count() == 1) {
                LOG_INFO("Unloading unused texture: {}", it->first);
                it->second->Cleanup();
                it = m_Textures.erase(it);
            } else {
                ++it;
            }
        }

        // Remove materials with only 1 reference
        for (auto it = m_Materials.begin(); it != m_Materials.end();) {
            if (it->second.use_count() == 1) {
                LOG_INFO("Unloading unused material: {}", it->first);
                it = m_Materials.erase(it);
            } else {
                ++it;
            }
        }

        // Remove shaders with only 1 reference
        for (auto it = m_Shaders.begin(); it != m_Shaders.end();) {
            if (it->second.use_count() == 1) {
                LOG_INFO("Unloading unused shader: {}", it->first);
                it = m_Shaders.erase(it);
            } else {
                ++it;
            }
        }
    }

} // namespace YUGA
