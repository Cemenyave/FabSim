#pragma once

#include "glm/glm/ext/matrix_float4x4.hpp"
#include "glm/glm/ext/vector_float4.hpp"
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/ext/quaternion_float.hpp>

class Camera
{
public:
  glm::mat4x4 getToCameraMatrix() const;
  glm::mat4x4 getCamereraProjectionMatrix() const;

  void addPosition(glm::vec3 posDiff);
  void setPosition(glm::vec3 newPos);

  glm::vec3 getForward() const;
  glm::vec3 getUp() const;
  glm::vec3 getRight() const;
  
  // Add camera rotation in radians
  void addRotation(float yaw, float pitch);

  // Set camera rotation in radians
  void setRotation(float yaw, float pitch);

private:
  void updateTransform();
private:
  glm::vec3 m_position = glm::vec4(0.0);
  glm::mat4 m_transform {1.f};

  // yaw and pitch in radians
  float m_yaw = 0.f;//180.f;
  float m_pitch = 0.f;
};
