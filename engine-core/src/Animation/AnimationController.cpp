#include "Animation/AnimationController.h"
#include "Math/MathUtils.h"
#include "Core/Log.h"

namespace YUGA {

// AnimationStateMachine implementation
void AnimationStateMachine::AddState(const std::string& name, const std::string& clipName) {
    stateToClip[name] = clipName;
    if (currentState.empty()) {
        currentState = name;
    }
}

void AnimationStateMachine::AddTransition(const AnimationTransition& transition) {
    transitions.push_back(transition);
}

void AnimationStateMachine::SetParameter(const std::string& name, bool value) {
    boolParameters[name] = value;
}

void AnimationStateMachine::SetParameter(const std::string& name, float value) {
    floatParameters[name] = value;
}

std::string AnimationStateMachine::GetTargetClip() const {
    auto it = stateToClip.find(currentState);
    if (it != stateToClip.end()) {
        return it->second;
    }
    return "";
}

void AnimationStateMachine::Update(float deltaTime) {
    // Check for valid transitions
    for (const auto& transition : transitions) {
        if (transition.fromState == currentState && EvaluateCondition(transition.condition)) {
            currentState = transition.toState;
            break;
        }
    }
}

bool AnimationStateMachine::EvaluateCondition(const std::string& condition) const {
    // Simple condition evaluation (can be expanded)
    auto boolIt = boolParameters.find(condition);
    if (boolIt != boolParameters.end()) {
        return boolIt->second;
    }
    return false;
}

// BlendTree implementation
void BlendTree::AddNode(const BlendNode& node) {
    nodes.push_back(node);
}

void BlendTree::SetBlendParameter(float x, float y) {
    blendParameter.x = x;
    blendParameter.y = y;
    CalculateWeights();
}

std::vector<std::pair<std::string, float>> BlendTree::GetActiveClips() const {
    std::vector<std::pair<std::string, float>> result;
    for (const auto& node : nodes) {
        if (node.weight > 0.001f) {
            result.push_back({node.clipName, node.weight});
        }
    }
    return result;
}

void BlendTree::CalculateWeights() {
    // Simple 2D blend space calculation
    float totalWeight = 0.0f;
    
    for (auto& node : nodes) {
        float dx = blendParameter.x - node.position.x;
        float dy = blendParameter.y - node.position.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        
        node.weight = std::max(0.0f, 1.0f - distance);
        totalWeight += node.weight;
    }
    
    // Normalize weights
    if (totalWeight > 0.0f) {
        for (auto& node : nodes) {
            node.weight /= totalWeight;
        }
    }
}

// AnimationController implementation
AnimationController::AnimationController()
    : state(AnimationState::Stopped)
    , currentTime(0.0f)
    , playbackSpeed(1.0f)
    , looping(true)
    , blendTime(0.0f)
    , blendDuration(0.0f)
    , useStateMachine(false)
    , useBlendTree(false)
    , eventCallback(nullptr)
{
}

void AnimationController::AddClip(const std::string& name, const AnimationClip& clip) {
    clips[name] = clip;
}

void AnimationController::RemoveClip(const std::string& name) {
    clips.erase(name);
}

bool AnimationController::HasClip(const std::string& name) const {
    return clips.find(name) != clips.end();
}

void AnimationController::Play(const std::string& clipName, float fadeTime) {
    if (!HasClip(clipName)) {
        return;
    }
    
    if (fadeTime > 0.0f && state == AnimationState::Playing) {
        // Start blending to new animation
        nextClipName = clipName;
        blendTime = 0.0f;
        blendDuration = fadeTime;
    } else {
        // Immediate switch
        currentClipName = clipName;
        currentTime = 0.0f;
        state = AnimationState::Playing;
        nextClipName.clear();
        blendTime = 0.0f;
    }
}

void AnimationController::Stop() {
    state = AnimationState::Stopped;
    currentTime = 0.0f;
}

void AnimationController::Pause() {
    if (state == AnimationState::Playing) {
        state = AnimationState::Paused;
    }
}

void AnimationController::Resume() {
    if (state == AnimationState::Paused) {
        state = AnimationState::Playing;
    }
}

void AnimationController::Update(float deltaTime) {
    if (state != AnimationState::Playing) {
        return;
    }
    
    if (currentClipName.empty() || !HasClip(currentClipName)) {
        return;
    }
    
    // Update time
    currentTime += deltaTime * playbackSpeed;
    
    const AnimationClip& clip = clips[currentClipName];
    
    // Handle looping
    if (currentTime >= clip.duration) {
        if (clip.looping || looping) {
            currentTime = fmod(currentTime, clip.duration);
        } else {
            currentTime = clip.duration;
            state = AnimationState::Stopped;
        }
    }
    
    // Handle blending
    if (!nextClipName.empty() && blendDuration > 0.0f) {
        blendTime += deltaTime;
        if (blendTime >= blendDuration) {
            // Blend complete, switch to next animation
            currentClipName = nextClipName;
            currentTime = 0.0f;
            nextClipName.clear();
            blendTime = 0.0f;
        }
    }
}

float AnimationController::GetNormalizedTime() const {
    if (currentClipName.empty() || !HasClip(currentClipName)) {
        return 0.0f;
    }
    
    const AnimationClip& clip = clips.at(currentClipName);
    if (clip.duration > 0.0f) {
        return currentTime / clip.duration;
    }
    return 0.0f;
}

void AnimationController::GetCurrentTransform(Vector3& position, Quaternion& rotation, Vector3& scale) const {
    if (currentClipName.empty() || !HasClip(currentClipName)) {
        position = Vector3::Zero();
        rotation = Quaternion::Identity();
        scale = Vector3::One();
        return;
    }
    
    const AnimationClip& currentClip = clips.at(currentClipName);
    
    if (!nextClipName.empty() && blendDuration > 0.0f) {
        // Blending between two animations
        const AnimationClip& nextClip = clips.at(nextClipName);
        
        Vector3 pos1, pos2, scale1, scale2;
        Quaternion rot1, rot2;
        
        SampleClip(currentClip, currentTime, pos1, rot1, scale1);
        SampleClip(nextClip, 0.0f, pos2, rot2, scale2);
        
        float blend = Math::Clamp(blendTime / blendDuration, 0.0f, 1.0f);
        BlendTransforms(pos1, rot1, scale1, pos2, rot2, scale2, blend, position, rotation, scale);
    } else {
        // Single animation
        SampleClip(currentClip, currentTime, position, rotation, scale);
    }
}

void AnimationController::SampleClip(const AnimationClip& clip, float time, Vector3& position, Quaternion& rotation, Vector3& scale) const {
    if (clip.keyframes.empty()) {
        position = Vector3::Zero();
        rotation = Quaternion::Identity();
        scale = Vector3::One();
        return;
    }
    
    // Find keyframes to interpolate between
    size_t nextIndex = 0;
    for (size_t i = 0; i < clip.keyframes.size(); ++i) {
        if (clip.keyframes[i].time > time) {
            nextIndex = i;
            break;
        }
    }
    
    if (nextIndex == 0) {
        // Before first keyframe
        const AnimationKeyframe& kf = clip.keyframes[0];
        position = kf.position;
        rotation = kf.rotation;
        scale = kf.scale;
    } else if (nextIndex >= clip.keyframes.size()) {
        // After last keyframe
        const AnimationKeyframe& kf = clip.keyframes.back();
        position = kf.position;
        rotation = kf.rotation;
        scale = kf.scale;
    } else {
        // Interpolate between keyframes
        const AnimationKeyframe& kf1 = clip.keyframes[nextIndex - 1];
        const AnimationKeyframe& kf2 = clip.keyframes[nextIndex];
        
        float t = (time - kf1.time) / (kf2.time - kf1.time);
        t = Math::Clamp(t, 0.0f, 1.0f);
        
        position = Vector3::Lerp(kf1.position, kf2.position, t);
        rotation = Quaternion::Slerp(kf1.rotation, kf2.rotation, t);
        scale = Vector3::Lerp(kf1.scale, kf2.scale, t);
    }
}

void AnimationController::BlendTransforms(const Vector3& pos1, const Quaternion& rot1, const Vector3& scale1,
                                         const Vector3& pos2, const Quaternion& rot2, const Vector3& scale2,
                                         float blend, Vector3& outPos, Quaternion& outRot, Vector3& outScale) const {
    outPos = Vector3::Lerp(pos1, pos2, blend);
    outRot = Quaternion::Slerp(rot1, rot2, blend);
    outScale = Vector3::Lerp(scale1, scale2, blend);
}

} // namespace YUGA

