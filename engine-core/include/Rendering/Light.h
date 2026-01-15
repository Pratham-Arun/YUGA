#pragma once
#include "Math/Vector3.h"
#include "Math/Transform.h"

namespace YUGA {

enum class LightType {
    Directional,
    Point,
    Spot
};

struct Light {
    LightType type;
    Vector3 color;
    float intensity;
    
    // Point/Spot light properties
    float range;
    float attenuation;
    
    // Spot light properties
    float spotAngle;
    float spotSoftness;
    
    // Shadow properties
    bool castShadows;
    int shadowResolution;
    
    Transform transform;
    
    Light()
        : type(LightType::Directional)
        , color(Vector3::One())
        , intensity(1.0f)
        , range(10.0f)
        , attenuation(1.0f)
        , spotAngle(45.0f)
        , spotSoftness(0.1f)
        , castShadows(false)
        , shadowResolution(1024)
    {}
    
    static Light CreateDirectional(const Vector3& direction, const Vector3& color = Vector3::One(), float intensity = 1.0f) {
        Light light;
        light.type = LightType::Directional;
        light.color = color;
        light.intensity = intensity;
        light.transform.SetRotation(Quaternion::FromEulerAngles(direction));
        return light;
    }
    
    static Light CreatePoint(const Vector3& position, const Vector3& color = Vector3::One(), float intensity = 1.0f, float range = 10.0f) {
        Light light;
        light.type = LightType::Point;
        light.color = color;
        light.intensity = intensity;
        light.range = range;
        light.transform.SetPosition(position);
        return light;
    }
    
    static Light CreateSpot(const Vector3& position, const Vector3& direction, const Vector3& color = Vector3::One(), 
                           float intensity = 1.0f, float range = 10.0f, float spotAngle = 45.0f) {
        Light light;
        light.type = LightType::Spot;
        light.color = color;
        light.intensity = intensity;
        light.range = range;
        light.spotAngle = spotAngle;
        light.transform.SetPosition(position);
        light.transform.SetRotation(Quaternion::FromEulerAngles(direction));
        return light;
    }
};

} // namespace YUGA
