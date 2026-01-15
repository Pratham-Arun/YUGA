#pragma once

#include "Core/Core.h"
#include <string>
#include <functional>

// Forward declare GLFW types to avoid including GLFW in header
struct GLFWwindow;

namespace YUGA {

struct WindowProps {
    std::string title;
    uint32_t width;
    uint32_t height;
    bool vsync;
    
    WindowProps(const std::string& title = "YUGA Engine",
                uint32_t width = 1920,
                uint32_t height = 1080,
                bool vsync = true)
        : title(title), width(width), height(height), vsync(vsync) {}
};

class Window {
public:
    using EventCallbackFn = std::function<void()>;
    
    Window(const WindowProps& props);
    ~Window();
    
    void OnUpdate();
    
    uint32_t GetWidth() const { return m_Data.width; }
    uint32_t GetHeight() const { return m_Data.height; }
    
    void SetVSync(bool enabled);
    bool IsVSync() const { return m_Data.vsync; }
    
    bool ShouldClose() const;
    
    void* GetNativeWindow() const { return m_Window; }
    
private:
    void Init(const WindowProps& props);
    void Shutdown();
    
private:
    GLFWwindow* m_Window;
    
    struct WindowData {
        std::string title;
        uint32_t width, height;
        bool vsync;
    };
    
    WindowData m_Data;
};

} // namespace YUGA
