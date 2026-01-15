#pragma once

#include "Core/Core.h"
#include "Math/Vector3.h"
#include <vector>
#include <string>

namespace YUGA {

    struct Vertex {
        Vector3 Position;
        Vector3 Normal;
        float TexCoords[2];
        Vector3 Tangent;
        Vector3 Bitangent;

        Vertex() : Position(), Normal(), TexCoords{0.0f, 0.0f}, Tangent(), Bitangent() {}
    };

    class Mesh {
    public:
        std::vector<Vertex> Vertices;
        std::vector<unsigned int> Indices;
        unsigned int MaterialIndex = 0;

        Mesh();
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void SetupMesh();
        void Draw();
        void Cleanup();

        unsigned int GetVAO() const { return m_VAO; }
        unsigned int GetVertexCount() const { return static_cast<unsigned int>(Vertices.size()); }
        unsigned int GetIndexCount() const { return static_cast<unsigned int>(Indices.size()); }

    private:
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        unsigned int m_EBO = 0;
        bool m_IsSetup = false;
    };

} // namespace YUGA
