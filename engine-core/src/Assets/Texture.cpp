#include "Assets/Texture.h"
#include "Core/Log.h"
#include <glad/glad.h>

// STB Image will be included here
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace YUGA {

    Texture::Texture() {
        stbi_set_flip_vertically_on_load(true);
    }

    Texture::~Texture() {
        Cleanup();
    }

    bool Texture::LoadFromFile(const std::string& path, TextureType type) {
        if (m_IsLoaded) {
            Cleanup();
        }

        m_Path = path;
        m_Type = type;

        unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
        
        if (!data) {
            LOG_ERROR("Failed to load texture: {}", path);
            return false;
        }

        bool success = LoadFromMemory(data, m_Width, m_Height, m_Channels);
        stbi_image_free(data);

        if (success) {
            LOG_INFO("Loaded texture: {} ({}x{}, {} channels)", path, m_Width, m_Height, m_Channels);
        }

        return success;
    }

    bool Texture::LoadFromMemory(unsigned char* data, int width, int height, int channels) {
        if (!data) {
            LOG_ERROR("Invalid texture data");
            return false;
        }

        m_Width = width;
        m_Height = height;
        m_Channels = channels;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        // Determine format
        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGB;
        
        if (channels == 1) {
            format = internalFormat = GL_RED;
        } else if (channels == 3) {
            format = internalFormat = GL_RGB;
        } else if (channels == 4) {
            format = internalFormat = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        // Set default parameters
        SetWrap(TextureWrap::Repeat, TextureWrap::Repeat);
        SetFilter(TextureFilter::LinearMipmapLinear, TextureFilter::Linear);
        GenerateMipmaps();

        glBindTexture(GL_TEXTURE_2D, 0);

        m_IsLoaded = true;
        return true;
    }

    void Texture::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Cleanup() {
        if (m_IsLoaded && m_TextureID != 0) {
            glDeleteTextures(1, &m_TextureID);
            m_TextureID = 0;
            m_IsLoaded = false;
        }
    }

    void Texture::SetWrap(TextureWrap wrapS, TextureWrap wrapT) {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLWrap(wrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLWrap(wrapT));
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::SetFilter(TextureFilter minFilter, TextureFilter magFilter) {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLFilter(minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLFilter(magFilter));
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::GenerateMipmaps() {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int Texture::GetGLWrap(TextureWrap wrap) const {
        switch (wrap) {
            case TextureWrap::Repeat:          return GL_REPEAT;
            case TextureWrap::MirroredRepeat:  return GL_MIRRORED_REPEAT;
            case TextureWrap::ClampToEdge:     return GL_CLAMP_TO_EDGE;
            case TextureWrap::ClampToBorder:   return GL_CLAMP_TO_BORDER;
            default:                           return GL_REPEAT;
        }
    }

    unsigned int Texture::GetGLFilter(TextureFilter filter) const {
        switch (filter) {
            case TextureFilter::Nearest:                return GL_NEAREST;
            case TextureFilter::Linear:                 return GL_LINEAR;
            case TextureFilter::NearestMipmapNearest:   return GL_NEAREST_MIPMAP_NEAREST;
            case TextureFilter::LinearMipmapNearest:    return GL_LINEAR_MIPMAP_NEAREST;
            case TextureFilter::NearestMipmapLinear:    return GL_NEAREST_MIPMAP_LINEAR;
            case TextureFilter::LinearMipmapLinear:     return GL_LINEAR_MIPMAP_LINEAR;
            default:                                    return GL_LINEAR;
        }
    }

} // namespace YUGA
