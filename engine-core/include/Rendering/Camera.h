#pragma once
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Math/Transform.h"

namespace YUGA {

enum class ProjectionType {
    Perspective,
    Orthographic
};

class Camera {
public:
    Camera();
    ~Camera() = default;
    
    // Projection settings
    void SetPerspective(float fov, float aspect, float near, float far);
    void SetOrthographic(float size, float aspect, float near, float far);
    
    // Getters
    const Matrix4& GetProjectionMatrix() const { return projectionMatrix; }
    const Matrix4& GetViewMatrix() const;
    Matrix4 GetViewProjectionMatrix() const;
    
    ProjectionType GetProjectionType() const { return projectionType; }
    float GetFieldOfView() const { return fieldOfView; }
    float GetAspectRatio() const { return aspectRatio; }
    float GetNearPlane() const { return nearPlane; }
    float GetFarPlane() const { return farPlane; }
    float GetOrthographicSize() const { return orthographicSize; }
    
    // Setters
    void SetFieldOfView(float fov);
    void SetAspectRatio(float aspect);
    void SetNearPlane(float near);
    void SetFarPlane(float far);
    void SetOrthographicSize(float size);
    
    // Transform
    Transform& GetTransform() { return transform; }
    const Transform& GetTransform() const { return transform; }
    
    // Screen to world
    Vector3 ScreenToWorldPoint(const Vector3& screenPoint) const;
    Vector3 WorldToScreenPoint(const Vector3& worldPoint) const;
    
private:
    Transform transform;
    Matrix4 projectionMatrix;
    mutable Matrix4 viewMatrix;
    mutable bool viewDirty;
    
    ProjectionType projectionType;
    float fieldOfView;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    float orthographicSize;
    
    void UpdateProjectionMatrix();
    void UpdateViewMatrix() const;
};

} // namespace YUGA
