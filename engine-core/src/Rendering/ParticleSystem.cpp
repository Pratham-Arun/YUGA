#include "Rendering/ParticleSystem.h"
#include "Math/MathUtils.h"
#include <cstdlib>

namespace YUGA {

ParticleSystem::ParticleSystem()
    : playing(false)
    , paused(false)
    , time(0.0f)
    , emissionAccumulator(0.0f)
{
    particles.resize(100); // Default max particles
}

void ParticleSystem::Play() {
    playing = true;
    paused = false;
    time = 0.0f;
}

void ParticleSystem::Stop() {
    playing = false;
    paused = false;
    time = 0.0f;
    
    // Deactivate all particles
    for (auto& particle : particles) {
        particle.active = false;
    }
}

void ParticleSystem::Pause() {
    paused = true;
}

void ParticleSystem::Clear() {
    for (auto& particle : particles) {
        particle.active = false;
    }
}

void ParticleSystem::Update(float deltaTime) {
    if (!playing || paused) return;
    
    time += deltaTime;
    
    // Check if duration has expired
    if (settings.duration > 0.0f && time >= settings.duration) {
        if (settings.looping) {
            time = 0.0f;
        } else {
            playing = false;
            return;
        }
    }
    
    // Emit new particles
    if (playing) {
        emissionAccumulator += deltaTime * settings.emissionRate;
        int particlesToEmit = static_cast<int>(emissionAccumulator);
        emissionAccumulator -= particlesToEmit;
        
        for (int i = 0; i < particlesToEmit; ++i) {
            EmitParticle();
        }
    }
    
    // Update existing particles
    for (auto& particle : particles) {
        if (particle.active) {
            UpdateParticle(particle, deltaTime);
        }
    }
}

void ParticleSystem::SetSettings(const ParticleEmitterSettings& newSettings) {
    settings = newSettings;
    
    // Resize particle array if needed
    if (static_cast<int>(particles.size()) != settings.maxParticles) {
        particles.resize(settings.maxParticles);
        for (auto& particle : particles) {
            particle.active = false;
        }
    }
}

int ParticleSystem::GetActiveParticleCount() const {
    int count = 0;
    for (const auto& particle : particles) {
        if (particle.active) count++;
    }
    return count;
}

void ParticleSystem::EmitParticle() {
    // Find inactive particle
    for (auto& particle : particles) {
        if (!particle.active) {
            particle.active = true;
            particle.age = 0.0f;
            
            // Set lifetime with variation
            float lifetimeVar = RandomRange(-settings.lifetimeVariation, settings.lifetimeVariation);
            particle.lifetime = settings.startLifetime + lifetimeVar;
            
            // Set position
            particle.position = transform.GetPosition() + GetEmissionPosition();
            
            // Set velocity
            particle.velocity = GetEmissionVelocity();
            
            // Set size with variation
            float sizeVar = RandomRange(-settings.sizeVariation, settings.sizeVariation);
            particle.size = settings.startSize + sizeVar;
            
            // Set color
            particle.color = settings.startColor;
            
            break;
        }
    }
}

void ParticleSystem::UpdateParticle(Particle& particle, float deltaTime) {
    particle.age += deltaTime;
    
    // Check if particle should die
    if (particle.age >= particle.lifetime) {
        particle.active = false;
        return;
    }
    
    // Apply physics
    particle.velocity += settings.gravity * deltaTime;
    particle.velocity *= (1.0f - settings.drag * deltaTime);
    
    // Update position
    particle.position += particle.velocity * deltaTime;
    
    // Update color/size over lifetime (simple fade)
    float t = particle.age / particle.lifetime;
    particle.color.w = 1.0f - t; // Fade out alpha
}

Vector3 ParticleSystem::GetEmissionPosition() const {
    switch (settings.shape) {
        case ParticleEmitterSettings::EmissionShape::Point:
            return Vector3::Zero();
            
        case ParticleEmitterSettings::EmissionShape::Sphere: {
            float theta = RandomRange(0.0f, Math::TWO_PI);
            float phi = RandomRange(0.0f, Math::PI);
            float r = RandomRange(0.0f, settings.shapeRadius);
            
            return Vector3(
                r * Math::Sin(phi) * Math::Cos(theta),
                r * Math::Sin(phi) * Math::Sin(theta),
                r * Math::Cos(phi)
            );
        }
        
        case ParticleEmitterSettings::EmissionShape::Box:
            return Vector3(
                RandomRange(-settings.shapeSize.x * 0.5f, settings.shapeSize.x * 0.5f),
                RandomRange(-settings.shapeSize.y * 0.5f, settings.shapeSize.y * 0.5f),
                RandomRange(-settings.shapeSize.z * 0.5f, settings.shapeSize.z * 0.5f)
            );
            
        case ParticleEmitterSettings::EmissionShape::Cone: {
            float angle = RandomRange(0.0f, settings.coneAngle * Math::DEG_TO_RAD);
            float rotation = RandomRange(0.0f, Math::TWO_PI);
            
            return Vector3(
                Math::Sin(angle) * Math::Cos(rotation),
                Math::Cos(angle),
                Math::Sin(angle) * Math::Sin(rotation)
            ) * RandomRange(0.0f, settings.shapeRadius);
        }
    }
    
    return Vector3::Zero();
}

Vector3 ParticleSystem::GetEmissionVelocity() const {
    Vector3 direction = GetEmissionPosition().Normalized();
    if (direction.LengthSquared() < 0.001f) {
        direction = Vector3::Up();
    }
    
    float speedVar = RandomRange(-settings.speedVariation, settings.speedVariation);
    float speed = settings.startSpeed + speedVar;
    
    return direction * speed;
}

float ParticleSystem::RandomRange(float min, float max) const {
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + t * (max - min);
}

} // namespace YUGA
