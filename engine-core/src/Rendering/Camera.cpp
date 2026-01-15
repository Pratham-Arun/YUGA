#include "Rendering/Camera.h"
#include "Math/MathUtils.h"

namespace YUGA {

Camera::Camera()
    : projectionType(ProjectionType::Perspective)
    , fieldOfView(Math::ToRadians(60.0f))
    , aspectRatio(16.0f / 9.0f)
    , nearPlane(0.1f)
    , farPlane(1000.0f)
    , orthographicSize(10.0f)
    , viewDirty(true)
{
    UpdateProjectionMatrix();
}

void Camera::SetPerspective(float fov, float aspect, float near, float far) {
    projectionType = ProjectionType::Perspective;
    fieldOfView = fov;
    aspectRatio = aspect;
    nearPlane = near;
    farPlane = far;
    UpdateProjectionMatrix();
}

void Camera::SetOrthographic(float size, float aspect, float near, float far) {
    projectionType = ProjectionType::Orthographic;
    orthographicSize = size;
    aspectRatio = aspect;
    nearPlane = near;
    farPlane = far;
    UpdateProjectionMatrix();
}

void Camera::SetFieldOfView(float fov) {
    fieldOfView = fov;
    if (projectionType == ProjectionType::Perspective) {
        UpdateProjectionMatrix();
    }
}

void Camera::SetAspectRatio(float aspect) {
    aspectRatio = aspect;
    UpdateProjectionMatrix();
}

void Camera::SetNearPlane(float near) {
    nearPlane = near;
    UpdateProjectionMatrix();
}

void Camera::SetFarPlane(float far) {
    farPlane = far;
    UpdateProjectionMatrix();
}

void Camera::SetOrthographicSize(float size) {
    orthographicSize = size;
    if (projectionType == ProjectionType::Orthographic) {
        UpdateProjectionMatrix();
    }
}

const Matrix4& Camera::GetViewMatrix() const {
    if (viewDirty) {
        UpdateViewMatrix();
    }
    return viewMatrix;
}

Matrix4 Camera::GetViewProjectionMatrix() const {
    return projectionMatrix * GetViewMatrix();
}

void Camera::UpdateProjectionMatrix() {
    if (projectionType == ProjectionType::Perspective) {
        projectionMatrix = Matrix4::Perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    } else {
        float height = orthographicSize;
        float width = height * aspectRatio;
        projectionMatrix = Matrix4::Orthographic(-width, width, -height, height, nearPlane, farPlane);
    }
}

void Camera::UpdateViewMatrix() const {
    Vector3 position = transform.GetPosition();
    Vector3 target = position + transform.GetForward();
    Vector3 up = transform.GetUp();
    viewMatrix = Matrix4::LookAt(position, target, up);
    viewDirty = false;
}

Vector3 Camera::ScreenToWorldPoint(const Vector3& screenPoint) const {
    // TODO: Implement screen to world conversion
    return Vector3::Zero();
}

Vector3 Camera::WorldToScreenPoint(const Vector3& worldPoint) const {
    // TODO: Implement world to screen conversion
    return Vector3::Zero();
}

} // namespace YUGA
