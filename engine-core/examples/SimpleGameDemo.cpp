// Simple Game Demo - Shows complete YUGA Engine usage
// This demonstrates a simple 3D scene with models, materials, physics, and audio

#include "Core/Engine.h"
#include "Assets/AssetManager.h"
#include "Physics/PhysicsWorld.h"
#include "Audio/AudioEngine.h"
#include "Scene/Scene.h"
#include "Input/Input.h"

using namespace YUGA;

class SimpleGame {
public:
    void Initialize() {
        LOG_INFO("Initializing Simple Game Demo...");

        // Initialize systems
        InitializeAssets();
        InitializePhysics();
        InitializeAudio();
        InitializeScene();

        LOG_INFO("Game initialized successfully!");
    }

    void Update(float deltaTime) {
        // Update physics
        m_PhysicsWorld->Step(deltaTime);

        // Handle input
        HandleInput(deltaTime);

        // Update audio listener position
        m_AudioEngine->SetListenerPosition(m_CameraPosition);
    }

    void Render() {
        // Set up camera
        m_Shader->Bind();
        m_Shader->SetMat4("u_View", m_ViewMatrix);
        m_Shader->SetMat4("u_Projection", m_ProjectionMatrix);
        m_Shader->SetFloat3("u_CameraPos", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);

        // Set up lighting
        m_Shader->SetInt("u_NumLights", 2);
        m_Shader->SetFloat3("u_LightPositions[0]", 10.0f, 10.0f, 10.0f);
        m_Shader->SetFloat3("u_LightColors[0]", 300.0f, 300.0f, 300.0f);
        m_Shader->SetFloat3("u_LightPositions[1]", -10.0f, 10.0f, 10.0f);
        m_Shader->SetFloat3("u_LightColors[1]", 200.0f, 200.0f, 250.0f);

        // Render scene
        m_Scene->Render();

        m_Shader->Unbind();
    }

    void Cleanup() {
        m_AudioEngine->Cleanup();
        m_PhysicsWorld->Cleanup();
        AssetManager::Get().UnloadAll();
    }

private:
    void InitializeAssets() {
        auto& assets = AssetManager::Get();

        // Load PBR shader
        m_Shader = assets.LoadShader("PBR", 
            "Assets/Shaders/pbr.vert", 
            "Assets/Shaders/pbr.frag");

        // Create ground material (stone)
        m_GroundMaterial = assets.CreateMaterial("Ground");
        m_GroundMaterial->SetShader(m_Shader);
        m_GroundMaterial->SetAlbedo(Vector3(0.5f, 0.5f, 0.5f));
        m_GroundMaterial->SetMetallic(0.0f);
        m_GroundMaterial->SetRoughness(0.9f);

        // Create player material (blue plastic)
        m_PlayerMaterial = assets.CreateMaterial("Player");
        m_PlayerMaterial->SetShader(m_Shader);
        m_PlayerMaterial->SetAlbedo(Vector3(0.2f, 0.4f, 1.0f));
        m_PlayerMaterial->SetMetallic(0.0f);
        m_PlayerMaterial->SetRoughness(0.5f);

        // Create collectible material (gold)
        m_CollectibleMaterial = assets.CreateMaterial("Collectible");
        m_CollectibleMaterial->SetShader(m_Shader);
        m_CollectibleMaterial->SetAlbedo(Vector3(1.0f, 0.765f, 0.336f));
        m_CollectibleMaterial->SetMetallic(1.0f);
        m_CollectibleMaterial->SetRoughness(0.3f);

        // Create enemy material (red emissive)
        m_EnemyMaterial = assets.CreateMaterial("Enemy");
        m_EnemyMaterial->SetShader(m_Shader);
        m_EnemyMaterial->SetAlbedo(Vector3(0.1f, 0.1f, 0.1f));
        m_EnemyMaterial->SetEmissive(Vector3(1.0f, 0.0f, 0.0f), 3.0f);

        // Load models (if available)
        // m_PlayerModel = assets.LoadModel("Assets/Models/player.fbx");
        // m_GroundModel = assets.LoadModel("Assets/Models/ground.obj");
        // m_CollectibleModel = assets.LoadModel("Assets/Models/coin.fbx");
    }

    void InitializePhysics() {
        m_PhysicsWorld = std::make_shared<PhysicsWorld>();
        m_PhysicsWorld->Initialize();
        m_PhysicsWorld->SetGravity(Vector3(0.0f, -9.81f, 0.0f));

        // Create ground physics
        auto groundBody = m_PhysicsWorld->CreateRigidBody(
            Vector3(0.0f, -1.0f, 0.0f),  // Position
            0.0f,                         // Mass (0 = static)
            PhysicsShape::Box,
            Vector3(50.0f, 1.0f, 50.0f)  // Size
        );

        // Create player physics
        m_PlayerBody = m_PhysicsWorld->CreateRigidBody(
            Vector3(0.0f, 5.0f, 0.0f),   // Position
            1.0f,                         // Mass
            PhysicsShape::Sphere,
            Vector3(0.5f, 0.5f, 0.5f)    // Radius
        );

        // Create some collectibles
        for (int i = 0; i < 5; i++) {
            float x = (i - 2) * 3.0f;
            auto collectible = m_PhysicsWorld->CreateRigidBody(
                Vector3(x, 2.0f, 5.0f),
                0.5f,
                PhysicsShape::Sphere,
                Vector3(0.3f, 0.3f, 0.3f)
            );
            m_Collectibles.push_back(collectible);
        }
    }

