#pragma once

#include <cmath>
#include <iostream>

namespace YUGA {

struct Vector3 {
    float x, y, z;
    
    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    // Operators
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
    
    // Component-wise multiplication and division
    Vector3 operator*(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }
    
    Vector3 operator/(const Vector3& other) const {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }
    
    Vector3& operator+=(const Vector3& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }
    
    // Static Lerp function
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
        return a + (b - a) * t;
    }
    
    // Dot product
    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // Cross product
    Vector3 Cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    // Length
    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    float LengthSquared() const {
        return x * x + y * y + z * z;
    }
    
    // Normalize
    Vector3 Normalized() const {
        float len = Length();
        return len > 0 ? (*this / len) : Vector3(0);
    }
    
    void Normalize() {
        float len = Length();
        if (len > 0) {
            x /= len; y /= len; z /= len;
        }
    }
    
    // Static vectors
    static Vector3 Zero()    { return Vector3(0, 0, 0); }
    static Vector3 One()     { return Vector3(1, 1, 1); }
    static Vector3 Up()      { return Vector3(0, 1, 0); }
    static Vector3 Down()    { return Vector3(0, -1, 0); }
    static Vector3 Left()    { return Vector3(-1, 0, 0); }
    static Vector3 Right()   { return Vector3(1, 0, 0); }
    static Vector3 Forward() { return Vector3(0, 0, 1); }
    static Vector3 Back()    { return Vector3(0, 0, -1); }
};

} // namespace YUGA
