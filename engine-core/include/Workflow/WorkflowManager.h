#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace YUGA {
namespace Workflow {

// Workflow Steps
enum class WorkflowStep {
    CreateProject,
    DesignScenes,
    WriteScripts,
    CreateAnimations,
    GenerateAssets,
    TestDebug,
    Optimize,
    Export
};

// Project Template
struct ProjectTemplate {
    std::string name;
    std::string description;
    std::string type; // "2D", "3D", "FPS", "Platformer", etc.
    bool includeAIContent;
    
    ProjectTemplate(const std::string& n, const std::string& d, const std::string& t)
        : name(n), description(d), type(t), includeAIContent(true) {}
};

// AI Generation Request
struct AIGenerationRequest {
    enum class Type {
        Code,
        Asset,
        Scene,
        Animation,
        Texture,
        Model
    };
    
    Type type;
    std::string prompt;
    std::string language; // For code: "C++", "Lua", "C#"
    std::string style;    // For assets: "Realistic", "Cartoon", "Low-Poly"
    
    AIGenerationRequest(Type t, const std::string& p)
        : type(t), prompt(p), language("Lua"), style("Realistic") {}
};

// Workflow Manager - Orchestrates the complete development workflow
class WorkflowManager {
public:
    WorkflowManager();
    ~WorkflowManager();
    
    // Step 1: Create Project
    bool CreateProject(const std::string& projectName, const ProjectTemplate& templ);
    std::vector<ProjectTemplate> GetAvailableTemplates() const;
    
    // Step 2: Design Scenes
    void OpenSceneDesigner();
    void CreateNewScene(const std::string& sceneName);
    void AddGameObject(const std::string& objectType);
    
    // Step 3: Write Scripts
    void OpenScriptEditor();
    void CreateScript(const std::string& scriptName, const std::string& language);
    std::string GenerateScriptFromPrompt(const std::string& prompt, const std::string& language);
    
    // Step 4: Create Animations
    void OpenAnimationEditor();
    void CreateAnimation(const std::string& animName);
    void AddKeyframe(float time, const std::string& property, float value);
    
    // Step 5: Generate Assets (AI-Powered)
    void OpenAssetGenerator();
    std::string GenerateAsset(const AIGenerationRequest& request);
    void Generate3DModel(const std::string& description, const std::string& style);
    void GenerateTexture(const std::string& description);
    void GenerateCharacter(const std::string& description);
    
    // Step 6: Test & Debug
    void StartPlayMode();
    void StopPlayMode();
    void PausePlayMode();
    void RunAIPlaytester();
    std::vector<std::string> GetDebugLogs() const;
    
    // Step 7: Optimize
    void RunPerformanceProfiler();
    void OptimizeAssets();
    void OptimizeCode();
    std::string GetOptimizationReport() const;
    
    // Step 8: Export
    void OpenBuildSettings();
    bool BuildProject(const std::string& platform, const std::string& outputPath);
    std::vector<std::string> GetSupportedPlatforms() const;
    
    // AI Features
    void EnableAITutorMode(bool enable);
    std::string GetAIHelp(const std::string& question);
    std::vector<std::string> GetAISuggestions(const std::string& context);
    void StartAIBrainstorm(const std::string& topic);
    
    // Workflow State
    WorkflowStep GetCurrentStep() const { return currentStep; }
    void SetCurrentStep(WorkflowStep step) { currentStep = step; }
    float GetProjectProgress() const;
    
    // Callbacks
    std::function<void(const std::string&)> onLog;
    std::function<void(const std::string&)> onError;
    std::function<void(WorkflowStep)> onStepChanged;
    
private:
    WorkflowStep currentStep;
    std::string currentProjectPath;
    bool aiTutorEnabled;
    
    // Helper methods
    void Log(const std::string& message);
    void Error(const std::string& error);
    bool ConnectToAIBackend();
    std::string SendAIRequest(const std::string& endpoint, const std::string& data);
};

// AI Assistant - Provides intelligent help throughout workflow
class AIAssistant {
public:
    AIAssistant();
    
    // Natural Language Interface
    std::string ProcessCommand(const std::string& command);
    
    // Code Generation
    std::string GenerateCode(const std::string& description, const std::string& language);
    std::string ExplainCode(const std::string& code);
    std::string FixCode(const std::string& code, const std::string& error);
    std::string OptimizeCode(const std::string& code);
    
    // Asset Generation
    std::string GenerateAssetPrompt(const std::string& description);
    std::vector<std::string> SuggestAssetVariations(const std::string& baseAsset);
    
    // Learning & Help
    std::string ExplainConcept(const std::string& concept);
    std::vector<std::string> GetTutorialSteps(const std::string& topic);
    std::string AnswerQuestion(const std::string& question);
    
    // Brainstorming
    std::vector<std::string> GenerateIdeas(const std::string& category);
    std::string GenerateGameConcept(const std::string& genre);
    std::vector<std::string> SuggestFeatures(const std::string& gameType);
    
private:
    std::string apiEndpoint;
    std::string apiKey;
};

// Project Creator - Guided project setup
class ProjectCreator {
public:
    ProjectCreator();
    
    // Template Management
    void AddTemplate(const ProjectTemplate& templ);
    std::vector<ProjectTemplate> GetTemplates() const;
    ProjectTemplate GetTemplate(const std::string& name) const;
    
    // Project Creation
    bool CreateFromTemplate(const std::string& projectName, const ProjectTemplate& templ);
    void CustomizeProject(const std::string& setting, const std::string& value);
    
    // AI Content Generation
    void GenerateStarterContent(const std::string& projectType);
    void GenerateSampleScenes();
    void GenerateSampleScripts();
    void GenerateSampleAssets();
    
private:
    std::vector<ProjectTemplate> templates;
    
    void InitializeDefaultTemplates();
};

} // namespace Workflow
} // namespace YUGA
