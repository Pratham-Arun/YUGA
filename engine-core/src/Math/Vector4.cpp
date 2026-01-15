#include "Math/Vector4.h"
#include <cmath>

namespace YUGA {

float Vector4::Length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSquared() const {
    return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalized() const {
    float len = Length();
    if (len > 0.0f) {
        return *this / len;
    }
    return *this;
}

void Vector4::Normalize() {
    float len = Length();
    if (len > 0.0f) {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
}

float Vector4::Dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t) {
    return a + (b - a) * t;
}

float Vector4::Dot(const Vector4& a, const Vector4& b) {
    return a.Dot(b);
}

} // namespace YUGA
