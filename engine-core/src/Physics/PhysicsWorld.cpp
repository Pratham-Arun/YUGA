#include "Physics/PhysicsWorld.h"
#include "Physics/RigidBody.h"
#include "Core/Log.h"

namespace YUGA {
    
    PhysicsWorld::PhysicsWorld() {
    }
    
    PhysicsWorld::~PhysicsWorld() {
        Shutdown();
    }
    
    void PhysicsWorld::Initialize() {
        // Collision configuration
        m_CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
        
        // Dispatcher
        m_Dispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfiguration.get());
        
        // Broadphase
        m_Broadphase = std::make_unique<btDbvtBroadphase>();
        
        // Solver
        m_Solver = std::make_unique<btSequentialImpulseConstraintSolver>();
        
        // Dynamics world
        m_DynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
            m_Dispatcher.get(),
            m_Broadphase.get(),
            m_Solver.get(),
            m_CollisionConfiguration.get()
        );
        
        // Set default gravity
        m_DynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
        
        Log::Info("Physics world initialized");
    }
    
    void PhysicsWorld::Update(float deltaTime) {
        if (m_DynamicsWorld) {
            m_DynamicsWorld->stepSimulation(deltaTime, 10);
        }
    }
    
    void PhysicsWorld::Shutdown() {
        m_RigidBodies.clear();
        m_DynamicsWorld.reset();
        m_Solver.reset();
        m_Broadphase.reset();
        m_Dispatcher.reset();
        m_CollisionConfiguration.reset();
        
        Log::Info("Physics world shutdown");
    }
    
    void PhysicsWorld::SetGravity(const btVector3& gravity) {
        if (m_DynamicsWorld) {
            m_DynamicsWorld->setGravity(gravity);
        }
    }
    
    btVector3 PhysicsWorld::GetGravity() const {
        if (m_DynamicsWorld) {
            return m_DynamicsWorld->getGravity();
        }
        return btVector3(0, 0, 0);
    }
    
    void PhysicsWorld::AddRigidBody(RigidBody* body) {
        if (body && m_DynamicsWorld) {
            m_DynamicsWorld->addRigidBody(body->GetBulletBody());
            m_RigidBodies.push_back(body);
        }
    }
    
    void PhysicsWorld::RemoveRigidBody(RigidBody* body) {
        if (body && m_DynamicsWorld) {
            m_DynamicsWorld->removeRigidBody(body->GetBulletBody());
            auto it = std::find(m_RigidBodies.begin(), m_RigidBodies.end(), body);
            if (it != m_RigidBodies.end()) {
                m_RigidBodies.erase(it);
            }
        }
    }
    
    bool PhysicsWorld::Raycast(const btVector3& from, const btVector3& to, btVector3& hitPoint) {
        if (!m_DynamicsWorld) return false;
        
        btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);
        m_DynamicsWorld->rayTest(from, to, rayCallback);
        
        if (rayCallback.hasHit()) {
            hitPoint = rayCallback.m_hitPointWorld;
            return true;
        }
        
        return false;
    }
    
} // namespace YUGA
