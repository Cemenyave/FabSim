#pragma once

#include "glm/glm/ext/vector_float4.hpp"
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/ext/quaternion_float.hpp>

class Camera
{
public:
  glm::mat4x4 getToCameraMatrix() const;

  void addPosition(glm::vec3 posDiff);
  void setPosition(glm::vec3 newPos);
  void addRotation(float yaw, float pitch);
  void setRotation(float yaw, float pitch);

private:
  glm::vec3 m_position = glm::vec4(0.0);

  // yaw and pitch in radians
  float m_yaw = 0.f;
  float m_pitch = 0.f;
};
