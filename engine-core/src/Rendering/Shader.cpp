#include "Rendering/Shader.h"
#include "Core/Log.h"

// Note: In real implementation, include OpenGL
// #include <glad/glad.h> or <GL/gl.h>

namespace YUGA {

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    : m_RendererID(0) {
    
    YUGA_LOG_INFO("Compiling shader...");
    
    // TODO: Compile vertex shader
    // uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    
    // TODO: Compile fragment shader
    // uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    
    // TODO: Link program
    // m_RendererID = glCreateProgram();
    // glAttachShader(m_RendererID, vertexShader);
    // glAttachShader(m_RendererID, fragmentShader);
    // glLinkProgram(m_RendererID);
    
    // TODO: Check for link errors
    
    // TODO: Delete shaders (no longer needed after linking)
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);
    
    YUGA_LOG_INFO("✓ Shader compiled successfully");
}

Shader::~Shader() {
    // TODO: Delete program
    // glDeleteProgram(m_RendererID);
}

void Shader::Bind() const {
    // TODO: Use program
    // glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    // TODO: Unbind program
    // glUseProgram(0);
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
    // TODO: Compile shader
    // uint32_t shader = glCreateShader(type);
    // const char* src = source.c_str();
    // glShaderSource(shader, 1, &src, nullptr);
    // glCompileShader(shader);
    
    // TODO: Check for compile errors
    // int success;
    // glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     char infoLog[512];
    //     glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    //     YUGA_LOG_ERROR("Shader compilation failed: ", infoLog);
    // }
    
    // return shader;
    return 0; // Stub
}

void Shader::SetInt(const std::string& name, int value) {
    // TODO: Set uniform
    // glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) {
    // TODO: Set uniform
    // glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetFloat3(const std::string& name, const Vector3& value) {
    // TODO: Set uniform
    // glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, float x, float y, float z, float w) {
    // TODO: Set uniform
    // glUniform4f(GetUniformLocation(name), x, y, z, w);
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    // TODO: Get uniform location
    // int location = glGetUniformLocation(m_RendererID, name.c_str());
    // m_UniformLocationCache[name] = location;
    // return location;
    
    return -1; // Stub
}

} // namespace YUGA
