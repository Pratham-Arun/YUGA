#pragma once
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Transform.h"
#include <vector>

namespace YUGA {

struct Particle {
    Vector3 position;
    Vector3 velocity;
    Vector4 color;
    float size;
    float lifetime;
    float age;
    bool active;
    
    Particle() : size(1.0f), lifetime(1.0f), age(0.0f), active(false) {}
};

struct ParticleEmitterSettings {
    // Emission
    float emissionRate;      // Particles per second
    int maxParticles;
    float duration;          // -1 for infinite
    bool looping;
    
    // Particle properties
    float startLifetime;
    float startSpeed;
    float startSize;
    Vector4 startColor;
    
    // Randomness ranges
    float lifetimeVariation;
    float speedVariation;
    float sizeVariation;
    
    // Physics
    Vector3 gravity;
    float drag;
    
    // Shape
    enum class EmissionShape {
        Point,
        Sphere,
        Box,
        Cone
    } shape;
    
    float shapeRadius;
    Vector3 shapeSize;
    float coneAngle;
    
    ParticleEmitterSettings()
        : emissionRate(10.0f)
        , maxParticles(100)
        , duration(-1.0f)
        , looping(true)
        , startLifetime(5.0f)
        , startSpeed(5.0f)
        , startSize(1.0f)
        , startColor(1.0f, 1.0f, 1.0f, 1.0f)
        , lifetimeVariation(0.0f)
        , speedVariation(0.0f)
        , sizeVariation(0.0f)
        , gravity(0.0f, -9.81f, 0.0f)
        , drag(0.0f)
        , shape(EmissionShape::Point)
        , shapeRadius(1.0f)
        , shapeSize(1.0f, 1.0f, 1.0f)
        , coneAngle(25.0f)
    {}
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem() = default;
    
    // Control
    void Play();
    void Stop();
    void Pause();
    void Clear();
    
    // Update
    void Update(float deltaTime);
    
    // Settings
    void SetSettings(const ParticleEmitterSettings& settings);
    const ParticleEmitterSettings& GetSettings() const { return settings; }
    
    // Transform
    Transform& GetTransform() { return transform; }
    const Transform& GetTransform() const { return transform; }
    
    // Particles
    const std::vector<Particle>& GetParticles() const { return particles; }
    int GetActiveParticleCount() const;
    
    // State
    bool IsPlaying() const { return playing; }
    bool IsPaused() const { return paused; }
    
private:
    std::vector<Particle> particles;
    ParticleEmitterSettings settings;
    Transform transform;
    
    bool playing;
    bool paused;
    float time;
    float emissionAccumulator;
    
    void EmitParticle();
    void UpdateParticle(Particle& particle, float deltaTime);
    Vector3 GetEmissionPosition() const;
    Vector3 GetEmissionVelocity() const;
    float RandomRange(float min, float max) const;
};

} // namespace YUGA
