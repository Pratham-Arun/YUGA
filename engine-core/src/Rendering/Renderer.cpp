#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Core/Log.h"

namespace YUGA {

// Default shaders
static const char* s_DefaultVertexShader = R"(
    #version 330 core
    layout(location = 0) in vec3 a_Position;
    layout(location = 1) in vec3 a_Color;
    
    out vec3 v_Color;
    
    void main() {
        v_Color = a_Color;
        gl_Position = vec4(a_Position, 1.0);
    }
)";

static const char* s_DefaultFragmentShader = R"(
    #version 330 core
    layout(location = 0) out vec4 color;
    
    in vec3 v_Color;
    
    void main() {
        color = vec4(v_Color, 1.0);
    }
)";

Renderer::Renderer() {
    Init();
}

Renderer::~Renderer() {
    Shutdown();
}

void Renderer::Init() {
    YUGA_LOG_INFO("Initializing Renderer...");
    
    // TODO: Initialize OpenGL
    // gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    // TODO: Set OpenGL options
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Create default shader
    // m_DefaultShader = CreateRef<Shader>(s_DefaultVertexShader, s_DefaultFragmentShader);
    
    YUGA_LOG_INFO("✓ Renderer initialized");
    YUGA_LOG_INFO("  Graphics API: OpenGL 4.6");
}

void Renderer::Shutdown() {
    YUGA_LOG_INFO("✓ Renderer shutdown");
}

void Renderer::BeginFrame() {
    ResetStats();
}

void Renderer::EndFrame() {
    // Stats are accumulated during frame
}

void Renderer::Clear(float r, float g, float b, float a) {
    // TODO: Clear screen
    // glClearColor(r, g, b, a);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawTriangle() {
    // TODO: Draw triangle
    m_Stats.drawCalls++;
    m_Stats.triangles++;
    m_Stats.vertices += 3;
}

void Renderer::DrawQuad() {
    // TODO: Draw quad (2 triangles)
    m_Stats.drawCalls++;
    m_Stats.triangles += 2;
    m_Stats.vertices += 4;
}

void Renderer::DrawCube() {
    // TODO: Draw cube (12 triangles)
    m_Stats.drawCalls++;
    m_Stats.triangles += 12;
    m_Stats.vertices += 8;
}

void Renderer::ResetStats() {
    m_Stats.drawCalls = 0;
    m_Stats.triangles = 0;
    m_Stats.vertices = 0;
}

} // namespace YUGA
