#pragma once

#include "Core/Core.h"
#include <imgui.h>
#include <string>

namespace YUGA {
    
    class Scene;
    class Entity;
    
    class YUGA_API EditorLayer {
    public:
        EditorLayer();
        ~EditorLayer();
        
        void OnAttach();
        void OnDetach();
        void OnUpdate(float deltaTime);
        void OnRender();
        
        void SetActiveScene(Scene* scene);
        
    private:
        void DrawMenuBar();
        void DrawSceneHierarchy();
        void DrawInspector();
        void DrawAssetBrowser();
        void DrawConsole();
        void DrawViewport();
        
        Scene* m_ActiveScene = nullptr;
        Entity m_SelectedEntity;
        
        bool m_ShowSceneHierarchy = true;
        bool m_ShowInspector = true;
        bool m_ShowAssetBrowser = true;
        bool m_ShowConsole = true;
    };
    
} // namespace YUGA
