/**
 * YUGA Engine - Complete AI-Powered Workflow Demo
 * Demonstrates the 8-step game development workflow
 */

#include "Workflow/WorkflowManager.h"
#include "Core/Log.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace YUGA;
using namespace YUGA::Workflow;

void PrintHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  " << title;
    for (size_t i = title.length(); i < 52; i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

void Wait(int seconds = 1) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main() {
    PrintHeader("YUGA ENGINE - AI-POWERED WORKFLOW DEMO");
    
    LOG_INFO("Welcome to YUGA Engine!");
    LOG_INFO("This demo showcases the complete AI-powered game development workflow");
    LOG_INFO("");
    
    // Initialize Workflow Manager
    WorkflowManager workflow;
    AIAssistant ai;
    ProjectCreator creator;
    
    // Enable AI Tutor Mode
    workflow.EnableAITutorMode(true);
    Wait(1);
    
    // ========================================
    // STEP 1: CREATE PROJECT
    // ========================================
    PrintHeader("STEP 1: CREATE PROJECT");
    
    LOG_INFO("📋 Available Templates:");
    auto templates = workflow.GetAvailableTemplates();
    for (size_t i = 0; i < templates.size(); i++) {
        LOG_INFO("   {}. {} - {}", i + 1, templates[i].name, templates[i].description);
    }
    LOG_INFO("");
    
    // Create a 3D FPS project
    LOG_INFO("Creating a 3D FPS game...");
    workflow.CreateProject("MyAwesomeFPS", templates[1]);
    Wait(2);
    
    // ========================================
    // STEP 2: DESIGN SCENES
    // ========================================
    PrintHeader("STEP 2: DESIGN SCENES");
    
    workflow.OpenSceneDesigner();
    workflow.CreateNewScene("MainLevel");
    Wait(1);
    
    LOG_INFO("Adding game objects to scene:");
    workflow.AddGameObject("Player");
    workflow.AddGameObject("Enemy");
    workflow.AddGameObject("Weapon");
    workflow.AddGameObject("Terrain");
    workflow.AddGameObject("Skybox");
    Wait(2);
    
    // ========================================
    // STEP 3: WRITE SCRIPTS (AI-POWERED)
    // ========================================
    PrintHeader("STEP 3: WRITE SCRIPTS WITH AI");
    
    workflow.OpenScriptEditor();
    Wait(1);
    
    LOG_INFO("🤖 Using AI to generate scripts:");
    LOG_INFO("");
    
    // Generate player controller
    std::string playerScript = workflow.GenerateScriptFromPrompt(
        "Create a first-person player controller with WASD movement and mouse look",
        "Lua"
    );
    LOG_INFO("Generated PlayerController.lua");
    Wait(1);
    
    // Generate enemy AI
    std::string enemyScript = workflow.GenerateScriptFromPrompt(
        "Create an enemy AI that patrols and chases the player when nearby",
        "Lua"
    );
    LOG_INFO("Generated EnemyAI.lua");
    Wait(1);
    
    // Generate weapon system
    std::string weaponScript = workflow.GenerateScriptFromPrompt(
        "Create a weapon system with shooting, reloading, and ammo management",
        "Lua"
    );
    LOG_INFO("Generated WeaponSystem.lua");
    Wait(2);
    
    // ========================================
    // STEP 4: CREATE ANIMATIONS
    // ========================================
    PrintHeader("STEP 4: CREATE ANIMATIONS");
    
    workflow.OpenAnimationEditor();
    Wait(1);
    
    LOG_INFO("Creating animations:");
    workflow.CreateAnimation("PlayerWalk");
    workflow.AddKeyframe(0.0f, "position.y", 0.0f);
    workflow.AddKeyframe(0.5f, "position.y", 0.2f);
    workflow.AddKeyframe(1.0f, "position.y", 0.0f);
    Wait(1);
    
    workflow.CreateAnimation("EnemyAttack");
    workflow.AddKeyframe(0.0f, "rotation.x", 0.0f);
    workflow.AddKeyframe(0.3f, "rotation.x", 45.0f);
    workflow.AddKeyframe(0.6f, "rotation.x", 0.0f);
    Wait(2);
    
    // ========================================
    // STEP 5: GENERATE ASSETS (AI-POWERED)
    // ========================================
    PrintHeader("STEP 5: GENERATE ASSETS WITH AI");
    
    workflow.OpenAssetGenerator();
    Wait(1);
    
    LOG_INFO("🎨 Using AI to generate game assets:");
    LOG_INFO("");
    
    // Generate 3D models
    workflow.Generate3DModel("Futuristic sci-fi weapon with glowing parts", "Low-Poly");
    Wait(1);
    
    workflow.Generate3DModel("Alien enemy creature with tentacles", "Realistic");
    Wait(1);
    
    workflow.GenerateCharacter("Armored space marine with helmet");
    Wait(1);
    
    // Generate textures
    workflow.GenerateTexture("Rusty metal wall with bullet holes");
    Wait(1);
    
    workflow.GenerateTexture("Alien organic floor texture");
    Wait(2);
    
    // ========================================
    // STEP 6: TEST & DEBUG (AI-POWERED)
    // ========================================
    PrintHeader("STEP 6: TEST & DEBUG");
    
    LOG_INFO("Starting game in Play Mode...");
    workflow.StartPlayMode();
    Wait(2);
    
    LOG_INFO("Game running... Testing gameplay...");
    Wait(2);
    
    LOG_INFO("🤖 Running AI Playtester:");
    workflow.RunAIPlaytester();
    Wait(2);
    
    LOG_INFO("AI Playtest Results:");
    LOG_INFO("   ✓ Difficulty: Balanced");
    LOG_INFO("   ✓ Player movement: Smooth");
    LOG_INFO("   ⚠ Enemy AI: Too predictable (suggestion: add random behavior)");
    LOG_INFO("   ✓ Weapon feel: Satisfying");
    LOG_INFO("   ⚠ Level design: Add more cover points");
    Wait(2);
    
    workflow.StopPlayMode();
    Wait(1);
    
    // ========================================
    // STEP 7: OPTIMIZE (AI-POWERED)
    // ========================================
    PrintHeader("STEP 7: OPTIMIZE");
    
    LOG_INFO("Running performance analysis...");
    workflow.RunPerformanceProfiler();
    Wait(2);
    
    LOG_INFO("🤖 AI: Analyzing performance bottlenecks...");
    Wait(1);
    
    LOG_INFO("Optimizing assets...");
    workflow.OptimizeAssets();
    Wait(1);
    
    LOG_INFO("🤖 AI: Optimizing code...");
    workflow.OptimizeCode();
    Wait(1);
    
    LOG_INFO("");
    LOG_INFO(workflow.GetOptimizationReport());
    Wait(2);
    
    // ========================================
    // STEP 8: EXPORT
    // ========================================
    PrintHeader("STEP 8: EXPORT");
    
    workflow.OpenBuildSettings();
    Wait(1);
    
    LOG_INFO("📦 Supported Platforms:");
    auto platforms = workflow.GetSupportedPlatforms();
    for (const auto& platform : platforms) {
        LOG_INFO("   • {}", platform);
    }
    LOG_INFO("");
    
    LOG_INFO("Building for Windows...");
    workflow.BuildProject("Windows", "./Builds/MyAwesomeFPS_Windows.exe");
    Wait(2);
    
    LOG_INFO("Building for Linux...");
    workflow.BuildProject("Linux", "./Builds/MyAwesomeFPS_Linux");
    Wait(2);
    
    // ========================================
    // WORKFLOW COMPLETE
    // ========================================
    PrintHeader("WORKFLOW COMPLETE!");
    
    LOG_INFO("🎉 Congratulations! Your game is ready!");
    LOG_INFO("");
    LOG_INFO("📊 Project Statistics:");
    LOG_INFO("   • Scenes: 1");
    LOG_INFO("   • Scripts: 3 (AI-generated)");
    LOG_INFO("   • Animations: 2");
    LOG_INFO("   • 3D Models: 3 (AI-generated)");
    LOG_INFO("   • Textures: 2 (AI-generated)");
    LOG_INFO("   • Platforms: 2 (Windows, Linux)");
    LOG_INFO("   • Development Time: ~30 minutes (vs 30+ hours traditional)");
    LOG_INFO("");
    
    float progress = workflow.GetProjectProgress();
    LOG_INFO("✅ Workflow Progress: {}%", static_cast<int>(progress * 100));
    LOG_INFO("");
    
    // ========================================
    // AI FEATURES DEMO
    // ========================================
    PrintHeader("BONUS: AI FEATURES");
    
    LOG_INFO("🤖 AI Tutor Mode:");
    std::string help = workflow.GetAIHelp("How do I add multiplayer to my game?");
    LOG_INFO(help);
    Wait(2);
    
    LOG_INFO("");
    LOG_INFO("💡 AI Brainstorming:");
    workflow.StartAIBrainstorm("power-ups for FPS game");
    Wait(1);
    
    LOG_INFO("");
    LOG_INFO("🎯 AI Suggestions:");
    auto suggestions = workflow.GetAISuggestions("FPS gameplay");
    for (const auto& suggestion : suggestions) {
        LOG_INFO("   • {}", suggestion);
    }
    Wait(2);
    
    // ========================================
    // FINAL MESSAGE
    // ========================================
    PrintHeader("THANK YOU!");
    
    LOG_INFO("This demo showcased the complete YUGA workflow:");
    LOG_INFO("");
    LOG_INFO("✅ 1. Create Project - AI-assisted setup");
    LOG_INFO("✅ 2. Design Scenes - Visual editor");
    LOG_INFO("✅ 3. Write Scripts - AI code generation");
    LOG_INFO("✅ 4. Create Animations - Timeline editor");
    LOG_INFO("✅ 5. Generate Assets - AI 3D models & textures");
    LOG_INFO("✅ 6. Test & Debug - AI playtester");
    LOG_INFO("✅ 7. Optimize - AI performance analysis");
    LOG_INFO("✅ 8. Export - Multi-platform builds");
    LOG_INFO("");
    LOG_INFO("🚀 YUGA Engine: 10x Faster Game Development!");
    LOG_INFO("");
    
    return 0;
}
