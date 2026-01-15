#pragma once
#include <memory>
#include <string>

namespace YUGA {

class Scene;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();
    
    void LoadScene(const std::string& name);
    void UnloadScene();
    
    Scene* GetActiveScene() const { return activeScene.get(); }
    
private:
    std::unique_ptr<Scene> activeScene;
};

} // namespace YUGA
