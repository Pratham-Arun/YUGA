#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <btBulletDynamicsCommon.h>
#include <memory>

namespace YUGA {
    
    enum class CollisionShape {
        Box,
        Sphere,
        Capsule,
        Mesh
    };
    
    class YUGA_API RigidBody {
    public:
        RigidBody(CollisionShape shape, float mass);
        ~RigidBody();
        
        void SetPosition(const Vector3& position);
        Vector3 GetPosition() const;
        
        void SetRotation(const btQuaternion& rotation);
        btQuaternion GetRotation() const;
        
        void ApplyForce(const Vector3& force);
        void ApplyImpulse(const Vector3& impulse);
        
        void SetMass(float mass);
        float GetMass() const { return m_Mass; }
        
        void SetKinematic(bool kinematic);
        bool IsKinematic() const { return m_IsKinematic; }
        
        btRigidBody* GetBulletBody() { return m_RigidBody.get(); }
        
    private:
        void CreateCollisionShape(CollisionShape shape);
        
        CollisionShape m_ShapeType;
        float m_Mass;
        bool m_IsKinematic;
        
        std::unique_ptr<btCollisionShape> m_CollisionShape;
        std::unique_ptr<btDefaultMotionState> m_MotionState;
        std::unique_ptr<btRigidBody> m_RigidBody;
    };
    
} // namespace YUGA
