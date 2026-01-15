#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace YUGA {

// Bone structure for skeletal animation
struct Bone {
    std::string name;
    int parentIndex;
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    
    Bone() : parentIndex(-1), position(Vector3::Zero()), rotation(Quaternion::Identity()), scale(Vector3::One()) {}
};

struct AnimationKeyframe {
    float time;
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    
    AnimationKeyframe() : time(0.0f), position(Vector3::Zero()), rotation(Quaternion::Identity()), scale(Vector3::One()) {}
};

struct BoneAnimation {
    int boneIndex;
    std::vector<AnimationKeyframe> keyframes;
};

struct AnimationClip {
    std::string name;
    float duration;
    bool looping;
    std::vector<BoneAnimation> boneAnimations;
    
    AnimationClip() : duration(0.0f), looping(true) {}
};

enum class AnimationState {
    Idle,
    Playing,
    Paused,
    Stopped
};

// State machine for animation transitions
struct AnimationTransition {
    std::string fromState;
    std::string toState;
    std::string condition;
    float blendTime;
    
    AnimationTransition() : blendTime(0.3f) {}
};

class AnimationStateMachine {
public:
    void AddState(const std::string& name, const std::string& clipName);
    void AddTransition(const AnimationTransition& transition);
    void SetParameter(const std::string& name, bool value);
    void SetParameter(const std::string& name, float value);
    
    std::string GetCurrentState() const { return currentState; }
    std::string GetTargetClip() const;
    
    void Update(float deltaTime);
    
private:
    std::string currentState;
    std::unordered_map<std::string, std::string> stateToClip;
    std::vector<AnimationTransition> transitions;
    std::unordered_map<std::string, bool> boolParameters;
    std::unordered_map<std::string, float> floatParameters;
    
    bool EvaluateCondition(const std::string& condition) const;
};

// Blend tree for smooth animation blending
struct BlendNode {
    std::string clipName;
    float weight;
    Vector2 position; // For 2D blend spaces
    
    BlendNode() : weight(0.0f), position(0, 0) {}
};

class BlendTree {
public:
    void AddNode(const BlendNode& node);
    void SetBlendParameter(float x, float y = 0.0f);
    
    std::vector<std::pair<std::string, float>> GetActiveClips() const;
    
private:
    std::vector<BlendNode> nodes;
    Vector2 blendParameter;
    
    void CalculateWeights();
};

class AnimationController {
public:
    AnimationController();
    ~AnimationController() = default;
    
    // Skeleton
    void SetSkeleton(const std::vector<Bone>& bones);
    const std::vector<Bone>& GetSkeleton() const { return skeleton; }
    
    // Clip management
    void AddClip(const std::string& name, const AnimationClip& clip);
    void RemoveClip(const std::string& name);
    bool HasClip(const std::string& name) const;
    AnimationClip* GetClip(const std::string& name);
    
    // Playback control
    void Play(const std::string& clipName, float fadeTime = 0.0f);
    void Stop();
    void Pause();
    void Resume();
    void CrossFade(const std::string& clipName, float fadeTime);
    
    // Update
    void Update(float deltaTime);
    
    // State
    AnimationState GetState() const { return state; }
    float GetCurrentTime() const { return currentTime; }
    float GetNormalizedTime() const;
    const std::string& GetCurrentClip() const { return currentClipName; }
    
    // Settings
    void SetSpeed(float speed) { playbackSpeed = speed; }
    float GetSpeed() const { return playbackSpeed; }
    
    void SetLooping(bool loop) { looping = loop; }
    bool IsLooping() const { return looping; }
    
    // Get current transform
    void GetCurrentTransform(Vector3& position, Quaternion& rotation, Vector3& scale) const;
    void GetBoneTransforms(std::vector<Vector3>& positions, std::vector<Quaternion>& rotations, std::vector<Vector3>& scales) const;
    
    // State machine
    AnimationStateMachine& GetStateMachine() { return stateMachine; }
    void EnableStateMachine(bool enable) { useStateMachine = enable; }
    
    // Blend tree
    BlendTree& GetBlendTree() { return blendTree; }
    void EnableBlendTree(bool enable) { useBlendTree = enable; }
    
    // Events
    void AddEvent(const std::string& clipName, float time, const std::string& eventName);
    void SetEventCallback(void (*callback)(const std::string& eventName));
    
private:
    std::vector<Bone> skeleton;
    std::unordered_map<std::string, AnimationClip> clips;
    std::string currentClipName;
    AnimationState state;
    float currentTime;
    float playbackSpeed;
    bool looping;
    
    // Blending
    std::string nextClipName;
    float blendTime;
    float blendDuration;
    
    // State machine & blend tree
    AnimationStateMachine stateMachine;
    BlendTree blendTree;
    bool useStateMachine;
    bool useBlendTree;
    
    // Events
    struct AnimationEvent {
        std::string clipName;
        float time;
        std::string eventName;
        bool triggered;
    };
    std::vector<AnimationEvent> events;
    void (*eventCallback)(const std::string& eventName);
    
    void SampleClip(const AnimationClip& clip, float time, std::vector<Vector3>& positions, 
                    std::vector<Quaternion>& rotations, std::vector<Vector3>& scales) const;
    void BlendTransforms(const Vector3& pos1, const Quaternion& rot1, const Vector3& scale1,
                        const Vector3& pos2, const Quaternion& rot2, const Vector3& scale2,
                        float blend, Vector3& outPos, Quaternion& outRot, Vector3& outScale) const;
    void CheckEvents();
};

} // namespace YUGA
