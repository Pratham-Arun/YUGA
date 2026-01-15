#include "Assets/Material.h"
#include "Core/Log.h"

namespace YUGA {

    Material::Material(const std::string& name)
        : m_Name(name) {
    }

    Material::~Material() {
    }

    void Material::SetShader(std::shared_ptr<Shader> shader) {
        m_Shader = shader;
    }

    void Material::SetTexture(TextureType type, std::shared_ptr<Texture> texture) {
        // Remove existing texture of this type
        RemoveTexture(type);
        
        // Add new texture
        m_Textures.push_back({type, texture});
    }

    void Material::RemoveTexture(TextureType type) {
        m_Textures.erase(
            std::remove_if(m_Textures.begin(), m_Textures.end(),
                [type](const auto& pair) { return pair.first == type; }),
            m_Textures.end()
        );
    }

    void Material::SetEmissive(const Vector3& color, float strength) {
        m_Properties.Emissive = color;
        m_Properties.EmissiveStrength = strength;
    }

    void Material::Bind() {
        if (!m_Shader) {
            LOG_WARN("Material '{}' has no shader", m_Name);
            return;
        }

        m_Shader->Bind();
        
        // Bind textures
        for (size_t i = 0; i < m_Textures.size(); ++i) {
            const auto& [type, texture] = m_Textures[i];
            int slot = GetTextureSlot(type);
            texture->Bind(slot);
            m_Shader->SetInt(GetTextureUniformName(type), slot);
        }

        ApplyProperties();
    }

    void Material::Unbind() {
        if (m_Shader) {
            m_Shader->Unbind();
        }
    }

    void Material::ApplyProperties() {
        if (!m_Shader) return;

        m_Shader->SetFloat3("u_Material.albedo", m_Properties.Albedo);
        m_Shader->SetFloat("u_Material.metallic", m_Properties.Metallic);
        m_Shader->SetFloat("u_Material.roughness", m_Properties.Roughness);
        m_Shader->SetFloat("u_Material.ao", m_Properties.AO);
        m_Shader->SetFloat3("u_Material.emissive", m_Properties.Emissive);
        m_Shader->SetFloat("u_Material.emissiveStrength", m_Properties.EmissiveStrength);
        m_Shader->SetFloat("u_Material.opacity", m_Properties.Opacity);

        // Set texture flags
        m_Shader->SetInt("u_Material.hasAlbedoMap", HasTexture(TextureType::Diffuse) ? 1 : 0);
        m_Shader->SetInt("u_Material.hasNormalMap", HasTexture(TextureType::Normal) ? 1 : 0);
        m_Shader->SetInt("u_Material.hasMetallicMap", HasTexture(TextureType::Metallic) ? 1 : 0);
        m_Shader->SetInt("u_Material.hasRoughnessMap", HasTexture(TextureType::Roughness) ? 1 : 0);
        m_Shader->SetInt("u_Material.hasAOMap", HasTexture(TextureType::AO) ? 1 : 0);
        m_Shader->SetInt("u_Material.hasEmissiveMap", HasTexture(TextureType::Emissive) ? 1 : 0);
    }

    bool Material::HasTexture(TextureType type) const {
        for (const auto& [texType, texture] : m_Textures) {
            if (texType == type) return true;
        }
        return false;
    }

    std::shared_ptr<Texture> Material::GetTexture(TextureType type) const {
        for (const auto& [texType, texture] : m_Textures) {
            if (texType == type) return texture;
        }
        return nullptr;
    }

    int Material::GetTextureSlot(TextureType type) const {
        switch (type) {
            case TextureType::Diffuse:   return 0;
            case TextureType::Normal:    return 1;
            case TextureType::Metallic:  return 2;
            case TextureType::Roughness: return 3;
            case TextureType::AO:        return 4;
            case TextureType::Emissive:  return 5;
            case TextureType::Specular:  return 6;
            case TextureType::Height:    return 7;
            default:                     return 0;
        }
    }

    const char* Material::GetTextureUniformName(TextureType type) const {
        switch (type) {
            case TextureType::Diffuse:   return "u_AlbedoMap";
            case TextureType::Normal:    return "u_NormalMap";
            case TextureType::Metallic:  return "u_MetallicMap";
            case TextureType::Roughness: return "u_RoughnessMap";
            case TextureType::AO:        return "u_AOMap";
            case TextureType::Emissive:  return "u_EmissiveMap";
            case TextureType::Specular:  return "u_SpecularMap";
            case TextureType::Height:    return "u_HeightMap";
            default:                     return "u_Texture";
        }
    }

} // namespace YUGA
