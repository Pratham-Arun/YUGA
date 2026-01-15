#pragma once

#include "Core/Core.h"
#include <string>
#include <memory>

namespace YUGA {

// Forward declarations
class Window;
class Renderer;
class PhysicsWorld;
class AudioEngine;
class InputManager;
class SceneManager;

struct EngineConfig {
    std::string title = "YUGA Engine";
    uint32_t width = 1920;
    uint32_t height = 1080;
    bool fullscreen = false;
    bool vsync = true;
};

class Engine {
public:
    static Engine& Get();
    
    void Initialize(const EngineConfig& config = {});
    void Run();
    void Shutdown();
    
    bool IsRunning() const { return m_Running; }
    void Stop() { m_Running = false; }
    
    float GetDeltaTime() const { return m_DeltaTime; }
    float GetFPS() const { return m_FPS; }
    
private:
    Engine() = default;
    ~Engine() = default;
    
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    
    void Update(float deltaTime);
    void Render();
    
private:
    bool m_Running = false;
    float m_DeltaTime = 0.0f;
    float m_FPS = 0.0f;
    
    Scope<Window> m_Window;
    Scope<Renderer> m_Renderer;
    Scope<PhysicsWorld> m_Physics;
    Scope<AudioEngine> m_Audio;
    Scope<InputManager> m_Input;
    Scope<SceneManager> m_SceneManager;
};

} // namespace YUGA
