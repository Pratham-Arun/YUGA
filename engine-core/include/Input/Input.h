#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace YUGA {
    
    enum class KeyCode {
        // Letters
        A = GLFW_KEY_A, B = GLFW_KEY_B, C = GLFW_KEY_C, D = GLFW_KEY_D,
        E = GLFW_KEY_E, F = GLFW_KEY_F, G = GLFW_KEY_G, H = GLFW_KEY_H,
        // Numbers
        Key0 = GLFW_KEY_0, Key1 = GLFW_KEY_1, Key2 = GLFW_KEY_2,
        // Special
        Space = GLFW_KEY_SPACE, Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER, Tab = GLFW_KEY_TAB,
        // Arrows
        Left = GLFW_KEY_LEFT, Right = GLFW_KEY_RIGHT,
        Up = GLFW_KEY_UP, Down = GLFW_KEY_DOWN,
        // Modifiers
        LeftShift = GLFW_KEY_LEFT_SHIFT, LeftControl = GLFW_KEY_LEFT_CONTROL
    };
    
    enum class MouseButton {
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Right = GLFW_MOUSE_BUTTON_RIGHT,
        Middle = GLFW_MOUSE_BUTTON_MIDDLE
    };
    
    class YUGA_API Input {
    public:
        static void Initialize(GLFWwindow* window);
        static void Update();
        
        // Keyboard
        static bool GetKey(KeyCode key);
        static bool GetKeyDown(KeyCode key);
        static bool GetKeyUp(KeyCode key);
        
        // Mouse
        static bool GetMouseButton(MouseButton button);
        static bool GetMouseButtonDown(MouseButton button);
        static bool GetMouseButtonUp(MouseButton button);
        
        static Vector3 GetMousePosition();
        static Vector3 GetMouseDelta();
        static float GetMouseScrollDelta();
        
    private:
        static GLFWwindow* s_Window;
        static std::unordered_map<int, bool> s_KeyStates;
        static std::unordered_map<int, bool> s_PrevKeyStates;
        static std::unordered_map<int, bool> s_MouseStates;
        static std::unordered_map<int, bool> s_PrevMouseStates;
        static Vector3 s_MousePosition;
        static Vector3 s_PrevMousePosition;
        static float s_ScrollDelta;
    };
    
} // namespace YUGA
