#include "Math/Quaternion.h"
#include "Math/Matrix4.h"
#include "Math/MathUtils.h"
#include <cmath>

namespace YUGA {

Quaternion::Quaternion(const Vector3& axis, float angle) {
    float halfAngle = angle * 0.5f;
    float s = Math::Sin(halfAngle);
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
    w = Math::Cos(halfAngle);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
}

Quaternion& Quaternion::operator*=(const Quaternion& other) {
    *this = *this * other;
    return *this;
}

float Quaternion::Length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

float Quaternion::LengthSquared() const {
    return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::Normalized() const {
    float len = Length();
    if (len > 0.0f) {
        return *this * (1.0f / len);
    }
    return *this;
}

void Quaternion::Normalize() {
    float len = Length();
    if (len > 0.0f) {
        float invLen = 1.0f / len;
        x *= invLen;
        y *= invLen;
        z *= invLen;
        w *= invLen;
    }
}

Quaternion Quaternion::Conjugate() const {
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::Inverse() const {
    float lenSq = LengthSquared();
    if (lenSq > 0.0f) {
        Quaternion conj = Conjugate();
        return conj * (1.0f / lenSq);
    }
    return *this;
}

float Quaternion::Dot(const Quaternion& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector3 Quaternion::RotateVector(const Vector3& vec) const {
    Quaternion vecQuat(vec.x, vec.y, vec.z, 0.0f);
    Quaternion result = (*this) * vecQuat * Conjugate();
    return Vector3(result.x, result.y, result.z);
}

Vector3 Quaternion::ToEulerAngles() const {
    Vector3 angles;
    
    // Roll (x-axis rotation)
    float sinr_cosp = 2.0f * (w * x + y * z);
    float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
    angles.x = Math::Atan2(sinr_cosp, cosr_cosp);
    
    // Pitch (y-axis rotation)
    float sinp = 2.0f * (w * y - z * x);
    if (Math::Abs(sinp) >= 1.0f)
        angles.y = std::copysign(Math::HALF_PI, sinp);
    else
        angles.y = Math::Asin(sinp);
    
    // Yaw (z-axis rotation)
    float siny_cosp = 2.0f * (w * z + x * y);
    float cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
    angles.z = Math::Atan2(siny_cosp, cosy_cosp);
    
    return angles;
}

Quaternion Quaternion::FromEulerAngles(float pitch, float yaw, float roll) {
    float cy = Math::Cos(yaw * 0.5f);
    float sy = Math::Sin(yaw * 0.5f);
    float cp = Math::Cos(pitch * 0.5f);
    float sp = Math::Sin(pitch * 0.5f);
    float cr = Math::Cos(roll * 0.5f);
    float sr = Math::Sin(roll * 0.5f);
    
    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;
    
    return q;
}

Quaternion Quaternion::FromEulerAngles(const Vector3& euler) {
    return FromEulerAngles(euler.x, euler.y, euler.z);
}

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, float angle) {
    return Quaternion(axis.Normalized(), angle);
}

Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t) {
    Quaternion result;
    float dot = a.Dot(b);
    
    // Ensure shortest path
    Quaternion b2 = b;
    if (dot < 0.0f) {
        b2 = b * -1.0f;
        dot = -dot;
    }
    
    if (dot > 0.9995f) {
        // Linear interpolation for very close quaternions
        result = Lerp(a, b2, t);
        result.Normalize();
        return result;
    }
    
    float theta = Math::Acos(dot);
    float sinTheta = Math::Sin(theta);
    float wa = Math::Sin((1.0f - t) * theta) / sinTheta;
    float wb = Math::Sin(t * theta) / sinTheta;
    
    result.x = wa * a.x + wb * b2.x;
    result.y = wa * a.y + wb * b2.y;
    result.z = wa * a.z + wb * b2.z;
    result.w = wa * a.w + wb * b2.w;
    
    return result;
}

Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t) {
    return Quaternion(
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    );
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b) {
    return a.Dot(b);
}

Matrix4 Quaternion::ToMatrix() const {
    Matrix4 result = Matrix4::Identity();
    
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    
    result.At(0, 0) = 1.0f - 2.0f * (yy + zz);
    result.At(0, 1) = 2.0f * (xy - wz);
    result.At(0, 2) = 2.0f * (xz + wy);
    
    result.At(1, 0) = 2.0f * (xy + wz);
    result.At(1, 1) = 1.0f - 2.0f * (xx + zz);
    result.At(1, 2) = 2.0f * (yz - wx);
    
    result.At(2, 0) = 2.0f * (xz - wy);
    result.At(2, 1) = 2.0f * (yz + wx);
    result.At(2, 2) = 1.0f - 2.0f * (xx + yy);
    
    return result;
}

Quaternion Quaternion::FromMatrix(const Matrix4& mat) {
    // Simplified - return identity
    // TODO: Implement proper matrix to quaternion conversion
    return Quaternion::Identity();
}

} // namespace YUGA
