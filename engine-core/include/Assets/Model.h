#pragma once

#include "Core/Core.h"
#include "Assets/Mesh.h"
#include "Assets/Material.h"
#include <vector>
#include <string>
#include <memory>

// Forward declarations for Assimp
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace YUGA {

    class Model {
    public:
        Model();
        ~Model();

        bool LoadFromFile(const std::string& path);
        void Draw();
        void Cleanup();

        const std::string& GetPath() const { return m_Path; }
        const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }
        const std::vector<std::shared_ptr<Material>>& GetMaterials() const { return m_Materials; }

        void SetMaterial(size_t meshIndex, std::shared_ptr<Material> material);

    private:
        std::string m_Path;
        std::string m_Directory;
        std::vector<std::shared_ptr<Mesh>> m_Meshes;
        std::vector<std::shared_ptr<Material>> m_Materials;
        bool m_IsLoaded = false;

        void ProcessNode(aiNode* node, const aiScene* scene);
        std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
        void LoadMaterialTextures(aiMaterial* mat, const aiScene* scene, std::shared_ptr<Material> material);
    };

} // namespace YUGA
