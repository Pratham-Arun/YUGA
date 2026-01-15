#pragma once

#include "Core/Core.h"
#include <btBulletDynamicsCommon.h>
#include <memory>
#include <vector>

namespace YUGA {
    
    class RigidBody;
    
    /**
     * @brief Physics simulation world using Bullet3
     */
    class PhysicsWorld {
    public:
        PhysicsWorld();
        ~PhysicsWorld();
        
        void Initialize();
        void Update(float deltaTime);
        void Shutdown();
        
        // Gravity
        void SetGravity(const btVector3& gravity);
        btVector3 GetGravity() const;
        
        // Rigid body management
        void AddRigidBody(RigidBody* body);
        void RemoveRigidBody(RigidBody* body);
        
        // Raycasting
        bool Raycast(const btVector3& from, const btVector3& to, btVector3& hitPoint);
        
        btDiscreteDynamicsWorld* GetWorld() { return m_DynamicsWorld.get(); }
        
    private:
        std::unique_ptr<btDefaultCollisionConfiguration> m_CollisionConfiguration;
        std::unique_ptr<btCollisionDispatcher> m_Dispatcher;
        std::unique_ptr<btBroadphaseInterface> m_Broadphase;
        std::unique_ptr<btSequentialImpulseConstraintSolver> m_Solver;
        std::unique_ptr<btDiscreteDynamicsWorld> m_DynamicsWorld;
        
        std::vector<RigidBody*> m_RigidBodies;
    };
    
} // namespace YUGA
