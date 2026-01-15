#include "Editor/EditorLayer.h"
#include "Scene/Scene.h"
#include "ECS/Components.h"
#include "Core/Log.h"

namespace YUGA {
    
    EditorLayer::EditorLayer() {
    }
    
    EditorLayer::~EditorLayer() {
    }
    
    void EditorLayer::OnAttach() {
        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        ImGui::StyleColorsDark();
        
        Log::Info("Editor layer attached");
    }
    
    void EditorLayer::OnDetach() {
        ImGui::DestroyContext();
        Log::Info("Editor layer detached");
    }
    
    void EditorLayer::OnUpdate(float deltaTime) {
        // Update editor logic
    }
    
    void EditorLayer::OnRender() {
        // Start ImGui frame
        ImGui::NewFrame();
        
        // Dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        
        // Draw all panels
        DrawMenuBar();
        
        if (m_ShowSceneHierarchy)
            DrawSceneHierarchy();
        
        if (m_ShowInspector)
            DrawInspector();
        
        if (m_ShowAssetBrowser)
            DrawAssetBrowser();
        
        if (m_ShowConsole)
            DrawConsole();
        
        DrawViewport();
        
        // Render ImGui
        ImGui::Render();
    }
    
    void EditorLayer::SetActiveScene(Scene* scene) {
        m_ActiveScene = scene;
    }
    
    void EditorLayer::DrawMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene")) {
                    // Create new scene
                }
                if (ImGui::MenuItem("Open Scene")) {
                    // Open scene dialog
                }
                if (ImGui::MenuItem("Save Scene")) {
                    // Save current scene
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    // Exit application
                }
                ImGui::EndMenu();
            }
            
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo")) {}
                if (ImGui::MenuItem("Redo")) {}
                ImGui::EndMenu();
            }
            
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Scene Hierarchy", nullptr, &m_ShowSceneHierarchy);
                ImGui::MenuItem("Inspector", nullptr, &m_ShowInspector);
                ImGui::MenuItem("Asset Browser", nullptr, &m_ShowAssetBrowser);
                ImGui::MenuItem("Console", nullptr, &m_ShowConsole);
                ImGui::EndMenu();
            }
            
            ImGui::EndMainMenuBar();
        }
    }
    
    void EditorLayer::DrawSceneHierarchy() {
        ImGui::Begin("Scene Hierarchy");
        
        if (m_ActiveScene) {
            ImGui::Text("Scene: %s", m_ActiveScene->GetName().c_str());
            ImGui::Separator();
            
            // List all entities
            // In real implementation, iterate through registry
            if (ImGui::Button("Create Entity")) {
                m_ActiveScene->CreateEntity("New Entity");
            }
        }
        
        ImGui::End();
    }
    
    void EditorLayer::DrawInspector() {
        ImGui::Begin("Inspector");
        
        if (m_SelectedEntity) {
            // Draw components
            if (m_SelectedEntity.HasComponent<TagComponent>()) {
                auto& tag = m_SelectedEntity.GetComponent<TagComponent>();
                char buffer[256];
                strcpy(buffer, tag.Tag.c_str());
                if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                    tag.Tag = buffer;
                }
            }
            
            if (m_SelectedEntity.HasComponent<TransformComponent>()) {
                auto& transform = m_SelectedEntity.GetComponent<TransformComponent>();
                ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
                ImGui::DragFloat3("Rotation", &transform.Rotation.x, 0.1f);
                ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
            }
        }
        
        ImGui::End();
    }
    
    void EditorLayer::DrawAssetBrowser() {
        ImGui::Begin("Asset Browser");
        
        ImGui::Text("Assets/");
        ImGui::Separator();
        
        // List assets
        // In real implementation, scan asset directory
        
        ImGui::End();
    }
    
    void EditorLayer::DrawConsole() {
        ImGui::Begin("Console");
        
        // Display log messages
        ImGui::Text("Console output...");
        
        ImGui::End();
    }
    
    void EditorLayer::DrawViewport() {
        ImGui::Begin("Viewport");
        
        // Render scene to texture and display
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        ImGui::Text("Viewport: %.0fx%.0f", viewportSize.x, viewportSize.y);
        
        ImGui::End();
    }
    
} // namespace YUGA
