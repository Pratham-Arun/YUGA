#pragma once

#include "Core/Core.h"
#include <lua.hpp>
#include <string>
#include <memory>

namespace YUGA {
    
    class YUGA_API ScriptEngine {
    public:
        static void Initialize();
        static void Shutdown();
        
        // Script execution
        static bool LoadScript(const std::string& filepath);
        static bool ExecuteScript(const std::string& code);
        static void CallFunction(const std::string& functionName);
        
        // Variable access
        static void SetGlobal(const std::string& name, float value);
        static void SetGlobal(const std::string& name, const std::string& value);
        static float GetGlobalFloat(const std::string& name);
        static std::string GetGlobalString(const std::string& name);
        
        // Hot reload
        static void ReloadScript(const std::string& filepath);
        
        static lua_State* GetState() { return s_LuaState; }
        
    private:
        static void RegisterEngineFunctions();
        
        static lua_State* s_LuaState;
    };
    
} // namespace YUGA
