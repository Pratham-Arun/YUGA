#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YUGA {

struct Quaternion {
    float x, y, z, w;
    
    // Constructors
    Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Quaternion(const Vector3& axis, float angle);
    
    // Operators
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator*(float scalar) const;
    Quaternion& operator*=(const Quaternion& other);
    
    // Methods
    float Length() const;
    float LengthSquared() const;
    Quaternion Normalized() const;
    void Normalize();
    Quaternion Conjugate() const;
    Quaternion Inverse() const;
    float Dot(const Quaternion& other) const;
    
    // Rotation
    Vector3 RotateVector(const Vector3& vec) const;
    Matrix4 ToMatrix() const;
    Vector3 ToEulerAngles() const; // Returns (pitch, yaw, roll) in radians
    
    // Static methods
    static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }
    static Quaternion FromEulerAngles(float pitch, float yaw, float roll);
    static Quaternion FromEulerAngles(const Vector3& euler);
    static Quaternion FromAxisAngle(const Vector3& axis, float angle);
    static Quaternion FromMatrix(const Matrix4& mat);
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
    static float Dot(const Quaternion& a, const Quaternion& b);
};

} // namespace YUGA
