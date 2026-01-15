#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace YUGA {

class Log {
public:
    enum class Level {
        Info,
        Warn,
        Error,
        Critical
    };
    
    template<typename... Args>
    static void Info(Args&&... args) {
        LogMessage(Level::Info, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    static void Warn(Args&&... args) {
        LogMessage(Level::Warn, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    static void Error(Args&&... args) {
        LogMessage(Level::Error, std::forward<Args>(args)...);
    }
    
    template<typename... Args>
    static void Critical(Args&&... args) {
        LogMessage(Level::Critical, std::forward<Args>(args)...);
    }
    
private:
    template<typename... Args>
    static void LogMessage(Level level, Args&&... args) {
        std::cout << GetTimestamp() << " " << GetLevelString(level) << " ";
        (std::cout << ... << args);
        std::cout << std::endl;
    }
    
    static std::string GetTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%H:%M:%S");
        return ss.str();
    }
    
    static const char* GetLevelString(Level level) {
        switch (level) {
            case Level::Info:     return "[INFO]";
            case Level::Warn:     return "[WARN]";
            case Level::Error:    return "[ERROR]";
            case Level::Critical: return "[CRITICAL]";
        }
        return "[UNKNOWN]";
    }
};

} // namespace YUGA

// Convenience macros
#define LOG_INFO(...) YUGA::Log::Info(__VA_ARGS__)
#define LOG_WARN(...) YUGA::Log::Warn(__VA_ARGS__)
#define LOG_ERROR(...) YUGA::Log::Error(__VA_ARGS__)
#define LOG_CRITICAL(...) YUGA::Log::Critical(__VA_ARGS__)
