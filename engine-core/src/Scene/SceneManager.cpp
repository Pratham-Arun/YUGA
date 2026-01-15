#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Core/Log.h"

namespace YUGA {

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}

void SceneManager::LoadScene(const std::string& name) {
    LOG_INFO("Loading scene: {}", name);
    activeScene = std::make_unique<Scene>();
}

void SceneManager::UnloadScene() {
    activeScene.reset();
}

} // namespace YUGA
