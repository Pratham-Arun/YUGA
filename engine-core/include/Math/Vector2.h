#pragma once

namespace YUGA {

struct Vector2 {
    float x, y;
    
    // Constructors
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2(float scalar) : x(scalar), y(scalar) {}
    
    // Operators
    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }
    
    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
    
    bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vector2& other) const { return !(*this == other); }
    
    // Methods
    float Length() const;
    float LengthSquared() const;
    Vector2 Normalized() const;
    void Normalize();
    float Dot(const Vector2& other) const;
    float Distance(const Vector2& other) const;
    
    // Static methods
    static Vector2 Zero() { return Vector2(0.0f, 0.0f); }
    static Vector2 One() { return Vector2(1.0f, 1.0f); }
    static Vector2 Up() { return Vector2(0.0f, 1.0f); }
    static Vector2 Down() { return Vector2(0.0f, -1.0f); }
    static Vector2 Left() { return Vector2(-1.0f, 0.0f); }
    static Vector2 Right() { return Vector2(1.0f, 0.0f); }
    
    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
    static float Dot(const Vector2& a, const Vector2& b);
};

} // namespace YUGA
