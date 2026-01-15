#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <cstdint>

namespace YUGA {

enum class NetworkMode {
    None,
    Server,
    Client
};

enum class MessageType : uint8_t {
    Connect = 0,
    Disconnect = 1,
    PlayerJoin = 2,
    PlayerLeave = 3,
    StateSync = 4,
    RPC = 5,
    Custom = 100
};

struct NetworkMessage {
    MessageType type;
    uint32_t clientId;
    std::vector<uint8_t> data;
    
    NetworkMessage() : type(MessageType::Custom), clientId(0) {}
};

struct NetworkClient {
    uint32_t id;
    std::string address;
    uint16_t port;
    bool connected;
    float lastPingTime;
    
    NetworkClient() : id(0), port(0), connected(false), lastPingTime(0.0f) {}
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    
    // Server
    bool StartServer(uint16_t port, int maxClients = 32);
    void StopServer();
    bool IsServer() const { return mode == NetworkMode::Server; }
    
    // Client
    bool Connect(const std::string& address, uint16_t port);
    void Disconnect();
    bool IsClient() const { return mode == NetworkMode::Client; }
    bool IsConnected() const;
    
    // Messaging
    void SendToServer(const NetworkMessage& message);
    void SendToClient(uint32_t clientId, const NetworkMessage& message);
    void SendToAll(const NetworkMessage& message);
    void SendToAllExcept(uint32_t excludeId, const NetworkMessage& message);
    
    // RPC (Remote Procedure Call)
    void RegisterRPC(const std::string& name, std::function<void(uint32_t, const std::vector<uint8_t>&)> callback);
    void CallRPC(const std::string& name, const std::vector<uint8_t>& data);
    void CallRPCOnServer(const std::string& name, const std::vector<uint8_t>& data);
    void CallRPCOnClient(uint32_t clientId, const std::string& name, const std::vector<uint8_t>& data);
    void CallRPCOnAll(const std::string& name, const std::vector<uint8_t>& data);
    
    // State synchronization
    void RegisterSyncVar(const std::string& name, void* variable, size_t size);
    void SyncToServer(const std::string& name);
    void SyncToClients(const std::string& name);
    
    // Update
    void Update(float deltaTime);
    
    // Callbacks
    void SetOnClientConnected(std::function<void(uint32_t)> callback) { onClientConnected = callback; }
    void SetOnClientDisconnected(std::function<void(uint32_t)> callback) { onClientDisconnected = callback; }
    void SetOnMessageReceived(std::function<void(const NetworkMessage&)> callback) { onMessageReceived = callback; }
    
    // Info
    NetworkMode GetMode() const { return mode; }
    uint32_t GetClientId() const { return myClientId; }
    const std::vector<NetworkClient>& GetClients() const { return clients; }
    int GetClientCount() const { return static_cast<int>(clients.size()); }
    
    // Stats
    float GetPing() const { return ping; }
    uint64_t GetBytesSent() const { return bytesSent; }
    uint64_t GetBytesReceived() const { return bytesReceived; }
    
private:
    NetworkMode mode;
    uint32_t myClientId;
    std::vector<NetworkClient> clients;
    
    // Socket handles (platform-specific)
    void* serverSocket;
    void* clientSocket;
    
    // RPC system
    std::unordered_map<std::string, std::function<void(uint32_t, const std::vector<uint8_t>&)>> rpcCallbacks;
    
    // Sync vars
    struct SyncVar {
        void* variable;
        size_t size;
        std::vector<uint8_t> lastValue;
    };
    std::unordered_map<std::string, SyncVar> syncVars;
    
    // Callbacks
    std::function<void(uint32_t)> onClientConnected;
    std::function<void(uint32_t)> onClientDisconnected;
    std::function<void(const NetworkMessage&)> onMessageReceived;
    
    // Stats
    float ping;
    uint64_t bytesSent;
    uint64_t bytesReceived;
    
    // Internal
    void ProcessMessages();
    void HandleMessage(const NetworkMessage& message);
    void SendMessage(void* socket, const NetworkMessage& message);
    NetworkMessage ReceiveMessage(void* socket);
    
    // Lag compensation
    float interpolationDelay;
    void UpdateInterpolation(float deltaTime);
};

// Helper class for network objects
class NetworkObject {
public:
    NetworkObject();
    virtual ~NetworkObject() = default;
    
    uint32_t GetNetworkId() const { return networkId; }
    uint32_t GetOwnerId() const { return ownerId; }
    
    bool IsOwner() const;
    bool IsServer() const;
    
    virtual void OnNetworkSpawn() {}
    virtual void OnNetworkDespawn() {}
    virtual void OnOwnershipChanged(uint32_t newOwner) {}
    
protected:
    uint32_t networkId;
    uint32_t ownerId;
    
    void SyncTransform();
    void RequestOwnership();
};

} // namespace YUGA
