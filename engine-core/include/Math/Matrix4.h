#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace YUGA {

struct Matrix4 {
    float m[16]; // Column-major order (OpenGL style)
    
    // Constructors
    Matrix4();
    Matrix4(float diagonal);
    Matrix4(const float* data);
    
    // Access
    float& operator[](int index) { return m[index]; }
    const float& operator[](int index) const { return m[index]; }
    
    float& At(int row, int col) { return m[col * 4 + row]; }
    const float& At(int row, int col) const { return m[col * 4 + row]; }
    
    // Operators
    Matrix4 operator*(const Matrix4& other) const;
    Vector4 operator*(const Vector4& vec) const;
    Matrix4& operator*=(const Matrix4& other);
    
    // Methods
    Matrix4 Transposed() const;
    Matrix4 Inverted() const;
    float Determinant() const;
    
    // Static factory methods
    static Matrix4 Identity();
    static Matrix4 Translation(const Vector3& translation);
    static Matrix4 Rotation(const Vector3& axis, float angle);
    static Matrix4 RotationX(float angle);
    static Matrix4 RotationY(float angle);
    static Matrix4 RotationZ(float angle);
    static Matrix4 Scale(const Vector3& scale);
    static Matrix4 Scale(float scale);
    
    // Camera matrices
    static Matrix4 Perspective(float fov, float aspect, float near, float far);
    static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
    static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
    
    // Transform extraction
    Vector3 GetTranslation() const;
    Vector3 GetScale() const;
    Vector3 GetRight() const;
    Vector3 GetUp() const;
    Vector3 GetForward() const;
};

} // namespace YUGA
