#include "Math/Vector2.h"
#include <cmath>

namespace YUGA {

float Vector2::Length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::LengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::Normalized() const {
    float len = Length();
    if (len > 0.0f) {
        return *this / len;
    }
    return *this;
}

void Vector2::Normalize() {
    float len = Length();
    if (len > 0.0f) {
        x /= len;
        y /= len;
    }
}

float Vector2::Dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

float Vector2::Distance(const Vector2& other) const {
    return (*this - other).Length();
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t) {
    return a + (b - a) * t;
}

float Vector2::Dot(const Vector2& a, const Vector2& b) {
    return a.Dot(b);
}

} // namespace YUGA
