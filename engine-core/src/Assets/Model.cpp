#include "Assets/Model.h"
#include "Assets/AssetManager.h"
#include "Core/Log.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace YUGA {

    Model::Model() {}

    Model::~Model() {
        Cleanup();
    }

    bool Model::LoadFromFile(const std::string& path) {
        m_Path = path;
        
        // Extract directory from path
        size_t lastSlash = path.find_last_of("/\\");
        m_Directory = (lastSlash != std::string::npos) ? path.substr(0, lastSlash) : "";

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, 
            aiProcess_Triangulate | 
            aiProcess_FlipUVs | 
            aiProcess_CalcTangentSpace |
            aiProcess_GenNormals |
            aiProcess_JoinIdenticalVertices |
            aiProcess_OptimizeMeshes
        );

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LOG_ERROR("Assimp error: {}", importer.GetErrorString());
            return false;
        }

        LOG_INFO("Loading model: {}", path);
        LOG_INFO("  Meshes: {}", scene->mNumMeshes);
        LOG_INFO("  Materials: {}", scene->mNumMaterials);

        // Process materials first
        m_Materials.reserve(scene->mNumMaterials);
        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            auto material = std::make_shared<Material>("Material_" + std::to_string(i));
            LoadMaterialTextures(scene->mMaterials[i], scene, material);
            m_Materials.push_back(material);
        }

        // Process nodes recursively
        ProcessNode(scene->mRootNode, scene);

        m_IsLoaded = true;
        LOG_INFO("Model loaded successfully: {} meshes", m_Meshes.size());
        return true;
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene) {
        // Process all meshes in this node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        // Process children nodes recursively
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Process vertices
        vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            // Position
            vertex.Position.x = mesh->mVertices[i].x;
            vertex.Position.y = mesh->mVertices[i].y;
            vertex.Position.z = mesh->mVertices[i].z;

            // Normals
            if (mesh->HasNormals()) {
                vertex.Normal.x = mesh->mNormals[i].x;
                vertex.Normal.y = mesh->mNormals[i].y;
                vertex.Normal.z = mesh->mNormals[i].z;
            }

            // Texture coordinates
            if (mesh->mTextureCoords[0]) {
                vertex.TexCoords[0] = mesh->mTextureCoords[0][i].x;
                vertex.TexCoords[1] = mesh->mTextureCoords[0][i].y;
            }

            // Tangent
            if (mesh->HasTangentsAndBitangents()) {
                vertex.Tangent.x = mesh->mTangents[i].x;
                vertex.Tangent.y = mesh->mTangents[i].y;
                vertex.Tangent.z = mesh->mTangents[i].z;

                // Bitangent
                vertex.Bitangent.x = mesh->mBitangents[i].x;
                vertex.Bitangent.y = mesh->mBitangents[i].y;
                vertex.Bitangent.z = mesh->mBitangents[i].z;
            }

            vertices.push_back(vertex);
        }

        // Process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        auto resultMesh = std::make_shared<Mesh>(vertices, indices);
        resultMesh->MaterialIndex = mesh->mMaterialIndex;

        return resultMesh;
    }

    void Model::LoadMaterialTextures(aiMaterial* mat, const aiScene* scene, std::shared_ptr<Material> material) {
        auto& assetManager = AssetManager::Get();

        // Helper lambda to load texture
        auto loadTexture = [&](aiTextureType aiType, TextureType yugaType) {
            if (mat->GetTextureCount(aiType) > 0) {
                aiString str;
                mat->GetTexture(aiType, 0, &str);
                std::string texturePath = m_Directory + "/" + std::string(str.C_Str());
                
                auto texture = assetManager.LoadTexture(texturePath, yugaType);
                if (texture) {
                    material->SetTexture(yugaType, texture);
                }
            }
        };

        // Load different texture types
        loadTexture(aiTextureType_DIFFUSE, TextureType::Diffuse);
        loadTexture(aiTextureType_NORMALS, TextureType::Normal);
        loadTexture(aiTextureType_SPECULAR, TextureType::Specular);
        loadTexture(aiTextureType_HEIGHT, TextureType::Height);
        loadTexture(aiTextureType_AMBIENT, TextureType::AO);
        loadTexture(aiTextureType_EMISSIVE, TextureType::Emissive);

        // Load material properties
        aiColor3D color;
        float value;

        if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
            material->SetAlbedo(Vector3(color.r, color.g, color.b));
        }

        if (mat->Get(AI_MATKEY_SHININESS, value) == AI_SUCCESS) {
            // Convert shininess to roughness (inverse relationship)
            material->SetRoughness(1.0f - (value / 128.0f));
        }

        if (mat->Get(AI_MATKEY_OPACITY, value) == AI_SUCCESS) {
            material->SetOpacity(value);
        }
    }

    void Model::Draw() {
        for (size_t i = 0; i < m_Meshes.size(); i++) {
            // Bind material if available
            if (m_Meshes[i]->MaterialIndex < m_Materials.size()) {
                m_Materials[m_Meshes[i]->MaterialIndex]->Bind();
            }

            m_Meshes[i]->Draw();

            // Unbind material
            if (m_Meshes[i]->MaterialIndex < m_Materials.size()) {
                m_Materials[m_Meshes[i]->MaterialIndex]->Unbind();
            }
        }
    }

    void Model::Cleanup() {
        for (auto& mesh : m_Meshes) {
            mesh->Cleanup();
        }
        m_Meshes.clear();
        m_Materials.clear();
        m_IsLoaded = false;
    }

    void Model::SetMaterial(size_t meshIndex, std::shared_ptr<Material> material) {
        if (meshIndex < m_Meshes.size()) {
            m_Meshes[meshIndex]->MaterialIndex = static_cast<unsigned int>(m_Materials.size());
            m_Materials.push_back(material);
        }
    }

} // namespace YUGA
