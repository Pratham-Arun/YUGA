#pragma once

#include "Core/Core.h"
#include <string>

namespace YUGA {

    enum class TextureType {
        Diffuse,
        Specular,
        Normal,
        Height,
        Ambient,
        Emissive,
        Metallic,
        Roughness,
        AO
    };

    enum class TextureWrap {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class TextureFilter {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear
    };

    class Texture {
    public:
        Texture();
        ~Texture();

        bool LoadFromFile(const std::string& path, TextureType type = TextureType::Diffuse);
        bool LoadFromMemory(unsigned char* data, int width, int height, int channels);
        
        void Bind(unsigned int slot = 0) const;
        void Unbind() const;
        void Cleanup();

        void SetWrap(TextureWrap wrapS, TextureWrap wrapT);
        void SetFilter(TextureFilter minFilter, TextureFilter magFilter);
        void GenerateMipmaps();

        unsigned int GetID() const { return m_TextureID; }
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        int GetChannels() const { return m_Channels; }
        TextureType GetType() const { return m_Type; }
        const std::string& GetPath() const { return m_Path; }

    private:
        unsigned int m_TextureID = 0;
        int m_Width = 0;
        int m_Height = 0;
        int m_Channels = 0;
        TextureType m_Type = TextureType::Diffuse;
        std::string m_Path;
        bool m_IsLoaded = false;

        unsigned int GetGLWrap(TextureWrap wrap) const;
        unsigned int GetGLFilter(TextureFilter filter) const;
    };

} // namespace YUGA
