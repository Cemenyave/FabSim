#include "mesh.h"
#include "shader.h"
#include "glad/glad.h"


void Mesh::setVertices(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
  m_vertices = vertices;
  m_indices = indices;
}

void Mesh::setVertices(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
{
  m_vertices = std::move(vertices);
  m_indices = std::move(indices);
}

void Mesh::init()
{
  // Set up vertex buffer object
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(decltype(m_vertices)::value_type), m_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(m_vertices)::value_type), 0);
  glEnableVertexAttribArray(0);

  // Normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(m_vertices)::value_type), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Color
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(decltype(m_vertices)::value_type), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(decltype(m_indices)::value_type), m_indices.data(), GL_STATIC_DRAW);
}

void Mesh::deinit()
{
  glDeleteBuffers(1, &m_IBO);
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void Mesh::draw() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);
}
