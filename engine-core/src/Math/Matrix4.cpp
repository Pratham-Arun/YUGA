#include "Math/Matrix4.h"
#include "Math/MathUtils.h"
#include <cstring>
#include <cmath>

namespace YUGA {

Matrix4::Matrix4() {
    std::memset(m, 0, sizeof(m));
}

Matrix4::Matrix4(float diagonal) {
    std::memset(m, 0, sizeof(m));
    m[0] = m[5] = m[10] = m[15] = diagonal;
}

Matrix4::Matrix4(const float* data) {
    std::memcpy(m, data, sizeof(m));
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (int i = 0; i < 4; ++i) {
                sum += At(row, i) * other.At(i, col);
            }
            result.At(row, col) = sum;
        }
    }
    return result;
}

Vector4 Matrix4::operator*(const Vector4& vec) const {
    return Vector4(
        At(0,0) * vec.x + At(0,1) * vec.y + At(0,2) * vec.z + At(0,3) * vec.w,
        At(1,0) * vec.x + At(1,1) * vec.y + At(1,2) * vec.z + At(1,3) * vec.w,
        At(2,0) * vec.x + At(2,1) * vec.y + At(2,2) * vec.z + At(2,3) * vec.w,
        At(3,0) * vec.x + At(3,1) * vec.y + At(3,2) * vec.z + At(3,3) * vec.w
    );
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

Matrix4 Matrix4::Transposed() const {
    Matrix4 result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.At(col, row) = At(row, col);
        }
    }
    return result;
}

Matrix4 Matrix4::Identity() {
    return Matrix4(1.0f);
}

Matrix4 Matrix4::Translation(const Vector3& translation) {
    Matrix4 result = Identity();
    result.At(0, 3) = translation.x;
    result.At(1, 3) = translation.y;
    result.At(2, 3) = translation.z;
    return result;
}

Matrix4 Matrix4::RotationX(float angle) {
    Matrix4 result = Identity();
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    result.At(1, 1) = c;
    result.At(1, 2) = -s;
    result.At(2, 1) = s;
    result.At(2, 2) = c;
    return result;
}

Matrix4 Matrix4::RotationY(float angle) {
    Matrix4 result = Identity();
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    result.At(0, 0) = c;
    result.At(0, 2) = s;
    result.At(2, 0) = -s;
    result.At(2, 2) = c;
    return result;
}

Matrix4 Matrix4::RotationZ(float angle) {
    Matrix4 result = Identity();
    float c = Math::Cos(angle);
    float s = Math::Sin(angle);
    result.At(0, 0) = c;
    result.At(0, 1) = -s;
    result.At(1, 0) = s;
    result.At(1, 1) = c;
    return result;
}

Matrix4 Matrix4::Scale(const Vector3& scale) {
    Matrix4 result = Identity();
    result.At(0, 0) = scale.x;
    result.At(1, 1) = scale.y;
    result.At(2, 2) = scale.z;
    return result;
}

Matrix4 Matrix4::Scale(float scale) {
    return Scale(Vector3(scale, scale, scale));
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far) {
    Matrix4 result;
    float tanHalfFov = Math::Tan(fov / 2.0f);
    
    result.At(0, 0) = 1.0f / (aspect * tanHalfFov);
    result.At(1, 1) = 1.0f / tanHalfFov;
    result.At(2, 2) = -(far + near) / (far - near);
    result.At(2, 3) = -(2.0f * far * near) / (far - near);
    result.At(3, 2) = -1.0f;
    
    return result;
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix4 result = Identity();
    
    result.At(0, 0) = 2.0f / (right - left);
    result.At(1, 1) = 2.0f / (top - bottom);
    result.At(2, 2) = -2.0f / (far - near);
    result.At(0, 3) = -(right + left) / (right - left);
    result.At(1, 3) = -(top + bottom) / (top - bottom);
    result.At(2, 3) = -(far + near) / (far - near);
    
    return result;
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
    Vector3 f = (center - eye).Normalized();
    Vector3 s = f.Cross(up).Normalized();
    Vector3 u = s.Cross(f);
    
    Matrix4 result = Identity();
    result.At(0, 0) = s.x;
    result.At(0, 1) = s.y;
    result.At(0, 2) = s.z;
    result.At(1, 0) = u.x;
    result.At(1, 1) = u.y;
    result.At(1, 2) = u.z;
    result.At(2, 0) = -f.x;
    result.At(2, 1) = -f.y;
    result.At(2, 2) = -f.z;
    result.At(0, 3) = -s.Dot(eye);
    result.At(1, 3) = -u.Dot(eye);
    result.At(2, 3) = f.Dot(eye);
    
    return result;
}

Vector3 Matrix4::GetTranslation() const {
    return Vector3(At(0, 3), At(1, 3), At(2, 3));
}

Vector3 Matrix4::GetRight() const {
    return Vector3(At(0, 0), At(1, 0), At(2, 0));
}

Vector3 Matrix4::GetUp() const {
    return Vector3(At(0, 1), At(1, 1), At(2, 1));
}

Vector3 Matrix4::GetForward() const {
    return Vector3(-At(0, 2), -At(1, 2), -At(2, 2));
}

Matrix4 Matrix4::Inverted() const {
    // Simplified inverse for now - just return identity
    // TODO: Implement proper matrix inversion
    return Matrix4::Identity();
}

float Matrix4::Determinant() const {
    // Simplified - return 1.0
    // TODO: Implement proper determinant calculation
    return 1.0f;
}

Matrix4 Matrix4::Rotation(const Vector3& axis, float angle) {
    // Simplified rotation
    return RotationY(angle);
}

Vector3 Matrix4::GetScale() const {
    return Vector3(
        Vector3(At(0,0), At(1,0), At(2,0)).Length(),
        Vector3(At(0,1), At(1,1), At(2,1)).Length(),
        Vector3(At(0,2), At(1,2), At(2,2)).Length()
    );
}

} // namespace YUGA
