#pragma once

#include "mesh.h"
#include "glm/glm/ext/vector_float3.hpp"
#include "glm/glm/ext/matrix_float4x4.hpp"

class Object
{
public:
  Object(Mesh&& mesh);

  void setTransform(glm::mat4x4 transform);
  void setScalse(glm::vec3);
  void setPosition(glm::vec3);

  const Mesh& getMesh() const;
  glm::mat4x4 getTransform() const;

private:
  Mesh m_mesh;

  glm::mat4x4 m_transform{1.f};
};
