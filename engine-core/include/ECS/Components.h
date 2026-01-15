#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <string>

namespace YUGA {
    
    struct TagComponent {
        std::string Tag;
        
        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
    };
    
    struct TransformComponent {
        Vector3 Position{ 0.0f, 0.0f, 0.0f };
        Vector3 Rotation{ 0.0f, 0.0f, 0.0f };
        Vector3 Scale{ 1.0f, 1.0f, 1.0f };
        
        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Vector3& position)
            : Position(position) {}
    };
    
    struct MeshComponent {
        uint32_t MeshId = 0;
        uint32_t MaterialId = 0;
        
        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
    };
    
    struct CameraComponent {
        float FOV = 45.0f;
        float NearClip = 0.1f;
        float FarClip = 1000.0f;
        bool Primary = true;
        
        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };
    
    struct ScriptComponent {
        std::string ScriptName;
        
        ScriptComponent() = default;
        ScriptComponent(const ScriptComponent&) = default;
        ScriptComponent(const std::string& name) : ScriptName(name) {}
    };
    
    struct RigidBodyComponent {
        float Mass = 1.0f;
        bool IsKinematic = false;
        Vector3 Velocity{ 0.0f, 0.0f, 0.0f };
        
        RigidBodyComponent() = default;
        RigidBodyComponent(const RigidBodyComponent&) = default;
    };
    
    struct AudioSourceComponent {
        uint32_t ClipId = 0;
        float Volume = 1.0f;
        float Pitch = 1.0f;
        bool Loop = false;
        bool PlayOnAwake = false;
        bool Is3D = true;
        
        AudioSourceComponent() = default;
        AudioSourceComponent(const AudioSourceComponent&) = default;
    };
    
    struct LightComponent {
        enum class Type { Directional, Point, Spot };
        
        Type LightType = Type::Point;
        Vector3 Color{ 1.0f, 1.0f, 1.0f };
        float Intensity = 1.0f;
        float Range = 10.0f;
        
        LightComponent() = default;
        LightComponent(const LightComponent&) = default;
    };
    
    struct ParticleSystemComponent {
        uint32_t MaxParticles = 1000;
        float EmissionRate = 10.0f;
        float Lifetime = 5.0f;
        Vector3 StartVelocity{ 0.0f, 1.0f, 0.0f };
        
        ParticleSystemComponent() = default;
        ParticleSystemComponent(const ParticleSystemComponent&) = default;
    };
    
    struct ColliderComponent {
        enum class Shape { Box, Sphere, Capsule, Mesh };
        
        Shape ColliderShape = Shape::Box;
        Vector3 Size{ 1.0f, 1.0f, 1.0f };
        Vector3 Center{ 0.0f, 0.0f, 0.0f };
        bool IsTrigger = false;
        
        ColliderComponent() = default;
        ColliderComponent(const ColliderComponent&) = default;
    };
    
} // namespace YUGA