void AnimationController::SetSkeleton(const std::vector<Bone>& bones) {
    skeleton = bones;
}

AnimationClip* AnimationController::GetClip(const std::string& name) {
    auto it = clips.find(name);
    if (it != clips.end()) {
        return &it->second;
    }
    return nullptr;
}

void AnimationController::CrossFade(const std::string& clipName, float fadeTime) {
    Play(clipName, fadeTime);
}

void AnimationController::GetBoneTransforms(std::vector<Vector3>& positions, std::vector<Quaternion>& rotations, std::vector<Vector3>& scales) const {
    if (skeleton.empty()) {
        return;
    }
    
    positions.resize(skeleton.size());
    rotations.resize(skeleton.size());
    scales.resize(skeleton.size());
    
    if (currentClipName.empty() || !HasClip(currentClipName)) {
        // Return bind pose
        for (size_t i = 0; i < skeleton.size(); ++i) {
            positions[i] = skeleton[i].position;
            rotations[i] = skeleton[i].rotation;
            scales[i] = skeleton[i].scale;
        }
        return;
    }
    
    const AnimationClip& currentClip = clips.at(currentClipName);
    
    if (!nextClipName.empty() && blendDuration > 0.0f) {
        // Blending between two animations
        const AnimationClip& nextClip = clips.at(nextClipName);
        
        std::vector<Vector3> pos1, pos2, scale1, scale2;
        std::vector<Quaternion> rot1, rot2;
        
        SampleClip(currentClip, currentTime, pos1, rot1, scale1);
        SampleClip(nextClip, 0.0f, pos2, rot2, scale2);
        
        float blend = Math::Clamp(blendTime / blendDuration, 0.0f, 1.0f);
        
        for (size_t i = 0; i < skeleton.size(); ++i) {
            BlendTransforms(pos1[i], rot1[i], scale1[i], pos2[i], rot2[i], scale2[i], 
                          blend, positions[i], rotations[i], scales[i]);
        }
    } else {
        // Single animation
        SampleClip(currentClip, currentTime, positions, rotations, scales);
    }
}

