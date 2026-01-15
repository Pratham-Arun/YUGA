#include "Assets/Mesh.h"
#include "Core/Log.h"
#include <glad/glad.h>

namespace YUGA {

    Mesh::Mesh() {}

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : Vertices(vertices), Indices(indices) {
        SetupMesh();
    }

    Mesh::~Mesh() {
        Cleanup();
    }

    void Mesh::SetupMesh() {
        if (m_IsSetup) {
            Cleanup();
        }

        // Generate buffers
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        // Load vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

        // Load index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // Vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        // Vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

        // Vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);

        m_IsSetup = true;
        LOG_INFO("Mesh setup complete: {} vertices, {} indices", Vertices.size(), Indices.size());
    }

    void Mesh::Draw() {
        if (!m_IsSetup) {
            LOG_WARN("Attempting to draw mesh that hasn't been setup");
            return;
        }

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::Cleanup() {
        if (m_IsSetup) {
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
            m_VAO = m_VBO = m_EBO = 0;
            m_IsSetup = false;
        }
    }

} // namespace YUGA
