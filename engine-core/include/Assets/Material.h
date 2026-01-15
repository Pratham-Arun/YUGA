#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include "Assets/Texture.h"
#include "Rendering/Shader.h"
#include <memory>
#include <vector>
#include <string>

namespace YUGA {

    struct MaterialProperties {
        Vector3 Albedo = Vector3(1.0f, 1.0f, 1.0f);
        float Metallic = 0.0f;
        float Roughness = 0.5f;
        float AO = 1.0f;
        Vector3 Emissive = Vector3(0.0f, 0.0f, 0.0f);
        float EmissiveStrength = 0.0f;
        float Opacity = 1.0f;
    };

    class Material {
    public:
        Material(const std::string& name = "Default Material");
        ~Material();

        void SetShader(std::shared_ptr<Shader> shader);
        void SetTexture(TextureType type, std::shared_ptr<Texture> texture);
        void RemoveTexture(TextureType type);

        void SetAlbedo(const Vector3& color) { m_Properties.Albedo = color; }
        void SetMetallic(float metallic) { m_Properties.Metallic = metallic; }
        void SetRoughness(float roughness) { m_Properties.Roughness = roughness; }
        void SetAO(float ao) { m_Properties.AO = ao; }
        void SetEmissive(const Vector3& color, float strength = 1.0f);
        void SetOpacity(float opacity) { m_Properties.Opacity = opacity; }

        void Bind();
        void Unbind();
        void ApplyProperties();

        std::shared_ptr<Shader> GetShader() const { return m_Shader; }
        const MaterialProperties& GetProperties() const { return m_Properties; }
        const std::string& GetName() const { return m_Name; }

        bool HasTexture(TextureType type) const;
        std::shared_ptr<Texture> GetTexture(TextureType type) const;

    private:
        std::string m_Name;
        std::shared_ptr<Shader> m_Shader;
        MaterialProperties m_Properties;
        std::vector<std::pair<TextureType, std::shared_ptr<Texture>>> m_Textures;

        int GetTextureSlot(TextureType type) const;
        const char* GetTextureUniformName(TextureType type) const;
    };

} // namespace YUGA
