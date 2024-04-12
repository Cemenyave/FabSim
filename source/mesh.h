#pragma once

#include "glad/glad.h"
#include <cstdint>
#include <vector>

class Shader;

struct Vertex
{
  Vertex(
    float x = 0.f,
    float y = 0.f,
    float z = 0.f,

    float nx = 0.f,
    float ny = 0.f,
    float nz = 0.f,

    float r = 0.f,
    float g = 0.f,
    float b = 0.f,
    float a = 0.f)
    : m_x{x}
    , m_y{y}
    , m_z{z}

    , m_nx{nx}
    , m_ny{ny}
    , m_nz{nz}

    , m_r{r}
    , m_g{g}
    , m_b{b}
    , m_a{a}
  {}

  // Vertex position
  float m_x = 0.f;
  float m_y = 0.f;
  float m_z = 0.f;

  // Vertex normal
  float m_nx = 0.f;
  float m_ny = 0.f;
  float m_nz = 0.f;

  // Vertex color
  float m_r = 0.f;
  float m_g = 0.f;
  float m_b = 0.f;
  float m_a = 0.f;
};

class Mesh
{
public:
  Mesh() = default;
  void setVertices(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
  void setVertices(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
  void init();
  void deinit();
  void draw() const;

private:
  GLuint m_VBO;
  GLuint m_IBO;
  GLuint m_VAO;

  //stores unique vertex data
  std::vector<Vertex> m_vertices;

  //stores indices to correctly draw a mesh using data from vertices
  std::vector<uint32_t> m_indices;
};
