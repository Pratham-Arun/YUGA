#include "Network/NetworkManager.h"
#include "Core/Log.h"
#include <cstring>

namespace YUGA {

NetworkManager::NetworkManager()
    : mode(NetworkMode::None)
    , myClientId(0)
    , serverSocket(nullptr)
    , clientSocket(nullptr)
    , ping(0.0f)
    , bytesSent(0)
    , bytesReceived(0)
    , interpolationDelay(0.1f)
{
}

NetworkManager::~NetworkManager() {
    if (mode == NetworkMode::Server) {
        StopServer();
    } else if (mode == NetworkMode::Client) {
        Disconnect();
    }
}

bool NetworkManager::StartServer(uint16_t port, int maxClients) {
    if (mode != NetworkMode::None) {
        LOG_ERROR("Network already initialized");
        return false;
    }
    
    // TODO: Platform-specific socket creation
    // For now, this is a stub implementation
    LOG_INFO("Starting server on port " + std::to_string(port));
    
    mode = NetworkMode::Server;
    myClientId = 0; // Server is always ID 0
    
    LOG_INFO("Server started successfully");
    return true;
}

void NetworkManager::StopServer() {
    if (mode != NetworkMode::Server) {
        return;
    }
    
    // Notify all clients
    NetworkMessage disconnectMsg;
    disconnectMsg.type = MessageType::Disconnect;
    SendToAll(disconnectMsg);
    
    // Close sockets
    clients.clear();
    mode = NetworkMode::None;
    
    LOG_INFO("Server stopped");
}

bool NetworkManager::Connect(const std::string& address, uint16_t port) {
    if (mode != NetworkMode::None) {
        LOG_ERROR("Network already initialized");
        return false;
    }
    
    // TODO: Platform-specific socket connection
    LOG_INFO("Connecting to " + address + ":" + std::to_string(port));
    
    mode = NetworkMode::Client;
    
    // Send connect message
    NetworkMessage connectMsg;
    connectMsg.type = MessageType::Connect;
    SendToServer(connectMsg);
    
    LOG_INFO("Connected to server");
    return true;
}

void NetworkManager::Disconnect() {
    if (mode != NetworkMode::Client) {
        return;
    }
    
    // Send disconnect message
    NetworkMessage disconnectMsg;
    disconnectMsg.type = MessageType::Disconnect;
    SendToServer(disconnectMsg);
    
    mode = NetworkMode::None;
    
    LOG_INFO("Disconnected from server");
}

bool NetworkManager::IsConnected() const {
    return mode == NetworkMode::Client && clientSocket != nullptr;
}

void NetworkManager::SendToServer(const NetworkMessage& message) {
    if (mode != NetworkMode::Client) {
        return;
    }
    
    SendMessage(clientSocket, message);
}

void NetworkManager::SendToClient(uint32_t clientId, const NetworkMessage& message) {
    if (mode != NetworkMode::Server) {
        return;
    }
    
    for (auto& client : clients) {
        if (client.id == clientId && client.connected) {
            // TODO: Send to specific client socket
            break;
        }
    }
}

void NetworkManager::SendToAll(const NetworkMessage& message) {
    if (mode != NetworkMode::Server) {
        return;
    }
    
    for (auto& client : clients) {
        if (client.connected) {
            SendToClient(client.id, message);
        }
    }
}

void NetworkManager::SendToAllExcept(uint32_t excludeId, const NetworkMessage& message) {
    if (mode != NetworkMode::Server) {
        return;
    }
    
    for (auto& client : clients) {
        if (client.connected && client.id != excludeId) {
            SendToClient(client.id, message);
        }
    }
}

void NetworkManager::RegisterRPC(const std::string& name, std::function<void(uint32_t, const std::vector<uint8_t>&)> callback) {
    rpcCallbacks[name] = callback;
}

void NetworkManager::CallRPC(const std::string& name, const std::vector<uint8_t>& data) {
    if (mode == NetworkMode::Server) {
        CallRPCOnAll(name, data);
    } else {
        CallRPCOnServer(name, data);
    }
}

void NetworkManager::CallRPCOnServer(const std::string& name, const std::vector<uint8_t>& data) {
    NetworkMessage msg;
    msg.type = MessageType::RPC;
    msg.data = data;
    // Prepend RPC name to data
    SendToServer(msg);
}

void NetworkManager::CallRPCOnClient(uint32_t clientId, const std::string& name, const std::vector<uint8_t>& data) {
    NetworkMessage msg;
    msg.type = MessageType::RPC;
    msg.data = data;
    SendToClient(clientId, msg);
}

void NetworkManager::CallRPCOnAll(const std::string& name, const std::vector<uint8_t>& data) {
    NetworkMessage msg;
    msg.type = MessageType::RPC;
    msg.data = data;
    SendToAll(msg);
}

void NetworkManager::RegisterSyncVar(const std::string& name, void* variable, size_t size) {
    SyncVar syncVar;
    syncVar.variable = variable;
    syncVar.size = size;
    syncVar.lastValue.resize(size);
    std::memcpy(syncVar.lastValue.data(), variable, size);
    
    syncVars[name] = syncVar;
}

void NetworkManager::SyncToServer(const std::string& name) {
    auto it = syncVars.find(name);
    if (it == syncVars.end()) {
        return;
    }
    
    SyncVar& syncVar = it->second;
    
    // Check if value changed
    if (std::memcmp(syncVar.variable, syncVar.lastValue.data(), syncVar.size) != 0) {
        NetworkMessage msg;
        msg.type = MessageType::StateSync;
        msg.data.resize(syncVar.size);
        std::memcpy(msg.data.data(), syncVar.variable, syncVar.size);
        
        SendToServer(msg);
        
        // Update last value
        std::memcpy(syncVar.lastValue.data(), syncVar.variable, syncVar.size);
    }
}

void NetworkManager::SyncToClients(const std::string& name) {
    auto it = syncVars.find(name);
    if (it == syncVars.end()) {
        return;
    }
    
    SyncVar& syncVar = it->second;
    
    NetworkMessage msg;
    msg.type = MessageType::StateSync;
    msg.data.resize(syncVar.size);
    std::memcpy(msg.data.data(), syncVar.variable, syncVar.size);
    
    SendToAll(msg);
}

void NetworkManager::Update(float deltaTime) {
    ProcessMessages();
    UpdateInterpolation(deltaTime);
    
    // Update ping for clients
    if (mode == NetworkMode::Client) {
        // TODO: Implement ping calculation
    }
}

void NetworkManager::ProcessMessages() {
    // TODO: Process incoming messages from sockets
}

void NetworkManager::HandleMessage(const NetworkMessage& message) {
    switch (message.type) {
        case MessageType::Connect:
            if (mode == NetworkMode::Server && onClientConnected) {
                onClientConnected(message.clientId);
            }
            break;
            
        case MessageType::Disconnect:
            if (mode == NetworkMode::Server && onClientDisconnected) {
                onClientDisconnected(message.clientId);
            }
            break;
            
        case MessageType::RPC:
            // TODO: Parse RPC name and call callback
            break;
            
        case MessageType::StateSync:
            // TODO: Update synced variables
            break;
            
        default:
            if (onMessageReceived) {
                onMessageReceived(message);
            }
            break;
    }
}

void NetworkManager::SendMessage(void* socket, const NetworkMessage& message) {
    // TODO: Platform-specific socket send
    bytesSent += message.data.size();
}

NetworkMessage NetworkManager::ReceiveMessage(void* socket) {
    // TODO: Platform-specific socket receive
    NetworkMessage msg;
    return msg;
}

void NetworkManager::UpdateInterpolation(float deltaTime) {
    // TODO: Implement client-side interpolation for smooth movement
}

// NetworkObject implementation
static uint32_t nextNetworkId = 1;

NetworkObject::NetworkObject()
    : networkId(nextNetworkId++)
    , ownerId(0)
{
}

bool NetworkObject::IsOwner() const {
    // TODO: Check against NetworkManager
    return true;
}

bool NetworkObject::IsServer() const {
    // TODO: Check NetworkManager mode
    return false;
}

void NetworkObject::SyncTransform() {
    // TODO: Sync position, rotation, scale
}

void NetworkObject::RequestOwnership() {
    // TODO: Send ownership request to server
}

} // namespace YUGA
