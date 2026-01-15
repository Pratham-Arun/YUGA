#pragma once

// Platform detection
#ifdef YUGA_PLATFORM_WINDOWS
    #define YUGA_WINDOWS
#elif defined(YUGA_PLATFORM_LINUX)
    #define YUGA_LINUX
#elif defined(YUGA_PLATFORM_MACOS)
    #define YUGA_MACOS
#endif

// Debug/Release
#ifdef YUGA_DEBUG
    #define YUGA_ENABLE_ASSERTS
#endif

// Assertions
#ifdef YUGA_ENABLE_ASSERTS
    #include <cassert>
    #define YUGA_ASSERT(x, msg) assert((x) && msg)
#else
    #define YUGA_ASSERT(x, msg)
#endif

// Logging macros
#define YUGA_LOG_INFO(...)    ::YUGA::Log::Info(__VA_ARGS__)
#define YUGA_LOG_WARN(...)    ::YUGA::Log::Warn(__VA_ARGS__)
#define YUGA_LOG_ERROR(...)   ::YUGA::Log::Error(__VA_ARGS__)
#define YUGA_LOG_CRITICAL(...) ::YUGA::Log::Critical(__VA_ARGS__)

// Smart pointers
#include <memory>
namespace YUGA {
    template<typename T>
    using Scope = std::unique_ptr<T>;
    
    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

// Bit manipulation
#define BIT(x) (1 << x)
