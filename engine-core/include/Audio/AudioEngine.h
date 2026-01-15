#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <unordered_map>

namespace YUGA {
    
    class AudioEngine {
    public:
        static void Initialize();
        static void Shutdown();
        static void Update();
        
        // Listener (camera/player position)
        static void SetListenerPosition(const Vector3& position);
        static void SetListenerVelocity(const Vector3& velocity);
        static void SetListenerOrientation(const Vector3& forward, const Vector3& up);
        
        // Audio clip loading
        static uint32_t LoadAudioClip(const std::string& filepath);
        static void UnloadAudioClip(uint32_t clipId);
        
        // Playback
        static uint32_t PlaySound(uint32_t clipId, bool loop = false);
        static uint32_t PlaySound3D(uint32_t clipId, const Vector3& position, bool loop = false);
        static void StopSound(uint32_t sourceId);
        static void PauseSound(uint32_t sourceId);
        
        // Volume control
        static void SetMasterVolume(float volume);
        static void SetSourceVolume(uint32_t sourceId, float volume);
        
    private:
        static ALCdevice* s_Device;
        static ALCcontext* s_Context;
        static std::unordered_map<uint32_t, ALuint> s_AudioClips;
        static std::unordered_map<uint32_t, ALuint> s_AudioSources;
        static uint32_t s_NextClipId;
        static uint32_t s_NextSourceId;
    };
    
} // namespace YUGA
