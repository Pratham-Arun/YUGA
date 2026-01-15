#pragma once
#include <cmath>
#include <algorithm>

namespace YUGA {
namespace Math {

// Constants
constexpr float PI = 3.14159265358979323846f;
constexpr float TWO_PI = 2.0f * PI;
constexpr float HALF_PI = 0.5f * PI;
constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;
constexpr float EPSILON = 1e-6f;

// Basic functions
template<typename T>
inline T Clamp(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

template<typename T>
inline T Lerp(T a, T b, float t) {
    return a + (b - a) * t;
}

template<typename T>
inline T Min(T a, T b) {
    return std::min(a, b);
}

template<typename T>
inline T Max(T a, T b) {
    return std::max(a, b);
}

template<typename T>
inline T Abs(T value) {
    return std::abs(value);
}

inline float Sin(float angle) { return std::sin(angle); }
inline float Cos(float angle) { return std::cos(angle); }
inline float Tan(float angle) { return std::tan(angle); }
inline float Asin(float value) { return std::asin(value); }
inline float Acos(float value) { return std::acos(value); }
inline float Atan(float value) { return std::atan(value); }
inline float Atan2(float y, float x) { return std::atan2(y, x); }

inline float Sqrt(float value) { return std::sqrt(value); }
inline float Pow(float base, float exp) { return std::pow(base, exp); }

inline float ToRadians(float degrees) { return degrees * DEG_TO_RAD; }
inline float ToDegrees(float radians) { return radians * RAD_TO_DEG; }

inline bool Approximately(float a, float b, float epsilon = EPSILON) {
    return Abs(a - b) < epsilon;
}

// Smoothing functions
inline float SmoothStep(float edge0, float edge1, float x) {
    float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

inline float SmootherStep(float edge0, float edge1, float x) {
    float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

// Easing functions
inline float EaseInQuad(float t) { return t * t; }
inline float EaseOutQuad(float t) { return t * (2.0f - t); }
inline float EaseInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

inline float EaseInCubic(float t) { return t * t * t; }
inline float EaseOutCubic(float t) { return (--t) * t * t + 1.0f; }
inline float EaseInOutCubic(float t) {
    return t < 0.5f ? 4.0f * t * t * t : (t - 1.0f) * (2.0f * t - 2.0f) * (2.0f * t - 2.0f) + 1.0f;
}

// Random (simple)
inline float Random01() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

inline float RandomRange(float min, float max) {
    return min + Random01() * (max - min);
}

inline int RandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

} // namespace Math
} // namespace YUGA
