#include "Scripting/ScriptEngine.h"
#include "Core/Log.h"
#include <fstream>
#include <sstream>

namespace YUGA {
    
    lua_State* ScriptEngine::s_LuaState = nullptr;
    
    void ScriptEngine::Initialize() {
        s_LuaState = luaL_newstate();
        luaL_openlibs(s_LuaState);
        
        RegisterEngineFunctions();
        
        Log::Info("Script engine initialized");
    }
    
    void ScriptEngine::Shutdown() {
        if (s_LuaState) {
            lua_close(s_LuaState);
            s_LuaState = nullptr;
        }
        Log::Info("Script engine shutdown");
    }
    
    bool ScriptEngine::LoadScript(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            Log::Error("Failed to load script: " + filepath);
            return false;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string code = buffer.str();
        
        return ExecuteScript(code);
    }
    
    bool ScriptEngine::ExecuteScript(const std::string& code) {
        if (luaL_dostring(s_LuaState, code.c_str()) != LUA_OK) {
            const char* error = lua_tostring(s_LuaState, -1);
            Log::Error("Lua error: " + std::string(error));
            lua_pop(s_LuaState, 1);
            return false;
        }
        return true;
    }
    
    void ScriptEngine::CallFunction(const std::string& functionName) {
        lua_getglobal(s_LuaState, functionName.c_str());
        if (lua_isfunction(s_LuaState, -1)) {
            if (lua_pcall(s_LuaState, 0, 0, 0) != LUA_OK) {
                const char* error = lua_tostring(s_LuaState, -1);
                Log::Error("Lua function call error: " + std::string(error));
                lua_pop(s_LuaState, 1);
            }
        } else {
            lua_pop(s_LuaState, 1);
        }
    }
    
    void ScriptEngine::SetGlobal(const std::string& name, float value) {
        lua_pushnumber(s_LuaState, value);
        lua_setglobal(s_LuaState, name.c_str());
    }
    
    void ScriptEngine::SetGlobal(const std::string& name, const std::string& value) {
        lua_pushstring(s_LuaState, value.c_str());
        lua_setglobal(s_LuaState, name.c_str());
    }
    
    float ScriptEngine::GetGlobalFloat(const std::string& name) {
        lua_getglobal(s_LuaState, name.c_str());
        float value = (float)lua_tonumber(s_LuaState, -1);
        lua_pop(s_LuaState, 1);
        return value;
    }
    
    std::string ScriptEngine::GetGlobalString(const std::string& name) {
        lua_getglobal(s_LuaState, name.c_str());
        const char* value = lua_tostring(s_LuaState, -1);
        lua_pop(s_LuaState, 1);
        return value ? value : "";
    }
    
    void ScriptEngine::ReloadScript(const std::string& filepath) {
        LoadScript(filepath);
        Log::Info("Script reloaded: " + filepath);
    }
    
    void ScriptEngine::RegisterEngineFunctions() {
        // Register C++ functions to Lua
        // Example: Log function
        lua_register(s_LuaState, "Log", [](lua_State* L) -> int {
            const char* message = lua_tostring(L, 1);
            Log::Info(message);
            return 0;
        });
    }
    
} // namespace YUGA
