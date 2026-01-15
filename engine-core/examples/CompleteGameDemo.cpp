/**
 * Complete Game Engine Demo
 * Demonstrates all YUGA Engine features
 */

#include "Core/Engine.h"
#include "Rendering/Window.h"
#include "Rendering/Renderer.h"
#include "Rendering/Camera.h"
#include "Rendering/Light.h"
#include "Rendering/ParticleSystem.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/RigidBody.h"
#include "Audio/AudioEngine.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Assets/AssetManager.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "UI/UICanvas.h"
#include "Terrain/Terrain.h"

using namespace YUGA;

class GameDemo {
public:
    void Initialize() {
        // Create window
        window = std::make_unique<Window>(1920, 1080, "YUGA Engine - Complete Demo");
        
        // Initialize subsystems
        renderer = std::make_unique<Renderer>();
        physics = std::make_unique<PhysicsWorld>();
        audio = std::make_unique<AudioEngine>();
        assetManager = std::make_unique<AssetManager>();
        scene = std::make_unique<Scene>();
        
        // Setup camera
        camera = std::make_unique<Camera>();
        camera->SetPerspective(Math::ToRadians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
        camera->GetTransform().SetPosition(Vector3(0, 5, 10));
        camera->GetTransform().LookAt(Vector3::Zero());
        
        // Create lights
        CreateLights();
        
        // Create terrain
        CreateTerrain();
        
        // Create game objects
        CreatePlayer();
        CreateEnemies();
        CreateEnvironment();
        
        // Setup UI
        CreateUI();
        
        // Setup particle effects
        CreateParticles();
        
        // Load audio
        LoadAudio();
        
        LOG_INFO("Game initialized successfully!");
    }
    
    void Run() {
        float lastTime = 0.0f;
        
        while (!window->ShouldClose()) {
            float currentTime = GetTime();
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;
            
            Update(deltaTime);
            Render();
            
            window->SwapBuffers();
            window->PollEvents();
        }
    }
    
    void Shutdown() {
        LOG_INFO("Shutting down game...");
    }
    
private:
    // Core systems
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<PhysicsWorld> physics;
    std::unique_ptr<AudioEngine> audio;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<UICanvas> ui;
    std::unique_ptr<Terrain> terrain;
    
    // Game objects
    Transform playerTransform;
    std::vector<Transform> enemyTransforms;
    std::vector<Light> lights;
    std::vector<std::unique_ptr<ParticleSystem>> particleSystems;
    
    // Game state
    float gameTime = 0.0f;
    int score = 0;
    bool paused = false;
    
    void CreateLights() {
        // Directional light (sun)
        Light sun = Light::CreateDirectional(
            Vector3(0.3f, -1.0f, 0.5f),
            Vector3(1.0f, 0.95f, 0.8f),
            1.0f
        );
        sun.castShadows = true;
        lights.push_back(sun);
        
        // Point lights
        for (int i = 0; i < 4; i++) {
            float angle = (i / 4.0f) * Math::TWO_PI;
            Vector3 pos(Math::Cos(angle) * 10.0f, 2.0f, Math::Sin(angle) * 10.0f);
            Light pointLight = Light::CreatePoint(pos, Vector3(1, 0.5f, 0.2f), 2.0f, 15.0f);
            lights.push_back(pointLight);
        }
    }
    
    void CreateTerrain() {
        terrain = std::make_unique<Terrain>(128, 128, 1.0f);
        terrain->GenerateHeightmap(12345);
        terrain->GenerateMesh();
    }
    
    void CreatePlayer() {
        playerTransform.SetPosition(Vector3(0, 1, 0));
        
        // Add physics
        // RigidBody* playerBody = physics->CreateRigidBody(playerTransform);
        // playerBody->SetMass(1.0f);
    }
    
    void CreateEnemies() {
        for (int i = 0; i < 10; i++) {
            Transform enemy;
            float angle = (i / 10.0f) * Math::TWO_PI;
            float radius = 20.0f;
            enemy.SetPosition(Vector3(
                Math::Cos(angle) * radius,
                1.0f,
                Math::Sin(angle) * radius
            ));
            enemyTransforms.push_back(enemy);
        }
    }
    
    void CreateEnvironment() {
        // Create trees, rocks, buildings, etc.
        // This would load models from AssetManager
    }
    
    void CreateUI() {
        ui = std::make_unique<UICanvas>(1920, 1080);
        
        // Score text
        auto scoreText = std::make_shared<UIText>();
        scoreText->text = "Score: 0";
        scoreText->position = Vector2(10, 10);
        scoreText->fontSize = 24.0f;
        ui->AddElement(scoreText);
        
        // Health bar
        auto healthBar = std::make_shared<UIImage>();
        healthBar->position = Vector2(10, 50);
        healthBar->size = Vector2(200, 20);
        healthBar->color = Vector4(1, 0, 0, 1);
        ui->AddElement(healthBar);
    }
    
    void CreateParticles() {
        // Fire effect
        auto fireParticles = std::make_unique<ParticleSystem>();
        ParticleEmitterSettings fireSettings;
        fireSettings.emissionRate = 50.0f;
        fireSettings.startLifetime = 2.0f;
        fireSettings.startSpeed = 3.0f;
        fireSettings.startSize = 0.5f;
        fireSettings.startColor = Vector4(1.0f, 0.5f, 0.0f, 1.0f);
        fireSettings.shape = ParticleEmitterSettings::EmissionShape::Cone;
        fireSettings.coneAngle = 15.0f;
        fireParticles->SetSettings(fireSettings);
        fireParticles->Play();
        particleSystems.push_back(std::move(fireParticles));
    }
    
    void LoadAudio() {
        // Load background music
        // audio->LoadMusic("Assets/Audio/background.ogg");
        // audio->PlayMusic();
        
        // Load sound effects
        // audio->LoadSound("jump", "Assets/Audio/jump.wav");
        // audio->LoadSound("shoot", "Assets/Audio/shoot.wav");
    }
    
    void Update(float deltaTime) {
        if (paused) return;
        
        gameTime += deltaTime;
        
        // Update input
        UpdateInput(deltaTime);
        
        // Update physics
        physics->Step(deltaTime);
        
        // Update audio
        audio->Update();
        
        // Update particles
        for (auto& particles : particleSystems) {
            particles->Update(deltaTime);
        }
        
        // Update enemies
        UpdateEnemies(deltaTime);
        
        // Update UI
        ui->Update(deltaTime);
    }
    
    void UpdateInput(float deltaTime) {
        float moveSpeed = 5.0f;
        float rotateSpeed = 2.0f;
        
        // Movement
        Vector3 movement = Vector3::Zero();
        if (Input::IsKeyPressed(GLFW_KEY_W)) movement += Vector3::Forward();
        if (Input::IsKeyPressed(GLFW_KEY_S)) movement += Vector3::Back();
        if (Input::IsKeyPressed(GLFW_KEY_A)) movement += Vector3::Left();
        if (Input::IsKeyPressed(GLFW_KEY_D)) movement += Vector3::Right();
        
        if (movement.LengthSquared() > 0.0f) {
            movement.Normalize();
            playerTransform.Translate(movement * moveSpeed * deltaTime);
        }
        
        // Rotation
        if (Input::IsKeyPressed(GLFW_KEY_Q)) {
            playerTransform.Rotate(Vector3::Up(), -rotateSpeed * deltaTime);
        }
        if (Input::IsKeyPressed(GLFW_KEY_E)) {
            playerTransform.Rotate(Vector3::Up(), rotateSpeed * deltaTime);
        }
        
        // Jump
        if (Input::IsKeyPressed(GLFW_KEY_SPACE)) {
            // Apply jump force
            // audio->PlaySound("jump");
        }
        
        // Shoot
        if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            // Spawn projectile
            // audio->PlaySound("shoot");
        }
        
        // Pause
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
            paused = !paused;
        }
    }
    
    void UpdateEnemies(float deltaTime) {
        for (auto& enemy : enemyTransforms) {
            // Simple AI: rotate towards player
            Vector3 toPlayer = playerTransform.GetPosition() - enemy.GetPosition();
            if (toPlayer.LengthSquared() > 0.0f) {
                enemy.LookAt(playerTransform.GetPosition());
                
                // Move towards player
                Vector3 direction = toPlayer.Normalized();
                enemy.Translate(direction * 2.0f * deltaTime);
            }
        }
    }
    
    void Render() {
        renderer->BeginFrame();
        renderer->Clear(0.1f, 0.1f, 0.15f, 1.0f);
        
        // Set camera
        renderer->SetCamera(camera.get());
        
        // Set lights
        for (const auto& light : lights) {
            renderer->AddLight(light);
        }
        
        // Render terrain
        if (terrain && terrain->GetMesh()) {
            renderer->DrawMesh(terrain->GetMesh().get(), Matrix4::Identity());
        }
        
        // Render player
        // renderer->DrawMesh(playerMesh, playerTransform.GetMatrix());
        
        // Render enemies
        for (const auto& enemy : enemyTransforms) {
            // renderer->DrawMesh(enemyMesh, enemy.GetMatrix());
        }
        
        // Render particles
        for (const auto& particles : particleSystems) {
            renderer->DrawParticles(particles.get());
        }
        
        // Render UI
        ui->Render();
        
        renderer->EndFrame();
    }
    
    float GetTime() {
        return static_cast<float>(glfwGetTime());
    }
};

int main() {
    try {
        GameDemo game;
        game.Initialize();
        game.Run();
        game.Shutdown();
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: {}", e.what());
        return -1;
    }
}
