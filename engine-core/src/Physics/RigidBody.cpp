#include "Physics/RigidBody.h"
#include "Core/Log.h"

namespace YUGA {
    
    RigidBody::RigidBody(CollisionShape shape, float mass)
        : m_ShapeType(shape), m_Mass(mass), m_IsKinematic(false) {
        
        CreateCollisionShape(shape);
        
        // Calculate inertia
        btVector3 localInertia(0, 0, 0);
        if (mass != 0.0f) {
            m_CollisionShape->calculateLocalInertia(mass, localInertia);
        }
        
        // Create motion state
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(0, 0, 0));
        m_MotionState = std::make_unique<btDefaultMotionState>(startTransform);
        
        // Create rigid body
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_MotionState.get(), m_CollisionShape.get(), localInertia);
        m_RigidBody = std::make_unique<btRigidBody>(rbInfo);
        
        Log::Info("RigidBody created");
    }
    
    RigidBody::~RigidBody() {
        m_RigidBody.reset();
        m_MotionState.reset();
        m_CollisionShape.reset();
    }
    
    void RigidBody::CreateCollisionShape(CollisionShape shape) {
        switch (shape) {
            case CollisionShape::Box:
                m_CollisionShape = std::make_unique<btBoxShape>(btVector3(0.5f, 0.5f, 0.5f));
                break;
            case CollisionShape::Sphere:
                m_CollisionShape = std::make_unique<btSphereShape>(0.5f);
                break;
            case CollisionShape::Capsule:
                m_CollisionShape = std::make_unique<btCapsuleShape>(0.5f, 1.0f);
                break;
            case CollisionShape::Mesh:
                // For mesh, we'd need actual mesh data
                m_CollisionShape = std::make_unique<btBoxShape>(btVector3(0.5f, 0.5f, 0.5f));
                Log::Warn("Mesh collision shape not fully implemented, using box");
                break;
        }
    }
    
    void RigidBody::SetPosition(const Vector3& position) {
        btTransform transform;
        m_RigidBody->getMotionState()->getWorldTransform(transform);
        transform.setOrigin(btVector3(position.x, position.y, position.z));
        m_RigidBody->setWorldTransform(transform);
        m_RigidBody->getMotionState()->setWorldTransform(transform);
    }
    
    Vector3 RigidBody::GetPosition() const {
        btTransform transform;
        m_RigidBody->getMotionState()->getWorldTransform(transform);
        btVector3 origin = transform.getOrigin();
        return Vector3(origin.x(), origin.y(), origin.z());
    }
    
    void RigidBody::SetRotation(const btQuaternion& rotation) {
        btTransform transform;
        m_RigidBody->getMotionState()->getWorldTransform(transform);
        transform.setRotation(rotation);
        m_RigidBody->setWorldTransform(transform);
        m_RigidBody->getMotionState()->setWorldTransform(transform);
    }
    
    btQuaternion RigidBody::GetRotation() const {
        btTransform transform;
        m_RigidBody->getMotionState()->getWorldTransform(transform);
        return transform.getRotation();
    }
    
    void RigidBody::ApplyForce(const Vector3& force) {
        m_RigidBody->activate();
        m_RigidBody->applyCentralForce(btVector3(force.x, force.y, force.z));
    }
    
    void RigidBody::ApplyImpulse(const Vector3& impulse) {
        m_RigidBody->activate();
        m_RigidBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
    }
    
    void RigidBody::SetMass(float mass) {
        m_Mass = mass;
        
        btVector3 localInertia(0, 0, 0);
        if (mass != 0.0f) {
            m_CollisionShape->calculateLocalInertia(mass, localInertia);
        }
        
        m_RigidBody->setMassProps(mass, localInertia);
    }
    
    void RigidBody::SetKinematic(bool kinematic) {
        m_IsKinematic = kinematic;
        
        if (kinematic) {
            m_RigidBody->setCollisionFlags(m_RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            m_RigidBody->setActivationState(DISABLE_DEACTIVATION);
        } else {
            m_RigidBody->setCollisionFlags(m_RigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
            m_RigidBody->forceActivationState(ACTIVE_TAG);
        }
    }
    
} // namespace YUGA
