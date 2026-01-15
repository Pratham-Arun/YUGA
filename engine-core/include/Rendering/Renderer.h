#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"

namespace YUGA {

class Shader;

struct RenderStats {
    uint32_t drawCalls = 0;
    uint32_t triangles = 0;
    uint32_t vertices = 0;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void Init();
    void Shutdown();
    
    void BeginFrame();
    void EndFrame();
    
    void Clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
    
    // Draw commands
    void DrawTriangle();
    void DrawQuad();
    void DrawCube();
    
    const RenderStats& GetStats() const { return m_Stats; }
    void ResetStats();
    
private:
    RenderStats m_Stats;
    Ref<Shader> m_DefaultShader;
};

} // namespace YUGA
