#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

namespace YUGA {

class ComponentBase {
public:
    virtual ~ComponentBase() = default;
};

class ComponentRegistry {
public:
    static ComponentRegistry& Get() {
        static ComponentRegistry instance;
        return instance;
    }
    
    template<typename T>
    void RegisterComponent(const std::string& name) {
        componentNames[std::type_index(typeid(T))] = name;
        componentTypes[name] = std::type_index(typeid(T));
    }
    
    template<typename T>
    std::string GetComponentName() const {
        auto it = componentNames.find(std::type_index(typeid(T)));
        if (it != componentNames.end()) {
            return it->second;
        }
        return "Unknown";
    }
    
    std::type_index GetComponentType(const std::string& name) const {
        auto it = componentTypes.find(name);
        if (it != componentTypes.end()) {
            return it->second;
        }
        return std::type_index(typeid(void));
    }
    
    std::vector<std::string> GetAllComponentNames() const {
        std::vector<std::string> names;
        for (const auto& pair : componentNames) {
            names.push_back(pair.second);
        }
        return names;
    }
    
private:
    ComponentRegistry() = default;
    std::unordered_map<std::type_index, std::string> componentNames;
    std::unordered_map<std::string, std::type_index> componentTypes;
};

// Helper macro for component registration
#define REGISTER_COMPONENT(Type) \
    ComponentRegistry::Get().RegisterComponent<Type>(#Type)

} // namespace YUGA
