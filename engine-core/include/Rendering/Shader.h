#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <string>
#include <unordered_map>

namespace YUGA {

class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    // Uniform setters
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetFloat3(const std::string& name, const Vector3& value);
    void SetFloat4(const std::string& name, float x, float y, float z, float w);
    
    uint32_t GetRendererID() const { return m_RendererID; }
    
private:
    uint32_t CompileShader(uint32_t type, const std::string& source);
    int GetUniformLocation(const std::string& name);
    
private:
    uint32_t m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

} // namespace YUGA
