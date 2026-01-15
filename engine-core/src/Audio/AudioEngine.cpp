#include "Audio/AudioEngine.h"
#include "Core/Log.h"

namespace YUGA {
    
    ALCdevice* AudioEngine::s_Device = nullptr;
    ALCcontext* AudioEngine::s_Context = nullptr;
    std::unordered_map<uint32_t, ALuint> AudioEngine::s_AudioClips;
    std::unordered_map<uint32_t, ALuint> AudioEngine::s_AudioSources;
    uint32_t AudioEngine::s_NextClipId = 1;
    uint32_t AudioEngine::s_NextSourceId = 1;
    
    void AudioEngine::Initialize() {
        // Open default device
        s_Device = alcOpenDevice(nullptr);
        if (!s_Device) {
            Log::Error("Failed to open audio device");
            return;
        }
        
        // Create context
        s_Context = alcCreateContext(s_Device, nullptr);
        if (!s_Context) {
            Log::Error("Failed to create audio context");
            return;
        }
        
        alcMakeContextCurrent(s_Context);
        
        // Set default listener properties
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        
        float orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
        alListenerfv(AL_ORIENTATION, orientation);
        
        Log::Info("Audio engine initialized");
    }
    
    void AudioEngine::Shutdown() {
        // Clean up sources
        for (auto& [id, source] : s_AudioSources) {
            alDeleteSources(1, &source);
        }
        s_AudioSources.clear();
        
        // Clean up buffers
        for (auto& [id, buffer] : s_AudioClips) {
            alDeleteBuffers(1, &buffer);
        }
        s_AudioClips.clear();
        
        // Destroy context
        if (s_Context) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(s_Context);
            s_Context = nullptr;
        }
        
        // Close device
        if (s_Device) {
            alcCloseDevice(s_Device);
            s_Device = nullptr;
        }
        
        Log::Info("Audio engine shutdown");
    }
    
    void AudioEngine::Update() {
        // Update audio sources, remove finished ones
        std::vector<uint32_t> toRemove;
        for (auto& [id, source] : s_AudioSources) {
            ALint state;
            alGetSourcei(source, AL_SOURCE_STATE, &state);
            if (state == AL_STOPPED) {
                toRemove.push_back(id);
            }
        }
        
        for (uint32_t id : toRemove) {
            alDeleteSources(1, &s_AudioSources[id]);
            s_AudioSources.erase(id);
        }
    }
    
    void AudioEngine::SetListenerPosition(const Vector3& position) {
        alListener3f(AL_POSITION, position.x, position.y, position.z);
    }
    
    void AudioEngine::SetListenerVelocity(const Vector3& velocity) {
        alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }
    
    void AudioEngine::SetListenerOrientation(const Vector3& forward, const Vector3& up) {
        float orientation[] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
        alListenerfv(AL_ORIENTATION, orientation);
    }
    
    uint32_t AudioEngine::LoadAudioClip(const std::string& filepath) {
        // Simplified - in real implementation, load WAV/OGG file
        ALuint buffer;
        alGenBuffers(1, &buffer);
        
        uint32_t clipId = s_NextClipId++;
        s_AudioClips[clipId] = buffer;
        
        Log::Info("Audio clip loaded: " + filepath);
        return clipId;
    }
    
    void AudioEngine::UnloadAudioClip(uint32_t clipId) {
        auto it = s_AudioClips.find(clipId);
        if (it != s_AudioClips.end()) {
            alDeleteBuffers(1, &it->second);
            s_AudioClips.erase(it);
        }
    }
    
    uint32_t AudioEngine::PlaySound(uint32_t clipId, bool loop) {
        auto it = s_AudioClips.find(clipId);
        if (it == s_AudioClips.end()) return 0;
        
        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, it->second);
        alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        alSourcePlay(source);
        
        uint32_t sourceId = s_NextSourceId++;
        s_AudioSources[sourceId] = source;
        return sourceId;
    }
    
    uint32_t AudioEngine::PlaySound3D(uint32_t clipId, const Vector3& position, bool loop) {
        uint32_t sourceId = PlaySound(clipId, loop);
        if (sourceId > 0) {
            ALuint source = s_AudioSources[sourceId];
            alSource3f(source, AL_POSITION, position.x, position.y, position.z);
        }
        return sourceId;
    }
    
    void AudioEngine::StopSound(uint32_t sourceId) {
        auto it = s_AudioSources.find(sourceId);
        if (it != s_AudioSources.end()) {
            alSourceStop(it->second);
        }
    }
    
    void AudioEngine::PauseSound(uint32_t sourceId) {
        auto it = s_AudioSources.find(sourceId);
        if (it != s_AudioSources.end()) {
            alSourcePause(it->second);
        }
    }
    
    void AudioEngine::SetMasterVolume(float volume) {
        alListenerf(AL_GAIN, volume);
    }
    
    void AudioEngine::SetSourceVolume(uint32_t sourceId, float volume) {
        auto it = s_AudioSources.find(sourceId);
        if (it != s_AudioSources.end()) {
            alSourcef(it->second, AL_GAIN, volume);
        }
    }
    
} // namespace YUGA
