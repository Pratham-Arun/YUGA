#include "Core/Engine.h"
#include "Core/Log.h"

int main(int argc, char** argv) {
    YUGA::Log::Info("╔════════════════════════════════════════════╗");
    YUGA::Log::Info("║     YUGA ENGINE - C++ Game Engine Core    ║");
    YUGA::Log::Info("║     AI-Powered Game Development Platform   ║");
    YUGA::Log::Info("╚════════════════════════════════════════════╝");
    
    try {
        auto& engine = YUGA::Engine::Get();
        
        // Configure engine
        YUGA::EngineConfig config;
        config.title = "YUGA Engine - Test Application";
        config.width = 1920;
        config.height = 1080;
        config.vsync = true;
        
        // Initialize
        engine.Initialize(config);
        
        // Run main loop
        engine.Run();
        
        // Shutdown
        engine.Shutdown();
        
        YUGA::Log::Info("✓ Application exited successfully");
        return 0;
        
    } catch (const std::exception& e) {
        YUGA::Log::Critical("Fatal error: ", e.what());
        return 1;
    }
}
