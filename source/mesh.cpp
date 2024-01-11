#include "mesh.h"
#include "shader.h"
#include "glad/glad.h"


void Mesh::setVertices(const std::vector<Vertex>& vertices)
{
  m_vertices = vertices;
}

void Mesh::setVertices(std::vector<Vertex>&& vertices)
{
  m_vertices = std::move(vertices);
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
}

void Mesh::deinit()
{
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void Mesh::draw() const
{
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}
