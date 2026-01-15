#include "Input/Input.h"

namespace YUGA {
    
    GLFWwindow* Input::s_Window = nullptr;
    std::unordered_map<int, bool> Input::s_KeyStates;
    std::unordered_map<int, bool> Input::s_PrevKeyStates;
    std::unordered_map<int, bool> Input::s_MouseStates;
    std::unordered_map<int, bool> Input::s_PrevMouseStates;
    Vector3 Input::s_MousePosition;
    Vector3 Input::s_PrevMousePosition;
    float Input::s_ScrollDelta = 0.0f;
    
    void Input::Initialize(GLFWwindow* window) {
        s_Window = window;
        
        // Get initial mouse position
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        s_MousePosition = Vector3((float)x, (float)y, 0.0f);
        s_PrevMousePosition = s_MousePosition;
    }
    
    void Input::Update() {
        // Update previous states
        s_PrevKeyStates = s_KeyStates;
        s_PrevMouseStates = s_MouseStates;
        s_PrevMousePosition = s_MousePosition;
        
        // Update mouse position
        double x, y;
        glfwGetCursorPos(s_Window, &x, &y);
        s_MousePosition = Vector3((float)x, (float)y, 0.0f);
        
        // Reset scroll delta
        s_ScrollDelta = 0.0f;
    }
    
    bool Input::GetKey(KeyCode key) {
        int state = glfwGetKey(s_Window, (int)key);
        s_KeyStates[(int)key] = (state == GLFW_PRESS);
        return s_KeyStates[(int)key];
    }
    
    bool Input::GetKeyDown(KeyCode key) {
        bool current = GetKey(key);
        bool previous = s_PrevKeyStates[(int)key];
        return current && !previous;
    }
    
    bool Input::GetKeyUp(KeyCode key) {
        bool current = GetKey(key);
        bool previous = s_PrevKeyStates[(int)key];
        return !current && previous;
    }
    
    bool Input::GetMouseButton(MouseButton button) {
        int state = glfwGetMouseButton(s_Window, (int)button);
        s_MouseStates[(int)button] = (state == GLFW_PRESS);
        return s_MouseStates[(int)button];
    }
    
    bool Input::GetMouseButtonDown(MouseButton button) {
        bool current = GetMouseButton(button);
        bool previous = s_PrevMouseStates[(int)button];
        return current && !previous;
    }
    
    bool Input::GetMouseButtonUp(MouseButton button) {
        bool current = GetMouseButton(button);
        bool previous = s_PrevMouseStates[(int)button];
        return !current && previous;
    }
    
    Vector3 Input::GetMousePosition() {
        return s_MousePosition;
    }
    
    Vector3 Input::GetMouseDelta() {
        return s_MousePosition - s_PrevMousePosition;
    }
    
    float Input::GetMouseScrollDelta() {
        return s_ScrollDelta;
    }
    
} // namespace YUGA
