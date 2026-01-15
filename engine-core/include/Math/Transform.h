#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

namespace YUGA {

class Transform {
public:
    Transform();
    Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
    
    // Getters
    const Vector3& GetPosition() const { return position; }
    const Quaternion& GetRotation() const { return rotation; }
    const Vector3& GetScale() const { return scale; }
    
    Vector3 GetEulerAngles() const { return rotation.ToEulerAngles(); }
    Vector3 GetForward() const;
    Vector3 GetRight() const;
    Vector3 GetUp() const;
    
    // Setters
    void SetPosition(const Vector3& pos) { position = pos; dirty = true; }
    void SetRotation(const Quaternion& rot) { rotation = rot; dirty = true; }
    void SetScale(const Vector3& scl) { scale = scl; dirty = true; }
    void SetEulerAngles(const Vector3& euler);
    void SetEulerAngles(float pitch, float yaw, float roll);
    
    // Transform operations
    void Translate(const Vector3& translation);
    void Rotate(const Quaternion& rotation);
    void Rotate(const Vector3& axis, float angle);
    void RotateAround(const Vector3& point, const Vector3& axis, float angle);
    void LookAt(const Vector3& target, const Vector3& up = Vector3::Up());
    
    // Matrix
    const Matrix4& GetMatrix() const;
    Matrix4 GetInverseMatrix() const;
    
    // Transform points/vectors
    Vector3 TransformPoint(const Vector3& point) const;
    Vector3 TransformDirection(const Vector3& direction) const;
    Vector3 InverseTransformPoint(const Vector3& point) const;
    Vector3 InverseTransformDirection(const Vector3& direction) const;
    
    // Hierarchy (optional - for scene graph)
    void SetParent(Transform* parent);
    Transform* GetParent() const { return parent; }
    Matrix4 GetWorldMatrix() const;
    
private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    
    mutable Matrix4 matrix;
    mutable bool dirty;
    
    Transform* parent;
    
    void UpdateMatrix() const;
};

} // namespace YUGA
