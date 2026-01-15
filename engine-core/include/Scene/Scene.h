#pragma once

#include "Core/Core.h"
#include "ECS/Entity.h"
#include <entt/entt.hpp>
#include <string>

namespace YUGA {
    
    class YUGA_API Scene {
    public:
        Scene(const std::string& name = "Untitled");
        ~Scene();
        
        Entity CreateEntity(const std::string& name = "Entity");
        void DestroyEntity(Entity entity);
        
        void OnUpdate(float deltaTime);
        void OnRender();
        
        const std::string& GetName() const { return m_Name; }
        
    private:
        std::string m_Name;
        entt::registry m_Registry;
        
        friend class Entity;
    };
    
} // namespace YUGA
