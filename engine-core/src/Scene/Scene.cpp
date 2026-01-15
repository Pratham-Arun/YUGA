#include "Scene/Scene.h"
#include "ECS/Components.h"
#include "Core/Log.h"

namespace YUGA {
    
    Scene::Scene(const std::string& name)
        : m_Name(name) {
        Log::Info("Scene created: " + name);
    }
    
    Scene::~Scene() {
        Log::Info("Scene destroyed: " + m_Name);
    }
    
    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TagComponent>(name);
        entity.AddComponent<TransformComponent>();
        return entity;
    }
    
    void Scene::DestroyEntity(Entity entity) {
        m_Registry.destroy(entity);
    }
    
    void Scene::OnUpdate(float deltaTime) {
        // Update all systems here
        // Physics, scripts, etc.
    }
    
    void Scene::OnRender() {
        // Render all entities with MeshComponent
        auto view = m_Registry.view<TransformComponent, MeshComponent>();
        for (auto entity : view) {
            auto& transform = view.get<TransformComponent>(entity);
            auto& mesh = view.get<MeshComponent>(entity);
            // Render mesh at transform position
        }
    }
    
} // namespace YUGA