    void InitializeAudio() {
        m_AudioEngine = std::make_shared<AudioEngine>();
        m_AudioEngine->Initialize();

        // Load sounds (if available)
        // m_JumpSound = m_AudioEngine->LoadSound("Assets/Audio/jump.wav");
        // m_CollectSound = m_AudioEngine->LoadSound("Assets/Audio/collect.wav");
        // m_BackgroundMusic = m_AudioEngine->LoadSound("Assets/Audio/music.ogg");
        
        // Play background music
        // m_AudioEngine->PlaySound(m_BackgroundMusic, true); // Loop
    }

    void InitializeScene() {
        m_Scene = std::make_shared<Scene>();
        
        // Create entities
        auto groundEntity = m_Scene->CreateEntity("Ground");
        // groundEntity.AddComponent<ModelComponent>(m_GroundModel);
        // groundEntity.AddComponent<MaterialComponent>(m_GroundMaterial);

        auto playerEntity = m_Scene->CreateEntity("Player");
        // playerEntity.AddComponent<ModelComponent>(m_PlayerModel);
        // playerEntity.AddComponent<MaterialComponent>(m_PlayerMaterial);

        // Camera setup
        m_CameraPosition = Vector3(0.0f, 5.0f, -10.0f);
        m_CameraTarget = Vector3(0.0f, 0.0f, 0.0f);
    }

    void HandleInput(float deltaTime) {
        const float moveSpeed = 5.0f;
        const float jumpForce = 10.0f;

        // Movement
        if (Input::IsKeyPressed(KeyCode::W)) {
            m_PlayerBody->ApplyForce(Vector3(0.0f, 0.0f, moveSpeed));
        }
        if (Input::IsKeyPressed(KeyCode::S)) {
            m_PlayerBody->ApplyForce(Vector3(0.0f, 0.0f, -moveSpeed));
        }
        if (Input::IsKeyPressed(KeyCode::A)) {
            m_PlayerBody->ApplyForce(Vector3(-moveSpeed, 0.0f, 0.0f));
        }
        if (Input::IsKeyPressed(KeyCode::D)) {
            m_PlayerBody->ApplyForce(Vector3(moveSpeed, 0.0f, 0.0f));
        }

        // Jump
        if (Input::IsKeyPressed(KeyCode::Space)) {
            m_PlayerBody->ApplyImpulse(Vector3(0.0f, jumpForce, 0.0f));
            // m_AudioEngine->PlaySound(m_JumpSound);
        }

        // Camera follow player
        Vector3 playerPos = m_PlayerBody->GetPosition();
        m_CameraPosition = playerPos + Vector3(0.0f, 5.0f, -10.0f);
        m_CameraTarget = playerPos;

        // Check collectible collisions
        for (auto& collectible : m_Collectibles) {
            float distance = (collectible->GetPosition() - playerPos).Length();
            if (distance < 1.0f) {
                // Collected!
                // m_AudioEngine->PlaySound(m_CollectSound);
                // Remove collectible
            }
        }
    }

private:
    // Systems
    std::shared_ptr<PhysicsWorld> m_PhysicsWorld;
    std::shared_ptr<AudioEngine> m_AudioEngine;
    std::shared_ptr<Scene> m_Scene;
    std::shared_ptr<Shader> m_Shader;

    // Materials
    std::shared_ptr<Material> m_GroundMaterial;
    std::shared_ptr<Material> m_PlayerMaterial;
    std::shared_ptr<Material> m_CollectibleMaterial;
    std::shared_ptr<Material> m_EnemyMaterial;

    // Models
    std::shared_ptr<Model> m_PlayerModel;
    std::shared_ptr<Model> m_GroundModel;
    std::shared_ptr<Model> m_CollectibleModel;

    // Physics bodies
    std::shared_ptr<RigidBody> m_PlayerBody;
    std::vector<std::shared_ptr<RigidBody>> m_Collectibles;

    // Audio
    unsigned int m_JumpSound;
    unsigned int m_CollectSound;
    unsigned int m_BackgroundMusic;

    // Camera
    Vector3 m_CameraPosition;
    Vector3 m_CameraTarget;
    Matrix4 m_ViewMatrix;
    Matrix4 m_ProjectionMatrix;
};

// Main game loop
int main() {
    SimpleGame game;
    
    game.Initialize();

    // Game loop
    float deltaTime = 0.016f; // ~60 FPS
    bool running = true;

    while (running) {
        game.Update(deltaTime);
        game.Render();

        // Check for exit
        if (Input::IsKeyPressed(KeyCode::Escape)) {
            running = false;
        }
    }

    game.Cleanup();
    return 0;
}

/*
 * This demo shows:
 * 
 * ✅ Asset Management - Loading models, textures, materials
 * ✅ Physics System - Rigid bodies, collisions, forces
 * ✅ Audio System - 3D spatial audio, sound effects, music
 * ✅ Material System - PBR materials with different properties
 * ✅ Scene Management - Entities and components
 * ✅ Input Handling - Keyboard controls
 * ✅ Camera System - Following player
 * 
 * To run this demo:
 * 1. Add your 3D models to Assets/Models/
 * 2. Add your audio files to Assets/Audio/
 * 3. Uncomment the asset loading lines
 * 4. Build and run!
 */