void AnimationController::AddEvent(const std::string& clipName, float time, const std::string& eventName) {
    AnimationEvent event;
    event.clipName = clipName;
    event.time = time;
    event.eventName = eventName;
    event.triggered = false;
    events.push_back(event);
}

void AnimationController::SetEventCallback(void (*callback)(const std::string& eventName)) {
    eventCallback = callback;
}

void AnimationController::SampleClip(const AnimationClip& clip, float time, std::vector<Vector3>& positions, 
                                    std::vector<Quaternion>& rotations, std::vector<Vector3>& scales) const {
    if (skeleton.empty()) {
        return;
    }
    
    positions.resize(skeleton.size());
    rotations.resize(skeleton.size());
    scales.resize(skeleton.size());
    
    // Initialize with bind pose
    for (size_t i = 0; i < skeleton.size(); ++i) {
        positions[i] = skeleton[i].position;
        rotations[i] = skeleton[i].rotation;
        scales[i] = skeleton[i].scale;
    }
    
    // Apply bone animations
    for (const auto& boneAnim : clip.boneAnimations) {
        if (boneAnim.boneIndex < 0 || boneAnim.boneIndex >= static_cast<int>(skeleton.size())) {
            continue;
        }
        
        if (boneAnim.keyframes.empty()) {
            continue;
        }
        
        // Find keyframes to interpolate between
        size_t nextIndex = 0;
        for (size_t i = 0; i < boneAnim.keyframes.size(); ++i) {
            if (boneAnim.keyframes[i].time > time) {
                nextIndex = i;
                break;
            }
        }
        
        if (nextIndex == 0) {
            // Before first keyframe
            const AnimationKeyframe& kf = boneAnim.keyframes[0];
            positions[boneAnim.boneIndex] = kf.position;
            rotations[boneAnim.boneIndex] = kf.rotation;
            scales[boneAnim.boneIndex] = kf.scale;
        } else if (nextIndex >= boneAnim.keyframes.size()) {
            // After last keyframe
            const AnimationKeyframe& kf = boneAnim.keyframes.back();
            positions[boneAnim.boneIndex] = kf.position;
            rotations[boneAnim.boneIndex] = kf.rotation;
            scales[boneAnim.boneIndex] = kf.scale;
        } else {
            // Interpolate between keyframes
            const AnimationKeyframe& kf1 = boneAnim.keyframes[nextIndex - 1];
            const AnimationKeyframe& kf2 = boneAnim.keyframes[nextIndex];
            
            float t = (time - kf1.time) / (kf2.time - kf1.time);
            t = Math::Clamp(t, 0.0f, 1.0f);
            
            positions[boneAnim.boneIndex] = Vector3::Lerp(kf1.position, kf2.position, t);
            rotations[boneAnim.boneIndex] = Quaternion::Slerp(kf1.rotation, kf2.rotation, t);
            scales[boneAnim.boneIndex] = Vector3::Lerp(kf1.scale, kf2.scale, t);
        }
    }
}

void AnimationController::CheckEvents() {
    if (!eventCallback) {
        return;
    }
    
    for (auto& event : events) {
        if (event.clipName == currentClipName && !event.triggered) {
            if (currentTime >= event.time) {
                eventCallback(event.eventName);
                event.triggered = true;
            }
        }
        
        // Reset triggered flag when animation loops
        if (currentTime < event.time) {
            event.triggered = false;
        }
    }
}

} // namespace YUGA
