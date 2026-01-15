// Example: Using the YUGA Asset Pipeline
// This demonstrates loading models, textures, and materials

#include "Core/Engine.h"
#include "Assets/AssetManager.h"
#include "Assets/Model.h"
#include "Assets/Material.h"
#include "Rendering/Shader.h"

using namespace YUGA;

void AssetPipelineExample() {
    // Get the asset manager singleton
    auto& assetManager = AssetManager::Get();

    // ===== LOADING A 3D MODEL =====
    // Supports: .obj, .fbx, .gltf, .dae, .blend, and more
    auto model = assetManager.LoadModel("Assets/Models/character.fbx");
    
    if (model) {
        LOG_INFO("Model loaded with {} meshes", model->GetMeshes().size());
        
        // Draw the model (automatically uses its materials)
        model->Draw();
    }

    // ===== LOADING TEXTURES =====
    auto diffuseTexture = assetManager.LoadTexture("Assets/Textures/brick_diffuse.png", TextureType::Diffuse);
    auto normalTexture = assetManager.LoadTexture("Assets/Textures/brick_normal.png", TextureType::Normal);
    auto roughnessTexture = assetManager.LoadTexture("Assets/Textures/brick_roughness.png", TextureType::Roughness);

    // ===== CREATING A CUSTOM MATERIAL =====
    auto material = assetManager.CreateMaterial("BrickMaterial");
    
    // Load and set shader
    auto shader = assetManager.LoadShader("PBR", "Assets/Shaders/pbr.vert", "Assets/Shaders/pbr.frag");
    material->SetShader(shader);
    
    // Set textures
    material->SetTexture(TextureType::Diffuse, diffuseTexture);
    material->SetTexture(TextureType::Normal, normalTexture);
    material->SetTexture(TextureType::Roughness, roughnessTexture);
    
    // Set material properties
    material->SetAlbedo(Vector3(1.0f, 1.0f, 1.0f));
    material->SetMetallic(0.0f);
    material->SetRoughness(0.8f);
    material->SetAO(1.0f);

    // ===== USING THE MATERIAL =====
    material->Bind();
    // ... draw your mesh here ...
    material->Unbind();

    // ===== CREATING A GLOWING MATERIAL =====
    auto emissiveMaterial = assetManager.CreateMaterial("GlowMaterial");
    emissiveMaterial->SetShader(shader);
    emissiveMaterial->SetAlbedo(Vector3(0.1f, 0.1f, 0.1f));
    emissiveMaterial->SetEmissive(Vector3(0.0f, 1.0f, 0.0f), 5.0f); // Green glow, strength 5

    // ===== CREATING A METALLIC MATERIAL =====
    auto metalMaterial = assetManager.CreateMaterial("MetalMaterial");
    metalMaterial->SetShader(shader);
    metalMaterial->SetAlbedo(Vector3(0.8f, 0.8f, 0.8f));
    metalMaterial->SetMetallic(1.0f);  // Fully metallic
    metalMaterial->SetRoughness(0.2f); // Smooth metal

    // ===== ASSET CACHING =====
    // Assets are automatically cached - loading the same file returns the cached version
    auto cachedModel = assetManager.LoadModel("Assets/Models/character.fbx");
    // cachedModel points to the same model as before (no reload)

    // ===== MEMORY MANAGEMENT =====
    // Unload specific assets
    assetManager.UnloadModel("Assets/Models/character.fbx");
    assetManager.UnloadTexture("Assets/Textures/brick_diffuse.png");
    
    // Unload assets that are no longer referenced
    assetManager.UnloadUnused();
    
    // Unload everything
    assetManager.UnloadAll();

    // ===== ASSET STATISTICS =====
    LOG_INFO("Loaded assets:");
    LOG_INFO("  Models: {}", assetManager.GetModelCount());
    LOG_INFO("  Textures: {}", assetManager.GetTextureCount());
    LOG_INFO("  Materials: {}", assetManager.GetMaterialCount());
    LOG_INFO("  Shaders: {}", assetManager.GetShaderCount());
}

// ===== COMPLETE RENDERING EXAMPLE =====
void RenderSceneWithAssets() {
    auto& assetManager = AssetManager::Get();

    // Load shader
    auto shader = assetManager.LoadShader("PBR", "Assets/Shaders/pbr.vert", "Assets/Shaders/pbr.frag");
    shader->Bind();

    // Set camera uniforms
    // shader->SetMat4("u_View", viewMatrix);
    // shader->SetMat4("u_Projection", projectionMatrix);
    // shader->SetFloat3("u_CameraPos", cameraPos.x, cameraPos.y, cameraPos.z);

    // Set lighting
    shader->SetInt("u_NumLights", 2);
    shader->SetFloat3("u_LightPositions[0]", 10.0f, 10.0f, 10.0f);
    shader->SetFloat3("u_LightColors[0]", 300.0f, 300.0f, 300.0f);
    shader->SetFloat3("u_LightPositions[1]", -10.0f, 10.0f, 10.0f);
    shader->SetFloat3("u_LightColors[1]", 300.0f, 300.0f, 300.0f);

    // Load and draw model
    auto model = assetManager.LoadModel("Assets/Models/scene.obj");
    if (model) {
        // shader->SetMat4("u_Model", modelMatrix);
        model->Draw(); // Automatically binds materials and draws all meshes
    }

    shader->Unbind();
}

// ===== SUPPORTED FILE FORMATS =====
/*
 * 3D Models (via Assimp):
 *   - .obj (Wavefront)
 *   - .fbx (Autodesk)
 *   - .gltf / .glb (Khronos)
 *   - .dae (Collada)
 *   - .blend (Blender)
 *   - .3ds (3D Studio)
 *   - .ase (3D Studio ASCII)
 *   - .ply (Stanford)
 *   - .stl (Stereolithography)
 *   - And 40+ more formats!
 *
 * Textures (via STB Image):
 *   - .png
 *   - .jpg / .jpeg
 *   - .bmp
 *   - .tga
 *   - .psd
 *   - .gif
 *   - .hdr
 *   - .pic
 */
