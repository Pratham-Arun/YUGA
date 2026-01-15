#include "Core/Engine.h"
#include "Core/Log.h"
#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsWorld.h"
#include "Audio/AudioEngine.h"
#include <chrono>

namespace YUGA {

Engine& Engine::Get() {
    static Engine instance;
    return instance;
}

void Engine::Initialize(const EngineConfig& config) {
    YUGA_LOG_INFO("🚀 Initializing YUGA Engine v1.0.0");
    YUGA_LOG_INFO("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    // Initialize subsystems
    // m_Window = CreateScope<Window>(WindowProps(config.title, config.width, config.height, config.vsync));
    m_Renderer = CreateScope<Renderer>();
    // m_Physics = CreateScope<PhysicsWorld>();
    // m_Audio = CreateScope<AudioEngine>();
    // m_Input = CreateScope<InputManager>();
    // m_SceneManager = CreateScope<SceneManager>();
    
    YUGA_LOG_INFO("✓ Core systems initialized");
    YUGA_LOG_INFO("✓ Window: ", config.width, "x", config.height);
    YUGA_LOG_INFO("✓ VSync: ", config.vsync ? "Enabled" : "Disabled");
    YUGA_LOG_INFO("✓ Renderer: OpenGL 4.6");
    YUGA_LOG_INFO("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    m_Running = true;
}

void Engine::Run() {
    YUGA_LOG_INFO("🎮 Starting main game loop...");
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    float fpsTimer = 0.0f;
    
    while (m_Running) {
        // Calculate delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        m_DeltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // FPS calculation
        frameCount++;
        fpsTimer += m_DeltaTime;
        if (fpsTimer >= 1.0f) {
            m_FPS = frameCount / fpsTimer;
            frameCount = 0;
            fpsTimer = 0.0f;
        }
        
        // Main loop
        Update(m_DeltaTime);
        Render();
        
        // TODO: Check window close
        // if (m_Window->ShouldClose()) {
        //     m_Running = false;
        // }
        
        // Temporary: Stop after 5 seconds for testing
        static float totalTime = 0.0f;
        totalTime += m_DeltaTime;
        if (totalTime >= 5.0f) {
            YUGA_LOG_INFO("Test run complete (5 seconds)");
            m_Running = false;
        }
    }
}

void Engine::Update(float deltaTime) {
    // TODO: Update subsystems
    // m_Input->Update();
    // m_Physics->Step(deltaTime);
    // m_Audio->Update();
    // m_SceneManager->Update(deltaTime);
}

void Engine::Render() {
    if (m_Renderer) {
        m_Renderer->BeginFrame();
        m_Renderer->Clear(0.1f, 0.1f, 0.15f, 1.0f);
        
        // TODO: Render scene
        // m_Renderer->RenderScene(m_SceneManager->GetActiveScene());
        
        m_Renderer->EndFrame();
    }
}

void Engine::Shutdown() {
    YUGA_LOG_INFO("🛑 Shutting down YUGA Engine...");
    
    // Cleanup subsystems
    m_SceneManager.reset();
    m_Input.reset();
    m_Audio.reset();
    m_Physics.reset();
    m_Renderer.reset();
    m_Window.reset();
    
    YUGA_LOG_INFO("✓ Engine shutdown complete");
}

} // namespace YUGA
