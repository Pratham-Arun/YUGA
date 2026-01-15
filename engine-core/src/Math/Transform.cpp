#include "Math/Transform.h"

namespace YUGA {

Transform::Transform()
    : position(Vector3::Zero())
    , rotation(Quaternion::Identity())
    , scale(Vector3::One())
    , matrix(Matrix4::Identity())
    , dirty(true)
    , parent(nullptr)
{
}

Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    : position(position)
    , rotation(rotation)
    , scale(scale)
    , matrix(Matrix4::Identity())
    , dirty(true)
    , parent(nullptr)
{
}

void Transform::SetEulerAngles(const Vector3& euler) {
    rotation = Quaternion::FromEulerAngles(euler);
    dirty = true;
}

void Transform::SetEulerAngles(float pitch, float yaw, float roll) {
    rotation = Quaternion::FromEulerAngles(pitch, yaw, roll);
    dirty = true;
}

Vector3 Transform::GetForward() const {
    return rotation.RotateVector(Vector3::Forward());
}

Vector3 Transform::GetRight() const {
    return rotation.RotateVector(Vector3::Right());
}

Vector3 Transform::GetUp() const {
    return rotation.RotateVector(Vector3::Up());
}

void Transform::Translate(const Vector3& translation) {
    position += translation;
    dirty = true;
}

void Transform::Rotate(const Quaternion& rot) {
    rotation = rot * rotation;
    rotation.Normalize();
    dirty = true;
}

void Transform::Rotate(const Vector3& axis, float angle) {
    Quaternion rot = Quaternion::FromAxisAngle(axis, angle);
    Rotate(rot);
}

void Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle) {
    Vector3 direction = position - point;
    Quaternion rot = Quaternion::FromAxisAngle(axis, angle);
    direction = rot.RotateVector(direction);
    position = point + direction;
    Rotate(rot);
}

void Transform::LookAt(const Vector3& target, const Vector3& up) {
    Vector3 forward = (target - position).Normalized();
    Vector3 right = up.Cross(forward).Normalized();
    Vector3 newUp = forward.Cross(right);
    
    Matrix4 lookMatrix = Matrix4::Identity();
    lookMatrix.At(0, 0) = right.x;
    lookMatrix.At(0, 1) = right.y;
    lookMatrix.At(0, 2) = right.z;
    lookMatrix.At(1, 0) = newUp.x;
    lookMatrix.At(1, 1) = newUp.y;
    lookMatrix.At(1, 2) = newUp.z;
    lookMatrix.At(2, 0) = forward.x;
    lookMatrix.At(2, 1) = forward.y;
    lookMatrix.At(2, 2) = forward.z;
    
    rotation = Quaternion::FromMatrix(lookMatrix);
    dirty = true;
}

const Matrix4& Transform::GetMatrix() const {
    if (dirty) {
        UpdateMatrix();
    }
    return matrix;
}

Matrix4 Transform::GetInverseMatrix() const {
    return GetMatrix().Inverted();
}

void Transform::UpdateMatrix() const {
    matrix = Matrix4::Translation(position) * 
             rotation.ToMatrix() * 
             Matrix4::Scale(scale);
    dirty = false;
}

Vector3 Transform::TransformPoint(const Vector3& point) const {
    Vector4 p(point.x, point.y, point.z, 1.0f);
    Vector4 result = GetMatrix() * p;
    return Vector3(result.x, result.y, result.z);
}

Vector3 Transform::TransformDirection(const Vector3& direction) const {
    return rotation.RotateVector(direction * scale);
}

Vector3 Transform::InverseTransformPoint(const Vector3& point) const {
    Vector4 p(point.x, point.y, point.z, 1.0f);
    Vector4 result = GetInverseMatrix() * p;
    return Vector3(result.x, result.y, result.z);
}

Vector3 Transform::InverseTransformDirection(const Vector3& direction) const {
    return rotation.Inverse().RotateVector(direction) / scale;
}

void Transform::SetParent(Transform* newParent) {
    parent = newParent;
    dirty = true;
}

Matrix4 Transform::GetWorldMatrix() const {
    if (parent) {
        return parent->GetWorldMatrix() * GetMatrix();
    }
    return GetMatrix();
}

} // namespace YUGA
